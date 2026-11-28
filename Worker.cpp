#pragma once
#include "Worker.hpp"

Worker::Worker(
	const int& _position,
	const int& _movementSpeed,
	const bool& _facingRight,
	const int& _hp,
	const int& _maxHp,
	const OrderType& _activeOrder,
	const int& _attackRange,
	const int& _aggroRange,
	I_Unit* _attackTarget,
	const float& _swingSpeed,
	const float& _swingRecoverySpeed,
	const int& _attackDamage,
	const int& _chanceToHit)
	:	I_Unit(
			_position,
			_movementSpeed,
			_facingRight,
			_hp,
			_maxHp,
			_activeOrder,
			_attackRange,
			_aggroRange,
			_attackTarget,
			_swingSpeed,
			_swingRecoverySpeed,
			_attackDamage,
			_chanceToHit)
{

};

void Worker::update(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	countDownCountdowns(_seconds);
	if (hp > 0)
		switch (activeOrder) {
			case OrderType::Follow:
				checkAggro(_engine);
				if (   !checkCollision(_engine)
					&& activeOrder == OrderType::Follow
					&& position != _designatedPosition)
					move(_seconds, _designatedPosition, _playerFacingRight);
				break;
			case OrderType::Swing:
				checkSwing(_seconds);
				break;
			default:
				std::cout << "ERROR in Worker::update on line #" << __LINE__ << ". Unknown orderType!" << std::endl;
				break;
		}
};

void Worker::countDownCountdowns(const float& _seconds) {
	countDownBy(swingCountdown, _seconds);
	countDownBy(swingRecoveryCountdown, _seconds);
};

void Worker::move(const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	int distanceTraveled{(int)(_seconds * (float)movementSpeed)};
	if (distanceTraveled == 0)
		distanceTraveled++;
	int distanceBetweenPositionAndDestination{std::abs(_designatedPosition - position)};
	if (distanceBetweenPositionAndDestination <= distanceTraveled) {
		position = _designatedPosition;
		if (_playerFacingRight)
			facingRight = true;
		else
			facingRight = false;
	}
	else if (_designatedPosition < position) {
		facingRight = false;
		position -= distanceTraveled;
	} else {
		facingRight = true;
		position += distanceTraveled;
	}
};

bool Worker::checkCollision(I_Engine* _engine) {
	for (std::vector<Goblin*>::iterator it{_engine->getGoblins()->begin()}; it != _engine->getGoblins()->end(); it++) {
		I_Unit* goblin{*it};
		if (goblin->hp > 0) {
			int distanceBetweenThisAndTarget{std::abs(position - goblin->position)};
			if (distanceBetweenThisAndTarget <= attackRange + goblin->attackRange - 50)
				return true;
		}
	}
	return false;
};

void Worker::checkAggro(I_Engine* _engine) {
	for (std::vector<Goblin*>::iterator it{_engine->getGoblins()->begin()}; it != _engine->getGoblins()->end(); it++) {
		I_Unit* goblin{*it};
		if (goblin->hp > 0) {
			int distanceBetweenThisAndTarget{std::abs(position - goblin->position)};
			if (distanceBetweenThisAndTarget <= attackRange + goblin->attackRange) {
				if (swingRecoveryCountdown <= 0.0f) {
					// initiate melee attack
					activeOrder = OrderType::Swing;
					attackTarget = goblin;
					swingCountdown = swingSpeed;
				}
			}
		}
	}
};

void Worker::checkCharge(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {

};

void Worker::checkSwing(const float& _seconds) {
	if (attackTarget->position > position)
		facingRight = true;
	else
		facingRight = false;
	if (swingCountdown <= 0.0f) {
		activeOrder = OrderType::Follow;
		if (chanceToHit >= 100)
			attackTarget->getHurt(attackDamage);
		else {
			if (Atlas::rollChanceToSucceed(chanceToHit))
				attackTarget->getHurt(attackDamage);
			if (Atlas::rollChanceToImprove(chanceToHit))
				chanceToHit++;
		}
		swingRecoveryCountdown = swingRecoverySpeed;
		attackTarget = NULL;
	}
};

void Worker::getHurt(const int& _amount) {
	if (hp > 0) {
		hp -= _amount;
		if (hp < 0)
			hp = 0;
		SoundManager::playSound({SoundOrigin::Knight, SoundReason::Hurt}, 50.0f);
	}
};

void Worker::getHealed(const int& _amount) {
	if (   hp > 0
		&& hp < maxHp) {
		hp += _amount;
		if (hp > maxHp)
			hp = maxHp;
		SoundManager::playSound({SoundOrigin::SpellOrb, SoundReason::Heal}, 50.0f);
	}
};