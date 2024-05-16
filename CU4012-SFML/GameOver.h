#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include"Framework/Collision.h"
#include "Framework/UI.h"
#include <string>
#include <iostream>
#include"Level.h"



class GameOver
{
public:
	GameOver(sf::RenderWindow* hwnd, Input* in, GameState* game);
	~GameOver();


	int handleInput(float dt);
	void update(float dt);
	void render();
	void MoveUp();
	void MoveDown();
	void updateVisualFeedback();
	int GetPressedItem() { return selectedItem; }


	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;

	int selectedItem;
	sf::Font UIfont;
	sf::Font titleFont;

	sf::Text Title;
	UI UIText[2];

	void beginDraw();
	void endDraw();



	sf::Sprite gameOver_sprite;
	sf::Texture gameOver_texture;

	sf::Vector2i MousePos;

	bool DebugRender;

	bool mouseOverAnyItem;

};

