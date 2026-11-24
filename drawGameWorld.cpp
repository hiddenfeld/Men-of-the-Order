#include "C_Engine.hpp"

void C_Engine::drawGameWorld() {
    window.setView(gameWorldView);
    gameWorldView.setCenter((float)playerPosition, (float)400);
    drawLevelBackground();
    drawUnits();
    window.setView(foregroundView);
    foregroundView.setCenter((float)(playerPosition / 3), (float)400);
    drawLevelForeground();
};

void C_Engine::drawLevelBackground() {
    int xBounds{Atlas::spriteBounds.at(SpriteName::DirtRoadInTheWoods).width};
    for (int i {playerPosition / xBounds - 3}; i < playerPosition / xBounds + 3; i++) {
        int x{i * xBounds};
        dirtRoadInTheWoodsSprite.setPosition((float)x, -310.0f);
        window.draw(dirtRoadInTheWoodsSprite);
    }
    for (std::vector<int>::iterator it{backgroundTreePositions.begin()}; it != backgroundTreePositions.end(); it++) {
        treeSprite.setPosition((float)(*it - Atlas::spriteBounds.at(SpriteName::Tree).width / 2), 0.0f);
        if (std::abs(gameWorldView.getCenter().x - *it) < xRenderBoundary)
            window.draw(treeSprite);
    }
}

void C_Engine::drawUnits() {
    drawGoblins();
    drawKnight();
    drawSquire();
};

void C_Engine::drawGoblins() {
    for (std::vector<Goblin*>::iterator it{goblins.begin()}; it != goblins.end(); it++) {
        drawGoblin(*it);
    }
};

void C_Engine::drawGoblin(Goblin* _goblin) {
    int xOffset{0};
    switch (_goblin->activeOrder) {
        case OrderType::Patrol:
            xOffset =   0;
            break;
        case OrderType::Charge:
            xOffset = 160;
            break;
        case OrderType::Swing:
            xOffset = 320;
            break;
        default:
            std::cout << "ERROR in C_Engine.cpp::drawGoblin() on Line #" << __LINE__ << ". Unknown orderType!" << std::endl;
            break;
    }
    if (_goblin->facingRight)
        goblinSprite.setTextureRect({xOffset,   0, Atlas::spriteBounds.at(SpriteName::Goblin).width, Atlas::spriteBounds.at(SpriteName::Goblin).height});
    else
        goblinSprite.setTextureRect({xOffset, 220, Atlas::spriteBounds.at(SpriteName::Goblin).width, Atlas::spriteBounds.at(SpriteName::Goblin).height});
    goblinSprite.setPosition((float)(_goblin->position - 80), 360.0f);
    goblinSprite.setColor({(sf::Uint8)(255 - (int)((float)calculateMissingHealthPercentile(_goblin->hp, _goblin->maxHp) * 1.25f)),
                           (sf::Uint8)(255 - (int)((float)calculateMissingHealthPercentile(_goblin->hp, _goblin->maxHp) * 2.50f)),
                           (sf::Uint8)(255 - (int)((float)calculateMissingHealthPercentile(_goblin->hp, _goblin->maxHp) * 2.50f)),
                                       255});
    window.draw(goblinSprite);
};

void C_Engine::drawKnight() {
    if (knight->facingRight)
        knightSprite.setTextureRect({Atlas::spriteBounds.at(SpriteName::Knight).width, 0, Atlas::spriteBounds.at(SpriteName::Knight).width, Atlas::spriteBounds.at(SpriteName::Knight).height});
    else
        knightSprite.setTextureRect({                                               0, 0, Atlas::spriteBounds.at(SpriteName::Knight).width, Atlas::spriteBounds.at(SpriteName::Knight).height});
    knightSprite.setPosition((float)(knight->position - 130), 300.0f);
    knightSprite.setColor({(sf::Uint8)(255 - (int)((float)calculateMissingHealthPercentile(knight->hp, knight->maxHp) * 1.25f)),
                           (sf::Uint8)(255 - (int)((float)calculateMissingHealthPercentile(knight->hp, knight->maxHp) * 2.50f)),
                           (sf::Uint8)(255 - (int)((float)calculateMissingHealthPercentile(knight->hp, knight->maxHp) * 2.50f)),
                                       255});
    window.draw(knightSprite);
}

void C_Engine::drawSquire() {
    if (playerFacingRight)
        squireSprite.setTextureRect({Atlas::spriteBounds.at(SpriteName::Squire).width, 0, Atlas::spriteBounds.at(SpriteName::Squire).width, Atlas::spriteBounds.at(SpriteName::Squire).height});
    else
        squireSprite.setTextureRect({                                               0, 0, Atlas::spriteBounds.at(SpriteName::Squire).width, Atlas::spriteBounds.at(SpriteName::Squire).height});
    squireSprite.setPosition((float)(playerPosition - 130), 300.0f);
    window.draw(squireSprite);
}

void C_Engine::drawLevelForeground() {
    treeSprite.setScale(1.7f, 1.7f);
    treeSprite.setColor({255, 255, 255, 150});
    for (std::vector<int>::iterator it{foregroundTreePositions.begin()}; it != foregroundTreePositions.end(); it++) {
        treeSprite.setPosition((float)(*it - Atlas::spriteBounds.at(SpriteName::Tree).width / 2), 500.0f);
        if (std::abs(foregroundView.getCenter().x - *it) < xRenderBoundary)
            window.draw(treeSprite);
    }
    window.draw(treeSprite);
    treeSprite.setScale(1.0f, 1.0f);
    treeSprite.setColor({255, 255, 255, 255});
};

int C_Engine::calculateMissingHealthPercentile(const int& _hp, const int& _maxHp) {
    int missingHp{_maxHp - _hp};
    return (missingHp * 100) / _maxHp;
};