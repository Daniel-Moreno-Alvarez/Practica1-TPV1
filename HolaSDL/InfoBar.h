#pragma once
#include "GameObject.h"
#include "Texture.h"

class PlayState;

class InfoBar : public GameObject
{
private:
	Texture* numeros;
	int tam = 20;
	int offset = 5;
	int points = 0;
	PlayState* playST;
public:
	InfoBar(PlayState* _playST);
	void render() const override;
	void update() override {};

	void setPoints(int _p) { points += _p; };
	void resetPoints() { points = 0; };
};