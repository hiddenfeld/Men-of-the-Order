#include "Goblin.hpp"

Goblin::Goblin(
	const int& _spawnPosition,
	const int& _patrolRange)
	:	I_Unit(
			_spawnPosition,
			300,
			false,
			6,
			6,
			OrderType::Patrol,
			90,
			900,
			NULL,
			0.8f,
			2.7f,
			2,
			95),
		spawnPosition(_spawnPosition)
{
	patrolPosition1 = _spawnPosition - _patrolRange;
	patrolPosition2 = _spawnPosition + _patrolRange;
	patrolingToPoint1 = false;
	swingCountdown = 0.0f;
	swingRecoveryCountdown = 0.0f;
};

Goblin::Goblin(
	const int& _spawnPosition,
	const int& _patrolPosition1,
	const int& _patrolPosition2)
	:	I_Unit(
			_spawnPosition,
			300,
			false,
			6,
			6,
			OrderType::Patrol,
			90,
			900,
			NULL,
			0.8f,
			2.7f,
			2,
			95),
		spawnPosition(_spawnPosition),
		patrolPosition1(_patrolPosition1),
		patrolPosition2(_patrolPosition2)
{
	patrolingToPoint1 = false;
	swingCountdown = 0.0f;
	swingRecoveryCountdown = 0.0f;
};

Goblin::Goblin(
	const int& _position,
	const int& _spawnPosition,
	const int& _patrolPosition1,
	const int& _patrolPosition2,
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
			_strikeRecoverySpeed,
			_attackDamage,
			_chanceToHit),
		spawnPosition(_spawnPosition),
		patrolPosition1(_patrolPosition1),
		patrolPosition2(_patrolPosition2)
{
	patrolingToPoint1 = false;
	swingCountdown = 0.0f;
	swingRecoveryCountdown = 0.0f;
};

void Goblin::update(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	countDownCountdowns(_seconds);
	if (hp > 0) {
		switch (activeOrder) {
			case OrderType::Patrol:
				move(_seconds, _designatedPosition, _playerFacingRight);
				checkAggro(_engine);
				break;
			case OrderType::Charge:
				checkCharge(_engine, _seconds, _designatedPosition, _playerFacingRight);
				break;
			case OrderType::Swing:
				checkSwing(_seconds);
				break;
			default:
				std::cout << "ERROR in Goblin.cpp on Line #" << __LINE__ << ". Unknown orderType!" << std::endl;
				break;
		}
	}
};

void Goblin::countDownCountdowns(const float& _seconds) {
	countDownBy(swingRecoveryCountdown, _seconds);
	countDownBy(swingCountdown, _seconds);
};

void Goblin::checkAggro(I_Engine* _engine) {
	I_Unit* unit{_engine->getKnight()};
	if (   std::abs(position - unit->position) < aggroRange
		&& unit->hp > 0) {
		activeOrder = OrderType::Charge;
		attackTarget = unit;
	}
};

void Goblin::checkCharge(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	if (attackTarget == NULL) {
		activeOrder = OrderType::Patrol;
		return;
	}
	int distanceBetweenThisAndTarget{std::abs(position - attackTarget->position)};
	if (distanceBetweenThisAndTarget > attackRange + attackTarget->attackRange)
		move(_seconds, _designatedPosition, _playerFacingRight);
	else {
		if (swingRecoveryCountdown <= 0.0f) {
			// initiate melee attack
			activeOrder = OrderType::Swing;
			swingCountdown = swingSpeed;
		}
	}
};

void Goblin::checkSwing(const float& _seconds) {
	if (swingCountdown <= 0.0f) {
		if (Atlas::rollChanceToSucceed(chanceToHit))
			attackTarget->getHurt(attackDamage);
		swingRecoveryCountdown = swingRecoverySpeed;
		if (attackTarget->hp == 0) {
			attackTarget = NULL;
			activeOrder = OrderType::Patrol;
		} else {
			activeOrder = OrderType::Charge;
		}
	}
};

void Goblin::move(const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	int distanceTraveled{(int)(_seconds * (float)movementSpeed)};
	if (distanceTraveled == 0)
		distanceTraveled++;
	// determine destination
	int designatedPosition{0};
	switch (activeOrder) {
		case OrderType::Patrol:
			if (patrolingToPoint1)
				designatedPosition = patrolPosition1;
			else
				designatedPosition = patrolPosition2;
			break;
		case OrderType::Charge:
			designatedPosition = attackTarget->position;
			break;
		default:
			std::cout << "ERROR in Goblin.cpp on Line #" << __LINE__ << ". Unknown orderType!" << std::endl;
			break;
	}
	int distanceBetweenPositionAndDestination{std::abs(designatedPosition - position)};
	if (distanceBetweenPositionAndDestination <= distanceTraveled) {
		position = designatedPosition;
		if (activeOrder == OrderType::Patrol)
			if (patrolingToPoint1)
				patrolingToPoint1 = false;
			else
				patrolingToPoint1 = true;
	}
	else if (designatedPosition < position) {
		facingRight = false;
		position -= distanceTraveled;
	} else {
		facingRight = true;
		position += distanceTraveled;
	}
};

void Goblin::getHurt(const int& _amount) {
	if (hp > 0) {
		hp -= _amount;
		if (hp < 0)
			hp = 0;
		if (hp == 0)
			activeOrder = OrderType::None;
	}
	//SoundManager::playSound({SoundOrigin::Goblin, SoundReason::Hurt}, 50.0f);
};

void Goblin::getHealed(const int& _amount) {
	if (hp < maxHp) {
		hp += _amount;
		if (hp > maxHp)
			hp = maxHp;
	}
};