#include "Enemy.h"

Enemy::Enemy()
{
	health = 100; 
	speed = 150; 
	velocity.x = 150;


	setSize(sf::Vector2f(100, 100));
	setPosition(500, 500);
	setCollisionBox(getPosition(), getSize());
	setTag("Enemy"); 
	setMass(100.f); 

}

void Enemy::update(float dt)
{


}

void Enemy::setCustomTexture(std::string path)
{
	if (!texture.loadFromFile(path))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);

}
