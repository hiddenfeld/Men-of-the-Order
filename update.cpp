#include "C_Engine.hpp"

void C_Engine::update(const float& _elapsedSeconds) {
	SoundManager::update();
	countDownCooldownsAndTimewindows(_elapsedSeconds);
	if (playerFacingRight)
		designatedKnightPosition = playerPosition + 550;
	else
		designatedKnightPosition = playerPosition - 550;
	updateSpellOrbs(_elapsedSeconds);
	updateGoblins(_elapsedSeconds);
	knight->update(this, _elapsedSeconds, designatedKnightPosition, playerFacingRight);
};

void C_Engine::updateSpellOrbs(const float& _elapsedSeconds) {
	for (unsigned int i{0}; i < spellOrbs.size(); i++) {
		SpellOrb* spellOrb{spellOrbs.at(i)};
        spellOrb->update(_elapsedSeconds);
		if (   spellOrb->timeToLive <= 0.0f
			|| spellOrb->spent) {
			delete(spellOrbs.at(i));
			spellOrbs.at(i) = NULL;
		}
    }
	auto it{remove_if(spellOrbs.begin(), spellOrbs.end(), [&](SpellOrb* _orb){return _orb == NULL;})};
    if (it != spellOrbs.end())
        spellOrbs.erase(it);
};

void C_Engine::updateGoblins(const float& _elapsedSeconds) {
    for (std::vector<Goblin*>::iterator it{goblins.begin()}; it != goblins.end(); it++) {
		Goblin* goblin{*it};
        goblin->update(this, _elapsedSeconds, designatedKnightPosition, playerFacingRight);
    }
};

void C_Engine::countDownCooldownsAndTimewindows(const float& _seconds) {
	countDownBy(playerSpellOrbLaunchCooldown, _seconds);
	countDownBy(doubleTapAButtonTimeWindow, _seconds);
	countDownBy(doubleTapDButtonTimeWindow, _seconds);
};