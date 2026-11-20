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
#include "Goblin.hpp"
#include "Knight.hpp"
#include "RandomIntFromZeroTo.cpp"
#include "Pythagoras.cpp"

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
    Texture treeSpritesheet;
    Sprite treeSprite;
    Texture squireSpritesheet;
    Sprite squireSprite;

    int xRenderBoundary;
    std::vector<int> backgroundTreePositions;
    std::vector<int> foregroundTreePositions;

    bool playerFacingRight;
    int playerPosition;
    int designatedKnightPosition;

    Goblin goblin;
    Knight knight;

    void input();
    Vector2i mousePosRelativeToTopLeftCornerOfWindow;
	Vector2i ascertainMousePosRelativeToTopLeftCornerOfWindow(const Vector2i&) const;
    void resetViewsAndRenderBounds();
    void update( const float& );
    void draw();
    void drawGUI();
    void drawGameWorld();
    void drawLevelBackground();
    void drawUnits();
    void drawGoblin();
    void drawKnight();
    void drawSquire();
    void drawLevelForeground();
    int calculateMissingHealthPercentile(const int&, const int&);

    void clearLevel();
    void generateForestLevel();

public:
    C_Engine();

    void start();
    void save();
    I_Unit* getGoblin();
    I_Unit* getKnight();
};
