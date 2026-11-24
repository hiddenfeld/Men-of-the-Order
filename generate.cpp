#include "C_Engine.hpp"

void C_Engine::clearLevel() {
	backgroundTreePositions.clear();
};

void C_Engine::generateForestLevel() {
	for (int i{0}; i <= 40; i++) {
		backgroundTreePositions.push_back((i - 20) * 1100);
	}
	for (int i{-5}; i <= 5; i++) {
		if (std::abs(i) > 1) {
			InteractibleDoodad* doodad{new InteractibleDoodad(i * 4050, (InteractibleDoodadType)randomIntFromZeroTo(1), 500)};
			interactibleDoodads.push_back(doodad);
		}
	}
	for (int i{0}; i <= 40; i++) {
		foregroundTreePositions.push_back((i - 20) * 2050);
	}
};