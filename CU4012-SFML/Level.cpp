#include "Level.h"
#include "Background.h"
#include "Player.h"
#include "Menu.h"
#include "TileEditor.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, sf::View* v, World* w, TileManager* tm)
{
	window = hwnd;
	input = in;
	gameState = gs;
	view = v;
	world = w;
	tileManager = tm;
	audioManager = new AudioManager();

	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "error loading font" << std::endl;
	};

	Player.setInput(input);
	Player.setAudio(audioManager);

	world->AddGameObject(Player);

	audioManager->addMusic("sfx/Level_Music.ogg", "bgm");
	audioManager->addSound("sfx/Jump_Sound.ogg", "jump");
	audioManager->playMusicbyName("bgm");

	// Background 

	for (size_t i = 0; i < 3; i++)
	{
		bg[i].setPosition(bg[i].getSize().x * i, 0);
		bg[i].setScale(3, 3);
	}

	// Write a for loop for setting the enemyArray variables texture 
	for (size_t i = 0; i < 4; i++)
	{
		//enemyArray[i].setCustomTexture("gfx/Enemy.png");
		enemyArray[i].setAlive(true);
		world->AddGameObject(enemyArray[i]);

	}

	//Enemy one 
	enemyArray[0].setPosition(100, 70);
	enemyArray[0].setVelocity(100, 0);

	//Enemy two
	enemyArray[1].setPosition(400, 400);
	enemyArray[1].setVelocity(100, 0);

	//Enemy three 
	enemyArray[2].setPosition(800, 500);
	enemyArray[2].setVelocity(100, 0);

	//Enemy four
	enemyArray[3].setPosition(850, 600);
	enemyArray[3].setVelocity(100, 0);

	//Collectables Collected Text
	CollectablesCollectedText.setFont(font);
	CollectablesCollectedText.setCharacterSize(24);
	CollectablesCollectedText.setFillColor(sf::Color::Green);
	CollectablesCollectedText.setPosition(window->getSize().x, 0);
	CollectablesCollectedText.setString("Collected: ");

}

Level::~Level()
{
	//Making pointers null
	window = nullptr;
	input = nullptr;
	gameState = nullptr;
	view = nullptr;
	world = nullptr;
	tileManager = nullptr;
	if (audioManager != nullptr) {
		delete audioManager;
		audioManager = nullptr;
	}
}

void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}
	if (input->isKeyDown(sf::Keyboard::Tab))
	{
		input->setKeyUp(sf::Keyboard::Tab);
		gameState->setCurrentState(State::TILEEDITOR);
	}
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		gameState->setCurrentState(State::PAUSE);

	}

	Player.handleInput(dt);

}

// Update game objects
void Level::update(float dt)
{
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	CollectablesCollectedText.setPosition(view->getCenter().x - viewSize.x / 14, view->getCenter().y - viewSize.y / 2);



	for (int i = 0; i < 4; i++)
	{
		if (enemyArray[i].CollisionWithTag("Player"))
		{
			std::cout << enemyArray[i].getCollisionDirection() << std::endl;
			if (enemyArray[i].getCollisionDirection() == "Down")
			{
				enemyArray[i].setAlive(false);
				world->RemoveGameObject(enemyArray[i]);
			}
			else
			{
				//std::cout << "Player hit enemy from the side\n";
				Player.setPosition(100, 100);
			}
		}
		else if (enemyArray[i].CollisionWithTag("Wall"))
		{
			enemyArray[i].setVelocity(-enemyArray[i].getVelocity().x, enemyArray[i].getVelocity().y);
		}
	}
	if (Player.CollisionWithTag("Collectable"))
	{
		// Player is Colliding with Collectable
		Player.AddCollectable(1); // Increment Collectable count
		tileManager->RemoveCollectable(); // Remove the collectable

		// Update the CollectablesCollectedText to display the new number of rings collected
		int collectableCount = Player.getCollectables(); // Assume p1 is the player object and has the getCollectablesCount method
		CollectablesCollectedText.setString("Collected: " + std::to_string(collectableCount));
	}

	//When the player goes over a certain position on the Y axis (Downwards), this should trigger a game over screen.
	if (Player.getPosition().y > 1500)
	{
		//Reset(); 
		gameState->setCurrentState(State::GAMEOVER);
	}

	//When the player goes over a certain position on the X axis (Right), this should trigger the winning screen.

	if (Player.getPosition().x > 3200)
	{
		//Reset();
		gameState->setCurrentState(State::WINNER);
	}



	//Move the view to follow the player
	view->setCenter(view->getCenter().x, 520);

	sf::Vector2f playerPosition = Player.getPosition();
	float newX = std::max(playerPosition.x, view->getSize().x / 2.0f);
	view->setCenter(newX, view->getCenter().y);
	window->setView(*view);
}

// Render level
void Level::render()
{

	for (size_t i = 0; i < 3; i++)
	{
		window->draw(bg[i]);
	}

	if (gameState->getCurrentState() == State::LEVEL)
	{
		tileManager->render(false);
	}
	window->draw(Player);
	for (size_t i = 0; i < 4; i++)
	{
		if (enemyArray[i].isAlive())
		{
			window->draw(enemyArray[i]);
		}
	}
	window->draw(CollectablesCollectedText);

}


void Level::adjustViewToWindowSize(unsigned int width, unsigned int height)
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view->setSize(static_cast<float>(width), static_cast<float>(height));
	view->setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}


