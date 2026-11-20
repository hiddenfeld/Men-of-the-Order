#include "Goblin.hpp"

void Goblin::update(I_Engine* _engine, const float& _seconds, const int& _designatedPosition, const bool& _playerFacingRight) {
	strikeRecoveryCountdown -= _seconds;
	if (strikeRecoveryCountdown < 0.0f)
		strikeRecoveryCountdown = 0.0f;
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
		if (strikeRecoveryCountdown <= 0.0f) {
			// initiate melee attack
			activeOrder = OrderType::Swing;
			swingCountdown = swingSpeed;
		}
	}
};

void Goblin::checkSwing(const float& _seconds) {
	swingCountdown -= _seconds;
	if (swingCountdown < 0.0f)
		swingCountdown = 0.0f;
	if (swingCountdown == 0.0f) {
		attackTarget->getHurt(attackDamage);
		strikeRecoveryCountdown = strikeRecoverySpeed;
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
	int designatedPosition;
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