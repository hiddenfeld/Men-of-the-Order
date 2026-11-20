#include "C_Engine.hpp"

void C_Engine::drawGUI() {
    window.setView(guiView);

    cursorSprite.setPosition((Vector2f)mousePosRelativeToTopLeftCornerOfWindow);
    window.draw(cursorSprite);
};