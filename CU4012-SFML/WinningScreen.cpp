#include "WinningScreen.h"
#include "Menu.h"
#include "Player.h"


WinningScreen::WinningScreen(sf::RenderWindow* hwnd, Input* in, GameState* game)
{
	window = hwnd;
	input = in;
	gameState = game;



	UIfont.loadFromFile("font/PixelTex.ttf");
	titleFont.loadFromFile("font/PixelTex.ttf");

	winner_texture.loadFromFile("gfx/winnerScreen.png");
	winner_sprite.setTexture(winner_texture);
	winner_sprite.setScale(10, 10);



	Title.setFont(titleFont);
	Title.setFillColor(sf::Color::Magenta);
	Title.setString("Well done!");
	Title.setOutlineColor(sf::Color::Black);
	Title.setCharacterSize(70);
	Title.setPosition(500, 50);


	UIText[0].text.setFont(UIfont);
	UIText[0].text.setFillColor(sf::Color::Red);
	UIText[0].text.setString("Play again");
	UIText[0].text.setPosition(sf::Vector2f(600, 120));
	UIText[0].setCollisionBox(sf::FloatRect(600, 120, 100, 30));



	UIText[1].text.setFont(UIfont);
	UIText[1].text.setFillColor(sf::Color::White);
	UIText[1].text.setString("Exit");
	UIText[1].text.setPosition(sf::Vector2f(600, 150));
	UIText[1].setCollisionBox(sf::FloatRect(600, 160, 100, 30));

	selectedItem = 0;

	mouseOverAnyItem = false;
	DebugRender = false;
}
WinningScreen::~WinningScreen()
{
}

void WinningScreen::update(float dt)
{
	selectedItem;
	mouseOverAnyItem = false; // Reset this flag each frame

	// Update mouse position
	MousePos.x = input->getMouseX();
	MousePos.y = input->getMouseY();

	for (int i = 0; i < 2; i++) {
		if (Collision::checkBoundingBox(UIText[i].getCollisionBox(), MousePos)) {
			if (!mouseOverAnyItem) { // Only change if the mouse wasn't already over an item
				selectedItem = i;
				mouseOverAnyItem = true;
			}
		}
	}

	updateVisualFeedback(); // Update visual feedback at the end to reflect any changes
}

void WinningScreen::updateVisualFeedback()
{
	for (int i = 0; i < 2; i++) {
		if (i == selectedItem) {
			UIText[i].text.setFillColor(sf::Color::Red); // Highlight selected item
		}
		else {
			UIText[i].text.setFillColor(sf::Color::White); // Default color for non-selected items
		}
	}
}

void WinningScreen::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		UIText[selectedItem].text.setFillColor(sf::Color::White);
		selectedItem--;
		UIText[selectedItem].text.setFillColor(sf::Color::Red);
	}
}
void WinningScreen::MoveDown()
{
	if (selectedItem + 1 < 2)
	{
		UIText[selectedItem].text.setFillColor(sf::Color::White);
		selectedItem++;
		UIText[selectedItem].text.setFillColor(sf::Color::Red);
	}

}
void WinningScreen::handleInput(float dt)
{
	// Keyboard handling for menu navigation
	if (input->isKeyDown(sf::Keyboard::Up)) {
		MoveUp();
		input->setKeyUp(sf::Keyboard::Up);
	}

	if (input->isKeyDown(sf::Keyboard::Down)) {
		MoveDown();
		input->setKeyUp(sf::Keyboard::Down);
	}

	// Execute action for the current selected item
	if (input->isKeyDown(sf::Keyboard::Enter) || (input->isLeftMouseDown() && mouseOverAnyItem)) {
		switch (selectedItem) {
		case 0:
			std::cout << "Restart has been Pressed" << std::endl;

			gameState->setCurrentState(State::LEVEL);
			break;
		case 1:
			std::cout << "Exit Button has been pressed" << std::endl;
			exit(0);
			break;
		}

		// Reset input states
		if (input->isKeyDown(sf::Keyboard::Enter)) {
			input->setKeyUp(sf::Keyboard::Enter);
		}
		if (input->isLeftMouseDown()) {
			input->setLeftMouse(Input::MouseState::UP); // Assuming you have a method to reset the mouse state
		}
	}
}

void WinningScreen::render()
{
	beginDraw();
	window->draw(winner_sprite);
	window->draw(Title);
	for (int i = 0; i < 2; i++)
	{
		window->draw(UIText[i].text);
	}

	//Uncomment so debug shapes for the menu text

	if (DebugRender)
	{
		for (int i = 0; i < 2; i++)
		{
			window->draw(UIText[i].getDebugShape());
		}
	}
	endDraw();
}




void WinningScreen::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}
void WinningScreen::endDraw()
{
	window->display();
}