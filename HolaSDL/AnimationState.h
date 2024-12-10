#pragma once
#include <functional>
#include "gameState.h"

class AnimationState : public GameState
{
public:
	AnimationState(Game* _game, GameState* _gameState, std::function<bool()> _animationFunc);
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override {};
private:
	GameState* gameState;
	std::function<bool()> animationFunc;
};