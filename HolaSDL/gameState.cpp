#include "gameState.h"
#include "Game.h"

void GameState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* handler : eventHandlers) 
		handler->handleEvent(event);
}

void GameState::addButton(Button* _button)
{
	gameObjects.push_back(_button);
	eventHandlers.push_back(_button);
}
