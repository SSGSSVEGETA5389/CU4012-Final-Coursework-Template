#include "TileEditor.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Framework/Utilities.h"

TileEditor::TileEditor(sf::RenderWindow* hwnd, Input* in, GameState* game, sf::View* v, World* w, TileManager* tm)
{
	window = hwnd;
	input = in;
	gameState = game;
	view = v;
	world = w;
	tileManager = tm;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "error loading font" << std::endl;
	};

	if (!mouseCurosorTex.loadFromFile("gfx/cursor-grabbed.png"))
	{
		std::cout << "Error loading cursor texture\n";
	}
	mouseCurosorGrab.setTexture(mouseCurosorTex);

	// Set up tile manager
	tileManager->setInput(input);
	tileManager->setWindow(window);
	tileManager->setWorld(world);
	tileManager->setView(view);
	tileManager->ShowDebugCollisionBox(true);

	if (!tileManager->loadTiles())
	{
		std::cout << "Tiles not found\n";
	}
	else
	{
		std::cout << "Tiles loaded\n";
	}

	originalViewSize = v->getSize(); // Store the original size of the view

}

TileEditor::~TileEditor()
{
}

void TileEditor::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Tab))
	{
		input->setKeyUp(sf::Keyboard::Tab);
		std::cout << "Exiting edit mode. Saving tiles...\n";
		tileManager->saveTiles(tileManager->getTiles(), tileManager->getFilePath());
		gameState->setCurrentState(State::LEVEL);

		// Reset the view to the original size
		view->setSize(originalViewSize);
		view->setCenter(window->getSize().x / 2, window->getSize().y / 2);
		view->zoom(1.0f);
	}
}

void TileEditor::update(float dt)
{
	tileManager->handleInput(dt);
	tileManager->update(dt);
	moveView(dt);
	window->setView(*view);
}

void TileEditor::render()
{
	if(isDragging) window->draw(mouseCurosorGrab);
	window->setView(*view);
	tileManager->render(true);
	tileManager->DrawImGui();

}

void TileEditor::moveView(float dt)
{

	sf::Vector2i pixelPos = sf::Vector2i(input->getMouseX(), input->getMouseY());
	sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos, *view);

	// Set the sprite position to the mouse position in world coordinates
	mouseCurosorGrab.setPosition(worldPos.x, worldPos.y);
	mouseCurosorGrab.setScale(currentZoomLevel, currentZoomLevel);

	// You can adjust the speed if needed
	float dragSpeed = 200.0f; // The speed might need to be adjusted based on view scale

	// Check for the left mouse button pressed event
	if (input->isRightMouseDown())
	{
		window->setMouseCursorVisible(false);
		if (!isDragging)
		{
			// When dragging starts, remember the initial position
			isDragging = true;
			lastMousePos.x = input->getMouseX();
			lastMousePos.y = input->getMouseY();
		}
		else
		{
			// Calculate the difference between the current mouse position and the last mouse position
			sf::Vector2i currentMousePos(input->getMouseX(), input->getMouseY());

			// Use mapPixelToCoords to convert from window coordinates to world coordinates
			sf::Vector2f lastWorldPos = window->mapPixelToCoords(lastMousePos);
			sf::Vector2f currentWorldPos = window->mapPixelToCoords(currentMousePos);

			// Calculate the delta in world coordinates
			sf::Vector2f deltaPos = lastWorldPos - currentWorldPos;

			// Move the view by this delta position
			view->move(deltaPos);

			// Update the last mouse position
			lastMousePos = currentMousePos;

			//input->setMousePosition(mousePos.x, mousePos.y);
		}
	}
	else
	{
		// If the right mouse button is not pressed, we are not dragging
		isDragging = false;
		window->setMouseCursorVisible(true);
	}

	if (!tileManager->isInputTextActive()) {
		if (input->isKeyDown(sf::Keyboard::Q))
		{
			currentZoomLevel *= 1.0005f;
			view->zoom(1.0005f);
		}
		if (input->isKeyDown(sf::Keyboard::E))
		{
			currentZoomLevel *= 0.9995f;
			view->zoom(0.9995f);
		}
	}
	// Handle mouse wheel zoom inputs
	int wheelDelta = input->getMouseWheelDelta();
	if (wheelDelta != 0) {
		float zoomFactor = wheelDelta > 0 ? 0.9f : 1.1f;  // More significant zoom change per scroll
		float zoomAdjustment = pow(zoomFactor, abs(wheelDelta));  // Apply the factor power of scroll intensity
		currentZoomLevel *= zoomAdjustment;
		view->zoom(zoomAdjustment);
	}
	// Set the new view
	window->setView(*view);
}