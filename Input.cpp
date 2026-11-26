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
            playerPosition += 15;
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
            playerPosition -= 15;
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
    }
	mousePosRelativeToTopLeftCornerOfWindow = ascertainMousePosRelativeToTopLeftCornerOfWindow(Mouse::getPosition());
};

Vector2i C_Engine::ascertainMousePosRelativeToTopLeftCornerOfWindow(const Vector2i& _mousePos) const {
	return {(int)(_mousePos.x - window.getPosition().x -  8),
			(int)(_mousePos.y - window.getPosition().y - 30)};
};

void C_Engine::resetViewsAndRenderBounds() {
    gameWorldView. reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    foregroundView.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    guiView.       reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    xRenderBoundary = (int)(gameWorldView.getSize().x / 2) + 750;
};