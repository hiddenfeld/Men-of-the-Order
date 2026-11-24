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
	const float& _strikeRecoverySpeed,
	const int& _attackDamage)
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
		strikeRecoverySpeed(_strikeRecoverySpeed),
		attackDamage(_attackDamage)
{
	swingCountdown = 0.0f;
	strikeRecoveryCountdown = 0.0f;
};