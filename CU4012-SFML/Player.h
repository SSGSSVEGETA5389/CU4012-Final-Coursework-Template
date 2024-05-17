#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
class Player : public GameObject
{
	int health;
	int speed; 
	sf::Texture HippoSpriteSheet;
	Animation walk; 
	Animation duck; 
	Animation* currentAnimation; 
	int numberOfCollectables; 

public: 

	Player(); 
	void handleInput(float dt) override; 
	void update(float dt); 

	void AddCollectable(int c)
	{
		numberOfCollectables += c;
	}

	int getCollectables()

	{
		return numberOfCollectables;

	}

};

