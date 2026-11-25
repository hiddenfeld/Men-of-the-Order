#include "C_Engine.hpp"

void C_Engine::drawGUI() {
    window.setView(guiView);
    cursorSprite.setColor(sf::Color::White);
    
    for (std::vector<InteractibleDoodad*>::iterator it{interactibleDoodads.begin()}; it != interactibleDoodads.end(); it++) {
		InteractibleDoodad* id{*it};
        if (   std::abs(relativeMousePosition.x - id->position) < 130
            && relativeMousePosition.y > 300
            && relativeMousePosition.y < 575)
        {
            if (altModeActive)
                drawInteractibleDoodadInfoWindow(id);
            cursorSprite.setColor(sf::Color::Blue);
        }
    }

    for (std::vector<Goblin*>::iterator it{goblins.begin()}; it != goblins.end(); it++) {
		Goblin* goblin{*it};
        if (   std::abs(relativeMousePosition.x - goblin->position) < 80
            && relativeMousePosition.y > 400
            && relativeMousePosition.y < 600)
        {
            if (altModeActive)
                drawGoblinInfoWindow(goblin);
            cursorSprite.setColor(sf::Color::Red);
        }
    }

    if (   std::abs(relativeMousePosition.x - knight->position) < 100
        && relativeMousePosition.y > 300
        && relativeMousePosition.y < 600)
    {
        if (altModeActive)
            drawKnightInfoWindow(knight);
        cursorSprite.setColor(sf::Color::Green);
    }

    if (altModeActive) {
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setPosition({0.0f, 0.0f});
        rectangle.setSize({40.0f, 35.0f});
        window.draw(rectangle);
        helpText.setPosition({0.0f, 0.0f});
        helpText.setString("Alt");
        helpText.setFillColor(sf::Color::Blue);
        window.draw(helpText);
    }
    cursorSprite.setPosition((Vector2f)mousePosRelativeToTopLeftCornerOfWindow);
    window.draw(cursorSprite);
    if (debugModeEnabled) {
        debugText.setPosition((Vector2f)mousePosRelativeToTopLeftCornerOfWindow);
        debugText.setString("(" + std::to_string(mousePosRelativeToTopLeftCornerOfWindow.x) + " | " + std::to_string(mousePosRelativeToTopLeftCornerOfWindow.y) + ")");
        window.draw(debugText);
        debugText.setPosition(0.0f, 20.0f);
        debugText.setString("relativeMousePosition: (" + std::to_string(relativeMousePosition.x) + " | " + std::to_string(relativeMousePosition.y) + ")");
        window.draw(debugText);
    }
};

void C_Engine::drawInteractibleDoodadInfoWindow(InteractibleDoodad* _id) {
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 15), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 15)});
    rectangle.setSize({350.0f, 200.0f});
    window.draw(rectangle);
    helpText.setString(convertInteractibleDoodadTypeToString(_id->interactibleDoodadType));
    helpText.setFillColor(sf::Color::Blue);
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 15)});
    window.draw(helpText);
    helpText.setString("ResourceType: " + convertResourceTypeToString(_id->resourceType));
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 50)});
    window.draw(helpText);
    helpText.setString("Quantity: " + std::to_string(_id->remainingHarvestAmount));
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 85)});
    window.draw(helpText);
};

void C_Engine::drawGoblinInfoWindow(Goblin* _goblin) {
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 15), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 15)});
    rectangle.setSize({320.0f, 300.0f});
    window.draw(rectangle);
    helpText.setString("Goblin");
    helpText.setFillColor(sf::Color::Red);
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 15)});
    window.draw(helpText);
    helpText.setString("HP: " + std::to_string(_goblin->hp) + " / " + std::to_string(_goblin->maxHp));
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 50)});
    window.draw(helpText);
    helpText.setString("Dmg: " + std::to_string(_goblin->attackDamage));
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 85)});
    window.draw(helpText);
    helpText.setString("Chance to hit: " + std::to_string(_goblin->chanceToHit) + "%");
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 120)});
    window.draw(helpText);
};

void C_Engine::drawKnightInfoWindow(Knight* _knight) {
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 15), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 15)});
    rectangle.setSize({320.0f, 300.0f});
    window.draw(rectangle);
    helpText.setString("Knight");
    helpText.setFillColor(sf::Color::Green);
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y +  15)});
    window.draw(helpText);
    helpText.setString("HP: " + std::to_string(_knight->hp) + " / " + std::to_string(_knight->maxHp));
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y +  50)});
    window.draw(helpText);
    helpText.setString("Dmg: " + std::to_string(_knight->attackDamage));
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y +  85)});
    window.draw(helpText);
    helpText.setString("Chance to hit: " + std::to_string(_knight->chanceToHit) + "%");
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 120)});
    window.draw(helpText);
    helpText.setString("Chance to block: " + std::to_string(_knight->chanceToBlock) + "%");
    helpText.setPosition({(float)(mousePosRelativeToTopLeftCornerOfWindow.x + 25), (float)(mousePosRelativeToTopLeftCornerOfWindow.y + 155)});
    window.draw(helpText);
};