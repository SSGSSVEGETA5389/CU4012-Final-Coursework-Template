#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "Framework/World.h"
#include "Framework/TileManager.h"
#include "Framework/AudioManager.h"
#include "Player.h"
#include "Background.h"
#include <string>
#include <iostream>
#include "Enemy.h"

class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs,sf::View* view ,World* w, TileManager* tm);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();
	void adjustViewToWindowSize(unsigned int width, unsigned int height);
	void Reset();
	

private:
	// Default variables for level class.


	//Player
	Player Player; 
	sf::Text CollectablesCollectedText;

	//Enemy

	Enemy e1; 
	int NumberOfEnemies = 10; 
	Enemy enemyArray[4]; 


	//Background

	Background bg[5];

	//Font 

	sf::Font font; 

	//Pause screen stuff

	sf::RenderWindow& window;
	

	
	
};



	
