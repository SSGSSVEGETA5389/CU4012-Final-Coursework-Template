#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class PauseScreen {
public:
    PauseScreen(sf::RenderWindow& window)
        : window(window), isPaused(false) {
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
        }

        pauseText.setFont(font);
        pauseText.setCharacterSize(50);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setString("Pause Menu\nPress P to Resume");
        pauseText.setPosition(window.getSize().x / 2.0f - pauseText.getGlobalBounds().width / 2.0f,
            window.getSize().y / 2.0f - pauseText.getGlobalBounds().height / 2.0f);
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            isPaused = !isPaused;
        }
    }

    void update() {
        if (isPaused) {
            window.draw(pauseText);
        }
    }

    bool getIsPaused() const {
        return isPaused;
    }

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text pauseText;
    bool isPaused;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pause Menu Example");

    PauseScreen pauseScreen(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            pauseScreen.handleEvent(event);
        }

        window.clear();

        // Update game objects here

        if (!pauseScreen.getIsPaused()) {
            // Update game state only when not paused
        }

        pauseScreen.update();

        window.display();
    }

    return 0;
}
