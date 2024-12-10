#include "gameState.h"
#include "Game.h"

GameState::~GameState() 
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
	
	for (auto obj : eventHandlers)
	{
		delete obj;
	}
}
void GameState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* handler : eventHandlers) 
		handler->handleEvent(event);
}
