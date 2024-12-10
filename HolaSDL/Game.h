#pragma once

#include <array>

// Biblioteca SDL
#include <SDL.h>
#include "GameList.h"
#include "gameState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "gameStateMachine.h"
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"
#include "Block.h"
#include "Collision.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Lift.h"
#include "InfoBar.h"
#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

using uint = unsigned int;

const float SCALE = 2;
const float BlockTam = 32;
const float BlockTam2 = BlockTam / 2;
const float BlockTam4 = BlockTam / 4;
const Point2D gravity = Point2D(0, 3);
const int ANIM_RANGE = 5;
const float MAX_SPEED = 20;
const int enemyPoints = 100;
const int brickPoints = 50;
const int mushroomPoints = 1000;
const int coinPoints = 200;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		BLOCKS,
		FIREMARIO,
		GOOMBA,
		KOOPA,
		MARIO,
		MUSHROOM,
		PIRANHA,
		PLANT,
		SHELL,
		STAR,
		SUPERMARIO,
		COIN,
		LIFT,
		NUMBERS,
		PORTADA,
		NIVEL1,
		NIVEL2,
		SALIR,
		CONTINUAR,
		VOLVERALMENU,
		GAMEOVER,
		GAMEWIN,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool seguir;

	// Estados del juego
	GameStateMachine* stateMachine;

public:
	void run();

	void update();
	void render();
	void handleEvents();

	// Constante globales
	static constexpr uint WIN_WIDTH = 576;
	static constexpr uint WIN_HEIGHT = 512;
	static constexpr uint FRAME_RATE = 50;

	// Geters
	Texture* getTexture(TextureName name) const;

	GameStateMachine* getGameSTMachine() const { return stateMachine; };
	void endGame() { seguir = false; };

	Game();
	~Game();

	SDL_Renderer* getRenderer() const { return renderer; };
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
