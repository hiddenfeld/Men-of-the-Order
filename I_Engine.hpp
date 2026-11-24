#pragma once
#include <vector>

struct I_Unit;
struct Goblin;

struct I_Engine {
	virtual std::vector<Goblin*>* getGoblins() = 0;
	virtual I_Unit* getKnight() = 0;
};