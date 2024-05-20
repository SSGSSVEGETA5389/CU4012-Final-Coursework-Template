#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include <string>
class Enemy : public GameObject
{
	int health; 
	float speed; 
	sf::Texture texture; 
	Animation walk;

public: 

	Enemy(); 

	void update(float dt); 
};

