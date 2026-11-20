#pragma once
#include <cmath>
#include "I_Engine.hpp"
#include "I_Unit.hpp"
#include "OrderType.hpp"
#include "SoundManager.hpp"

struct Knight : public I_Unit {
	bool learnedBlock;
	float currentBlockCooldown;
	float blockCooldown;

	void update(I_Engine*, const float&, const int&, const bool&);
	void move(const float&, const int&, const bool&);
	void checkAggro(I_Engine*);
	void checkCharge(I_Engine*, const float&, const int&, const bool&);
	void checkSwing(const float&);
	void getHurt(const int&);
	void getHealed(const int&);
};