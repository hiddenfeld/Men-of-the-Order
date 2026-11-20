#pragma once

struct I_Unit;

struct I_Engine {
	virtual I_Unit* getGoblin() = 0;
	virtual I_Unit* getKnight() = 0;
};