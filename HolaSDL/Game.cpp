#include <string>

#include "Game.h"

using namespace std;

// Formato de la especificacion de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec
	{"background.png", 9, 7},
	{"blocks.png", 6, 1},
	{"firemario.png", 21, 1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"mario.png", 12, 1},
	{"mushroom.png", 1, 1},
	{"piranha.png", 2, 1},
	{"plant.png", 4, 1},
	{"shell.png", 2, 1},
	{"star.png", 4, 1},
	{"supermario.png", 22, 1},
	{"coin.png", 4, 1},
	{"lift.png", 1, 1},
	{"numbers.png", 10, 1},
};

Game::Game()
 : seguir(true)
{
	// Inicializa la SDL
	try
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("SUPER MARIO",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH,
			WIN_HEIGHT,
			SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	catch (const std::string& error)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw "Error al cargar SDL";
	}

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		try {
			textures[i] = new Texture(renderer,
				(textureRoot + textureSpec[i].name).c_str(),
				textureSpec[i].numRows,
				textureSpec[i].numColumns);
		}
		catch (const std::string& error)
		{
			throw "Error al cargar la textura " + string(textureSpec[i].name);
		}
	}

	stateMachine = new GameStateMachine();
	playState = new PlayState(this);
	stateMachine->pushState(playState);
}

Game::~Game()
{
	delete stateMachine;

	// Elimina las texturas
	for (Texture* texture : textures) {
		delete texture;
	}

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		update();// Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render()
{
	SDL_RenderClear(renderer);

	stateMachine->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	stateMachine->update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) {
			seguir = false;
		}
		stateMachine->handleEvent(evento);
	}
} 