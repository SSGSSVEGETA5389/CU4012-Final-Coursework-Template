#pragma once
#include "Framework/GameObject.h"
#include <iostream>
#include <string>
class Enemy : public GameObject
{
	int health; 
	float speed; 
	sf::Texture texture; 

public: 

	Enemy(); 

	void update(float dt); 

	void setCustomTexture(std::string path);
};

