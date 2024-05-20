#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include"Framework/Collision.h"
#include "Framework/UI.h"
#include <string>
#include <iostream>
#include"Level.h"
class WinningScreen : public GameObject
{
public:
	WinningScreen(sf::RenderWindow* hwnd, Input* in, GameState* game);
	~WinningScreen();


	void handleInput(float dt);
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



	sf::Sprite winner_sprite;
	sf::Texture winner_texture;

	sf::Vector2i MousePos;

	bool DebugRender;

	bool mouseOverAnyItem;

};

