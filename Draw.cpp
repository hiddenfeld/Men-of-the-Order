#include "C_Engine.hpp"

void C_Engine::draw() {
    window.clear( Color::Black );
    
    drawGameWorld();
    drawGUI();

    window.display();
};