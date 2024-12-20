#pragma once
#include <SDL.h>

struct Collision {
	bool collides = false;
	bool damages = false;
	bool isEnemy = false;
	SDL_Rect rect = { 0,0,0,0 };

	operator bool() const { return collides; }

	// �A qui�n afecta esta colisi�n? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparasz�n opciona).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisi�n
	enum Result {
		NONE,		// no ha habido colisi�n
		DAMAGE,		// la colisi�n produce da�o
		OBSTACLE,	// la colisi�n impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisi�n horizontal
	int vertical = 0;     // profundidad de la colisi�n vertical
};

const Collision NO_COLLISION = Collision();