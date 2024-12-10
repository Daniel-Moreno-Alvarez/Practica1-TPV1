#include "AnimationState.h"
#include "Game.h"

AnimationState::AnimationState(Game* _game, PlayState* _playState, std::function<bool()> _animationFunc) :
	GameState(_game), playState(_playState), animationFunc(_animationFunc)
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
	playState->render();
}
