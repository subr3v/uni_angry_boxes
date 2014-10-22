#include "GameState.h"

bool GameState::getCurrentState()
{
	return isCurrentState;
}

void GameState::setCurrentState(bool newState)
{
	isCurrentState = newState;
}

GameState::GameState()
{
	isCurrentState = false;
}