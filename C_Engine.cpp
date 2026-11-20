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

    Atlas::load();

    playerFacingRight = false;
    clearLevel();
    generateForestLevel();

    playerPosition = 0;
    knight.position = 0;
    knight.movementSpeed = 300;
    knight.facingRight = false;
    knight.hp    =  8;
    knight.maxHp = 10;
    knight.currentBlockCooldown = 0.0f;
    knight.blockCooldown = 2.0f;
    knight.learnedBlock = true;
    knight.attackRange = 110;
    knight.aggroRange = 600;
    knight.attackTarget = NULL;
    knight.swingCountdown = 0.0f;
    knight.swingSpeed = 1.0f;
    knight.strikeRecoveryCountdown = 1.0f;
    knight.strikeRecoverySpeed = 2.0f;
    knight.attackDamage = 2;
    goblin.position = -1600;
    goblin.spawnPosition = -1600;
    goblin.patrolPosition1 = -800;
    goblin.patrolPosition2 = -2400;
    goblin.movementSpeed = 300;
    goblin.facingRight = false;
    goblin.hp    = 6;
    goblin.maxHp = 6;
    goblin.activeOrder = OrderType::Patrol;
    goblin.attackRange = 90;
    goblin.aggroRange = 900;
    goblin.attackTarget = NULL;
    goblin.swingCountdown = 0.0f;
    goblin.swingSpeed = 0.8f;
    goblin.strikeRecoveryCountdown = 0.0f;
    goblin.strikeRecoverySpeed = 2.7f;
    goblin.attackDamage = 1;
    dirtRoadInTheWoodsSpritesheet.loadFromFile("spritesheets/dirtRoadInTheWoods.jpg");
    dirtRoadInTheWoodsSprite.setTexture(dirtRoadInTheWoodsSpritesheet);
    goblinSpritesheet.loadFromFile("spritesheets/goblin.png");
    goblinSprite.setTexture(goblinSpritesheet);
    knightSpritesheet.loadFromFile("spritesheets/knight.png");
    knightSprite.setTexture(knightSpritesheet);
    cursorSpritesheet.loadFromFile("cursor.png");
    cursorSprite.setTexture(cursorSpritesheet);
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

        input();
        update(elapsedSeconds);
        draw();
    }
};

I_Unit* C_Engine::getGoblin() {
    return &goblin;
};

I_Unit* C_Engine::getKnight() {
    return &knight;
};