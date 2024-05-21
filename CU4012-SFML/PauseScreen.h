#pragma once
#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class PauseScreen {
public:
    PauseScreen(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void update();
    bool getIsPaused() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text pauseText;
    bool isPaused;
};

#endif // PAUSESCREEN_H
