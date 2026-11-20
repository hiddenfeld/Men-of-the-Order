#include "C_Engine.hpp"

void C_Engine::update(const float& _elapsedSeconds) {
	SoundManager::update();
	if (playerFacingRight)
		designatedKnightPosition = playerPosition + 550;
	else
		designatedKnightPosition = playerPosition - 550;
	goblin.update(this, _elapsedSeconds, designatedKnightPosition, playerFacingRight);
	knight.update(this, _elapsedSeconds, designatedKnightPosition, playerFacingRight);
};
