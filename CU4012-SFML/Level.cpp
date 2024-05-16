#include "Level.h"
#include "Background.h"
#include "Player.h"
#include "Menu.h"
#include "TileEditor.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs,sf::View* v, World* w, TileManager* tm)
{
	window = hwnd;
	input = in;
	gameState = gs;
	view = v;
	world = w;	
	tileManager = tm;
	audioManager = new AudioManager();
	

	player.setInput(input); 
	player.setAudio(audioManager);

	world->AddGameObject(player);

	audioManager->addMusic("Level_Music.ogg", "bgm");
	audioManager->addSound("Jump_Sound.ogg", "jump");
	audioManager->playMusicbyName("bgm");

	// Background 

	for (size_t i = 0; i < 3; i++)
	{
		bg[i].setScale(3, 3);
		bg[i].setPosition(bg[i].getSize().x * i, 0);
	}
	e1.setCustomTexture("gfx/Enemy.png");

	// Write a for loop for setting the enemyArray variables texture 
	for (size_t i = 0; i < 4; i++)
	{
		enemyArray[i].setCustomTexture("gfx/Enemy.png");
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

	player.handleInput(dt); 

}

// Update game objects
void Level::update(float dt)
{

	//Move the view to follow the player
	view->setCenter(view->getCenter().x, 360);
	
	sf::Vector2f playerPosition = player.getPosition();
	float newX = std::max(playerPosition.x, view->getSize().x / 2.0f);
	view->setCenter(newX, view->getCenter().y);
	window->setView(*view);

	for (int i = 0; i < 4; i++)
	{
		if (enemyArray[i].CollisionWithTag("Player"))
		{
			std::cout << enemyArray[i].getCollisionDirection() << std::endl;
			if (enemyArray[i].getCollisionDirection() == "Up")
			{
				enemyArray[i].setAlive(false);
				world->RemoveGameObject(enemyArray[i]);
			}
			else
			{
				std::cout << "Player hit enemy from the side\n";
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
		tileManager.RemoveCollectable(); // Remove the collectable

		// Update the CollectablesCollectedText to display the new number of rings collected
		int collectableCount = Player.getCollectables(); // Assume p1 is the player object and has the getCollectablesCount method
		CollectablesCollectedText.setString("Collected: " + std::to_string(collectableCount));
	}

	//When the player goes over a certain position on the Y axis (Downwards), this should trigger a game over screen.
	if (Player.getPosition().y > 1500)
	{
		Reset();
		gameState->setCurrentState(State::GAMEOVER);
	}

	//When the player goes over a certain position on the X axis (Right), this should trigger the winning screen.

	if (Player.getPosition().x > 3200)
	{
		Reset();
		gameState->setCurrentState(State::WINNER);
	}
}

// Render level
void Level::render()
{
	if (gameState->getCurrentState() == State::LEVEL)
	{
		tileManager->render(false);
	}
	
	window->draw(player);
}


void Level::adjustViewToWindowSize(unsigned int width, unsigned int height) 
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view->setSize(static_cast<float>(width), static_cast<float>(height));
	view->setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}