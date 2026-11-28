#include "C_Engine.hpp"

void C_Engine::input() {
    sf::Event event;
    window.pollEvent(event);
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if (event.type == sf::Event::Resized) {
        resetViewsAndRenderBounds();
    }
    if (window.hasFocus()) {
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (!dButtonPressed) {
                if (doubleTapDButtonTimeWindow > 0.0f)
            playerFacingRight = true;
                doubleTapDButtonTimeWindow = 0.35f;
            }
            dButtonPressed = true;
            bool collisionToTheRightDetected{false};
            for (std::vector<Goblin*>::iterator it{goblins.begin()}; it != goblins.end(); it++) {
		        I_Unit* goblin{*it};
		        if (goblin->hp > 0) {
			        int distanceBetweenThisAndTarget{std::abs(playerPosition - goblin->position)};
			        if (   distanceBetweenThisAndTarget <= 100 + goblin->attackRange - 50
                        && goblin->position > playerPosition)
				        collisionToTheRightDetected = true;
		        }
	        }
	        if (!collisionToTheRightDetected)
                playerPosition += 12;
        } else {
            dButtonPressed = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (!aButtonPressed) {
                if (doubleTapAButtonTimeWindow > 0.0f)
            playerFacingRight = false;
                doubleTapAButtonTimeWindow = 0.35f;
            }
            aButtonPressed = true;
            bool collisionToTheLeftDetected{false};
            for (std::vector<Goblin*>::iterator it{goblins.begin()}; it != goblins.end(); it++) {
		        I_Unit* goblin{*it};
		        if (goblin->hp > 0) {
			        int distanceBetweenThisAndTarget{std::abs(playerPosition - goblin->position)};
			        if (   distanceBetweenThisAndTarget <= 100 + goblin->attackRange - 50
                        && goblin->position < playerPosition)
				        collisionToTheLeftDetected = true;
		        }
	        }
	        if (!collisionToTheLeftDetected)
                playerPosition -= 12;
        } else {
            aButtonPressed = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::LAlt)) {
            altModeActive = true;
        } else {
            altModeActive = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::F2)) {
            if (f2Enabled) {
                if (debugModeEnabled)
                    debugModeEnabled = false;
                else
                    debugModeEnabled = true;
            }
            f2Enabled = false;
        } else {
            f2Enabled = true;
        }
        if (Mouse::isButtonPressed(Mouse::Left))
            leftMouseButtonDown = true;
        else
            leftMouseButtonDown = false;
        if (Mouse::isButtonPressed(Mouse::Right))
            rightMouseButtonDown = true;
        else
            rightMouseButtonDown = false;
        if (   leftMouseButtonDown
            && rightMouseButtonDown)
            inputTriggersSpellOrbShot();
    }
	mousePosRelativeToTopLeftCornerOfWindow = ascertainMousePosRelativeToTopLeftCornerOfWindow(Mouse::getPosition());
};

Vector2i C_Engine::ascertainMousePosRelativeToTopLeftCornerOfWindow(const Vector2i& _mousePos) const {
	return {(int)(_mousePos.x - window.getPosition().x -  8),
			(int)(_mousePos.y - window.getPosition().y - 30)};
};

void C_Engine::resetViewsAndRenderBounds() {
    gameWorldView. reset(FloatRect(0.0f, 0.0f, (float)(window.getSize().x), (float)(window.getSize().y)));
    foregroundView.reset(FloatRect(0.0f, 0.0f, (float)(window.getSize().x), (float)(window.getSize().y)));
    guiView.       reset(FloatRect(0.0f, 0.0f, (float)(window.getSize().x), (float)(window.getSize().y)));
    xRenderBoundary = (int)(gameWorldView.getSize().x / 2) + 750;
};

void C_Engine::inputTriggersSpellOrbShot() {
    if (playerSpellOrbLaunchCooldown <= 0.0f) {
        sf::Vector2f spellOrbMovement{(float)(relativeMousePosition.x) - (float)playerPosition,
                                      (float)(relativeMousePosition.y) - 400.0f};
        spellOrbs.push_back(new SpellOrb({(float)playerPosition, gameWorldView.getCenter().y},
                                         lengthenVector(normalizeVector(spellOrbMovement), 600.0f),
                                         5.0f));
        playerSpellOrbLaunchCooldown = playerSpellOrbLaunchSpeed;
        SoundManager::playSound({SoundOrigin::SpellOrb, SoundReason::Spawn}, 3000.0f);
    }
};