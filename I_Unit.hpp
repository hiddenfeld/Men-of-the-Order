#pragma once
#include "I_Engine.hpp"
#include "CountDownByUtility.cpp"
#include "OrderType.hpp"

struct I_Unit {
	
	int position;
	int movementSpeed;
	bool facingRight;
	int hp;
	int maxHp;
	int attackRange;
	int aggroRange;
	OrderType activeOrder;
	I_Unit* attackTarget;
	float swingCountdown;
	float swingSpeed;
	float swingRecoveryCountdown;
	float swingRecoverySpeed;
	int attackDamage;
	int chanceToHit;

	I_Unit(const int&, const int&, const bool&, const int&, const int&, const OrderType&, const int&, const int&, I_Unit*, const float&, const float&, const int&, const int&);

	virtual void update(I_Engine*, const float&, const int&, const bool&) = 0;
	virtual void move(const float&, const int&, const bool&) = 0;
	virtual void checkAggro(I_Engine*) = 0;
	virtual void checkCharge(I_Engine*, const float&, const int&, const bool&) = 0;
	virtual void checkSwing(const float&) = 0;

	virtual void getHurt(const int&) = 0;
	virtual void getHealed(const int&) = 0;
};