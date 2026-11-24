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
	const bool& _learnedBlock,
	const float& _blockSpeed)
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
			_attackDamage),
		learnedBlock(_learnedBlock),
		blockSpeed(_blockSpeed)
{
	currentBlockCooldown = 0.0f;
};

void Knight::update(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	if (hp > 0) {
		if (position != _designatedPosition)
			move(_seconds, _designatedPosition, _playerFacingRight);
		if (currentBlockCooldown > 0.0f) {
			currentBlockCooldown -= _seconds;
			if (currentBlockCooldown < 0.0f)
				currentBlockCooldown = 0.0f;
		}
	}
};

void Knight::checkAggro(I_Engine* _engine) {

};

void Knight::checkCharge(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {

};

void Knight::checkSwing(const float& _seconds) {

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

void Knight::getHurt(const int& _amount) {
	bool attackBlocked{false};
	if (learnedBlock)
		if (currentBlockCooldown <= 0.0f) {
			SoundManager::playSound({SoundOrigin::Knight, SoundReason::Block}, 50.0f);
			attackBlocked = true;
			currentBlockCooldown = blockSpeed;
		}
	if (!attackBlocked) {
		if (hp > 0) {
			hp -= _amount;
		}
		SoundManager::playSound({SoundOrigin::Knight, SoundReason::Hurt}, 50.0f);
	}
};

void Knight::getHealed(const int& _amount) {
	if (hp < maxHp) {
		hp += _amount;
		if (hp > maxHp)
			hp = maxHp;
	}
};