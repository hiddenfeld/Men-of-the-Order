#include "C_Engine.hpp"

C_Engine::C_Engine() {
    Vector2f resolution(
        {(float)VideoMode::getDesktopMode().width,
         (float)VideoMode::getDesktopMode().height}
    );
    window.create(
        VideoMode((resolution.x * 3) / 4,
                  (resolution.y * 3) / 4),
        "Men of the Order",
        Style::Default
    );
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
    xRenderBoundary = 750;

    arialFont.loadFromFile("arial.ttf");
    debugText.setFont(arialFont);
    helpText.setFont(arialFont);

    Atlas::load();
    altModeActive = false;
    debugModeEnabled = false;
    f2Enabled = true;
    
    clearLevel();
    generateForestLevel();

    playerFacingRight = false;
    playerPosition = 0;
    knight = new Knight(0, 300, false, 8, 10, OrderType::ProtectFront, 110, 600, NULL, 1.0f, 2.0f, 2, 40, true, 2.0f, 40);
    {   Goblin* goblin{new Goblin(-2000, 800)};
        goblins.push_back(goblin);
    } { Goblin* goblin{new Goblin(-3400, 750)};
        goblins.push_back(goblin);
    } { Goblin* goblin{new Goblin( 2000, 800)};
        goblins.push_back(goblin);
    } { Goblin* goblin{new Goblin( 2500, 600)};
        goblins.push_back(goblin);
    }
    dirtRoadInTheWoodsSpritesheet.loadFromFile("spritesheets/dirtRoadInTheWoods.jpg");
    dirtRoadInTheWoodsSprite.setTexture(dirtRoadInTheWoodsSpritesheet);
    goblinSpritesheet.loadFromFile("spritesheets/goblin.png");
    goblinSprite.setTexture(goblinSpritesheet);
    knightSpritesheet.loadFromFile("spritesheets/knight.png");
    knightSprite.setTexture(knightSpritesheet);
    cursorSpritesheet.loadFromFile("spritesheets/cursor.png");
    cursorSprite.setTexture(cursorSpritesheet);
    bushSpritesheet.loadFromFile("spritesheets/bush.png");
    bushSprite.setTexture(bushSpritesheet);
    logSpritesheet.loadFromFile("spritesheets/log.png");
    logSprite.setTexture(logSpritesheet);
    treeSpritesheet.loadFromFile("spritesheets/tree.png");
    treeSprite.setTexture(treeSpritesheet);
    squireSpritesheet.loadFromFile("spritesheets/squire.png");
    squireSprite.setTexture(squireSpritesheet);
    squireSprite.setTextureRect({0, 0, 260, 295});
};

void C_Engine::start() {
    Clock clock;
    resetViewsAndRenderBounds();
    while (window.isOpen()) {
        Time dt{clock.restart()};
        float elapsedSeconds{dt.asSeconds()};
        if (elapsedSeconds > 0.05f)
            elapsedSeconds = 0.05f;
        relativeMousePosition = {(int)(Mouse::getPosition().x - window.getPosition().x -  8 - (gameWorldView.getSize().x / 2) + gameWorldView.getCenter().x),
                                 (int)(Mouse::getPosition().y - window.getPosition().y - 30 - (gameWorldView.getSize().y / 2) + gameWorldView.getCenter().y)};
        input();
        update(elapsedSeconds);
        draw();
    }
};

std::vector<Goblin*>* C_Engine::getGoblins() {
    return &goblins;
};

I_Unit* C_Engine::getKnight() {
    return knight;
};