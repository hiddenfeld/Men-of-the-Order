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

	void update(I_Engine*, const float&, const int&, const bool&);
	void move(const float&, const int&, const bool&);
	void checkAggro(I_Engine*);
	void checkCharge(I_Engine*, const float&, const int&, const bool&);
	void checkSwing(const float&);
	void getHurt(const int&);
	void getHealed(const int&);
};