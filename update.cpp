#include "C_Engine.hpp"

void C_Engine::update(const float& _elapsedSeconds) {
	SoundManager::update();
	countDownCooldownsAndTimewindows(_elapsedSeconds);
	if (playerFacingRight)
		designatedKnightPosition = playerPosition + 550;
	else
		designatedKnightPosition = playerPosition - 550;
	updateGoblins(_elapsedSeconds);
	knight->update(this, _elapsedSeconds, designatedKnightPosition, playerFacingRight);
};

void C_Engine::updateGoblins(const float& _elapsedSeconds) {
    for (std::vector<Goblin*>::iterator it{goblins.begin()}; it != goblins.end(); it++) {
		Goblin* goblin{*it};
        goblin->update(this, _elapsedSeconds, designatedKnightPosition, playerFacingRight);
    }
};

void C_Engine::countDownCooldownsAndTimewindows(const float& _seconds) {
	countDownBy(doubleTapAButtonTimeWindow, _seconds);
	countDownBy(doubleTapDButtonTimeWindow, _seconds);
};