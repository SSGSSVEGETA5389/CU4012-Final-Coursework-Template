#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "Framework/World.h"
#include "Framework/TileManager.h"
#include <string>
#include <iostream>

class TileEditor
{
public:
	TileEditor(sf::RenderWindow* hwnd, Input* in, GameState* game, sf::View* view, World* w, TileManager* tm);
	~TileEditor();

	void handleInput(float dt);
	void Init();
	void update(float dt);
	void render();
	void moveView(float dt);
private:
	// Default variables for level class.
	sf::RenderWindow* window;
	sf::View* view;
	Input* input;
	GameState* gameState;
	World* world;

	TileManager* tileManager;
	sf::Font font;

	sf::Vector2f originalViewSize;

	//moving the view variables
	float currentZoomLevel = 1.0f;
	sf::Vector2i lastMousePos;
	bool isDragging = false;
	sf::Texture mouseCurosorTex;
	sf::Sprite mouseCurosorGrab;

};