#include "AnimationState.h"
#include "Game.h"

AnimationState::AnimationState(Game* _game, GameState* _gameState, std::function<bool()> _animationFunc) :
	GameState(_game), gameState(_gameState), animationFunc(_animationFunc)
{
}

void AnimationState::update()
{
	if (!animationFunc())
	{
		game->getGameSTMachine()->popState();
	}
}

void AnimationState::render() const
{
	gameState->render();
}
