#pragma once
#include <iostream>
#include "I_Engine.hpp"
#include "I_Unit.hpp"
#include "SoundManager.hpp"
#include "Goblin.hpp"

struct Goblin;

struct Worker : public I_Unit {
	Worker(const int&, const int&, const bool&, const int&, const int&, const OrderType&, const int&, const int&, I_Unit*, const float&, const float&, const int&, const int&);

	void update(I_Engine*, const float&, const int&, const bool&);
	void countDownCountdowns(const float&);
	void move(const float&, const int&, const bool&);
	bool checkCollision(I_Engine*);
	void checkAggro(I_Engine*);
	void checkCharge(I_Engine*, const float&, const int&, const bool&);
	void checkSwing(const float&);
	void getHurt(const int&);
	void getHealed(const int&);
};