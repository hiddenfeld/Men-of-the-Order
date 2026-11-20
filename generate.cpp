#include "C_Engine.hpp"

void C_Engine::clearLevel() {
	backgroundTreePositions.clear();
};

void C_Engine::generateForestLevel() {
	for (int i = 0; i < 40; i++) {
		backgroundTreePositions.push_back((i - 20) * 1000);
	}
	for (int i = 0; i < 40; i++) {
		foregroundTreePositions.push_back((i - 20) * 1700);
	}
};