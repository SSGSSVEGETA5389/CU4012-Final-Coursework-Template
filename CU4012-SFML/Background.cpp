#include "Background.h"

Background::Background()
{
    if (!backgroundTex.loadFromFile("gfx/Background.png")) {
        // Handle error loading texture
    }

    setTexture(&backgroundTex);
    setSize(sf::Vector2f(698, 478));

    // Set initial position
    setPosition(0, 0);
}

Background::~Background()
{
}
