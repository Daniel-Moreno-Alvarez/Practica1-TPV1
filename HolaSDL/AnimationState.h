#pragma once
#include <functional>
#include "gameState.h"
#include "PlayState.h"
class AnimationState : public GameState
{
public:
	AnimationState(Game* _game, PlayState* _playState, std::function<bool()> _animationFunc);
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override {};
private:
	PlayState* playState;
	std::function<bool()> animationFunc;
};