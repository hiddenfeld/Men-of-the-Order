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
            playerFacingRight = true;
            playerPosition += 15;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            playerFacingRight = false;
            playerPosition -= 15;
        }
    }
	mousePosRelativeToTopLeftCornerOfWindow = ascertainMousePosRelativeToTopLeftCornerOfWindow(Mouse::getPosition());
};

Vector2i C_Engine::ascertainMousePosRelativeToTopLeftCornerOfWindow(const Vector2i& _mousePos) const {
	return {(int)(_mousePos.x - window.getPosition().x -  8),
			(int)(_mousePos.y - window.getPosition().y - 30)};
};

void C_Engine::resetViewsAndRenderBounds() {
    gameWorldView. reset(FloatRect( 0, 0, window.getSize().x, window.getSize().y));
    foregroundView.reset(FloatRect( 0, 0, window.getSize().x, window.getSize().y));
    guiView.       reset(FloatRect( 0, 0, window.getSize().x, window.getSize().y));
    xRenderBoundary = gameWorldView.getSize().x / 2 + 750.0;
};