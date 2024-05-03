#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Player : public GameObject
{
	int speed; 
	sf::Texture HippoSpriteSheet;
	Animation walk; 
	Animation duck; 
	Animation* currentAnimation; 

public: 

	Player(); 
	void handleInput(float dt) override; 

};

