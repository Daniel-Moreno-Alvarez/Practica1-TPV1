#include "gameState.h"
#include "Game.h"

void GameState::render() const
{
	for (GameObject* object : gameObjects)
		object->render();
}

void GameState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* handler : eventHandlers)
		handler->handleEvent(event);
}
