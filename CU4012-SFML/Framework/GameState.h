// Game State Class
// Simple game state controller. enum lists possible game states (can be modified), tracks and updates the current state

#pragma once

// Possible states. This enum can be modified to add additional states as required.
enum class State { MENU, LEVEL, TILEEDITOR,PAUSE, CREDITS, GAMEOVER, WINNER };

class GameState
{
public:
	// Set the current state.
	void setCurrentState(State s);
	// Returns the current state.
	State getCurrentState();
	
	


protected:
	State currentState;
	bool paused;
	
};