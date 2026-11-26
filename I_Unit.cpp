#pragma once
#include "I_Unit.hpp"

I_Unit::I_Unit(
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
	:	position(_position),
		movementSpeed(_movementSpeed),
		facingRight(_facingRight),
		hp(_hp),
		maxHp(_maxHp),
		activeOrder(_activeOrder),
		attackRange(_attackRange),
		aggroRange(_aggroRange),
		attackTarget(_attackTarget),
		swingSpeed(_swingSpeed),
		swingRecoverySpeed(_swingRecoverySpeed),
		attackDamage(_attackDamage),
		chanceToHit(_chanceToHit)
{
	swingCountdown = 0.0f;
	swingRecoveryCountdown = 0.0f;
};