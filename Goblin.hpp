#pragma once
#include <iostream>
#include "I_Engine.hpp"
#include "I_Unit.hpp"
#include "OrderType.hpp"
#include "SoundManager.hpp"

struct Goblin : public I_Unit {
	int spawnPosition;
	int patrolPosition1;
	int patrolPosition2;
	bool patrolingToPoint1;

	Goblin(const int&, const int&);
	Goblin(const int&, const int&, const int&);
	Goblin(const int&, const int&, const int&, const int&, const int&, const bool&, const int&, const int&, const OrderType&, const int&, const int&, I_Unit*, const float&, const float&, const int&, const int&);

	void update(I_Engine*, const float&, const int&, const bool&);
	void countDownCountdowns(const float&);
	void move(const float&, const int&, const bool&);
	void checkAggro(I_Engine*);
	bool checkAggroForUnit(I_Unit*);
	void checkCharge(I_Engine*, const float&, const int&, const bool&);
	void checkSwing(const float&);
	void getHurt(const int&);
	void getHealed(const int&);
};