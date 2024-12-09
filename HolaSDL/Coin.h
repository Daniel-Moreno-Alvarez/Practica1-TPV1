#pragma once
#include "Pickable.h"
#include <istream>
class PlayState;

class Coin : public Pickable
{
private:
	int frameMax = 4;
public:
	Coin(PlayState* _gameST, std::istream& is);

	void update() override;
	void triggerAction() override;

	SceneObject* clone() const override;
};

