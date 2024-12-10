#include "gameState.h"
#include "Game.h"

void GameState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* handler : eventHandlers) 
		handler->handleEvent(event);
}
