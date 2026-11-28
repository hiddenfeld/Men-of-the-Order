#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <direct.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <set>
#include <sys/stat.h>
#include <memory>
#include "I_Engine.hpp"
#include "Atlas.hpp"
#include "CountDownByUtility.cpp"
#include "EnumsToStringUtility.cpp"
#include "Goblin.hpp"
#include "InteractibleDoodad.hpp"
#include "Knight.hpp"
#include "Pythagoras.cpp"
#include "RandomIntFromZeroTo.cpp"
#include "SpellOrb.hpp"
#include "VectorMathUtility.cpp"
#include "Worker.hpp"

using namespace sf;

class C_Engine : public I_Engine {
    RenderWindow window;
    View gameWorldView;
    View foregroundView;
    View guiView;
    Texture dirtRoadInTheWoodsSpritesheet;
    Sprite dirtRoadInTheWoodsSprite;
    Texture goblinSpritesheet;
    Sprite goblinSprite;
    Texture knightSpritesheet;
    Sprite knightSprite;
    Texture cursorSpritesheet;
    Sprite cursorSprite;
    Texture bushSpritesheet;
    Sprite bushSprite;
    Texture logSpritesheet;
    Sprite logSprite;
    Texture treeSpritesheet;
    Sprite treeSprite;
    Texture squireSpritesheet;
    Sprite squireSprite;
    Texture workerSpritesheet;
    Sprite workerSprite;

    int xRenderBoundary;
    std::vector<int> backgroundTreePositions;
    std::vector<int> foregroundTreePositions;
    std::vector<InteractibleDoodad*> interactibleDoodads;

    bool playerFacingRight;
    int playerPosition;
    float playerSpellOrbLaunchCooldown{0.0f};
    float playerSpellOrbLaunchSpeed{1.0f};
    int designatedKnightPosition;
    int designatedWorkerPosition;

    std::vector<Goblin*> goblins;
    Knight* knight;
    Worker* worker;

    std::vector<SpellOrb*> spellOrbs;

    Font arialFont;
    sf::Text debugText;
    sf::Text helpText;
    sf::RectangleShape rectangle;

    bool aButtonPressed{false};
    bool dButtonPressed{false};
    bool leftMouseButtonDown{false};
    bool rightMouseButtonDown{false};
    float doubleTapAButtonTimeWindow{0.0f};
    float doubleTapDButtonTimeWindow{0.0f};
    bool debugModeEnabled;
    bool f2Enabled;
    bool altModeActive;

    sf::Vector2i relativeMousePosition;
    void input();
    Vector2i mousePosRelativeToTopLeftCornerOfWindow;
	Vector2i ascertainMousePosRelativeToTopLeftCornerOfWindow(const Vector2i&) const;
    void resetViewsAndRenderBounds();
    void inputTriggersSpellOrbShot();

    void update(const float&);
    void countDownCooldownsAndTimewindows(const float&);
    void updateSpellOrbs(const float&);
    void updateGoblins(const float&);

    void draw();
    void drawGameWorld();
    void drawLevelBackground();
    void drawInteractibleDoodads();
    void drawInteractibleDoodad(InteractibleDoodad*);
    void drawUnits();
    void drawGoblins();
    void drawGoblin(Goblin*);
    void drawKnight();
    void drawSquire();
    void drawWorker();
    void drawSpellOrbs();
    void drawSpellOrb(SpellOrb*);
    void drawLevelForeground();
    void drawGUI();
    void drawInteractibleDoodadInfoWindow(InteractibleDoodad*);
    void drawGoblinInfoWindow(Goblin*);
    void drawKnightInfoWindow(Knight*);
    void drawWorkerInfoWindow(Worker*);
    int calculateMissingHealthPercentile(const int&, const int&);

    void clearLevel();
    void generateForestLevel();

public:
    C_Engine();

    void start();
    void save();
    std::vector<Goblin*>* getGoblins();
    I_Unit* getKnight();
    I_Unit* getWorker();
};
