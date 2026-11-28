#pragma once
#include "Knight.hpp"

Knight::Knight(
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
	const float& _strikeRecoverySpeed,
	const int& _attackDamage,
	const int& _chanceToHit,
	const bool& _learnedBlock,
	const float& _blockSpeed,
	const int& _chanceToBlock)
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
			_strikeRecoverySpeed,
			_attackDamage,
			_chanceToHit),
		learnedBlock(_learnedBlock),
		blockSpeed(_blockSpeed),
		chanceToBlock(_chanceToBlock)
{
	currentBlockCooldown = 0.0f;
};

void Knight::update(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	countDownCountdowns(_seconds);
	if (hp > 0) {
		switch (activeOrder) {
			case OrderType::ProtectFront:
				if (   !checkCollision(_engine)
					&& position != _designatedPosition)
					move(_seconds, _designatedPosition, _playerFacingRight);
				checkAggro(_engine);
				break;
			case OrderType::Swing:
				checkSwing(_seconds);
				break;
			case OrderType::Patrol:
			case OrderType::Charge:
			default:
				std::cout << "ERROR in Knight.cpp on Line #" << __LINE__ << ". Unknown orderType!" << std::endl;
				break;
		}	
	}
};

void Knight::countDownCountdowns(const float& _seconds) {
	countDownBy(swingCountdown, _seconds);
	countDownBy(swingRecoveryCountdown, _seconds);
	countDownBy(currentBlockCooldown, _seconds);
};

void Knight::checkAggro(I_Engine* _engine) {
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

void Knight::checkCharge(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {

};

void Knight::checkSwing(const float& _seconds) {
	if (swingCountdown <= 0.0f) {
		activeOrder = OrderType::ProtectFront;
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

void Knight::move(const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
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

bool Knight::checkCollision(I_Engine* _engine) {
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

void Knight::getHurt(const int& _amount) {
	if (hp > 0) {
		bool attackBlocked{false};
		if (learnedBlock) {
			if (currentBlockCooldown <= 0.0f) {
				if (chanceToBlock >= 100)
					attackBlocked = true;
				else {
					if (Atlas::rollChanceToSucceed(chanceToBlock))
						attackBlocked = true;
					if (Atlas::rollChanceToImprove(chanceToBlock))
						chanceToBlock++;
				}
				if (attackBlocked) {
					SoundManager::playSound({SoundOrigin::Knight, SoundReason::Block}, 50.0f);
					currentBlockCooldown = blockSpeed;
				}
			}
		}
		if (!attackBlocked) {
			hp -= _amount;
			if (hp < 0)
				hp = 0;
			SoundManager::playSound({SoundOrigin::Knight, SoundReason::Hurt}, 50.0f);
		}
	}
};

void Knight::getHealed(const int& _amount) {
	if (   hp > 0
		&& hp < maxHp) {
		hp += _amount;
		if (hp > maxHp)
			hp = maxHp;
		SoundManager::playSound({SoundOrigin::SpellOrb, SoundReason::Heal}, 50.0f);
	}
};