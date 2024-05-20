#include "Enemy.h"

Enemy::Enemy()
{
	health = 100; 
	speed = 150; 
	velocity.x = 150;
	
	if (!texture.loadFromFile("gfx/enemyWalkCycle.png"))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);

	setSize(sf::Vector2f(24*3, 34*3));
	//setPosition(500, 500);
	setCollisionBox(getPosition(), getSize());
	setTag("Enemy"); 
	setMass(100.f); 

	walk.addFrame(sf::IntRect(0, 0, 24, 34));
	walk.addFrame(sf::IntRect(22, 0, 24, 34));
	walk.addFrame(sf::IntRect(46, 0, 24, 34));
	walk.addFrame(sf::IntRect(68, 0, 24, 34));
	walk.addFrame(sf::IntRect(92, 0, 24, 34));
	walk.addFrame(sf::IntRect(114, 0, 24, 34));

	walk.setFrameSpeed(1.f / 10.f);


}

void Enemy::update(float dt)
{
	setTextureRect(walk.getCurrentFrame());
	if (velocity.x < 0)
	{
		walk.setFlipped(true);
	}
	if (velocity.x > 0)
	{
		walk.setFlipped(false);
	}
	walk.animate(dt);
}

