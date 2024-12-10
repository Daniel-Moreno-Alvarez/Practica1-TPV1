#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* _game)
    : GameState(_game)
{
    auxposX = Game::WIN_WIDTH / 2;
    startMenu();
}

void MainMenuState::render() const
{
    getGame()->getTexture(Game::PORTADA)->render();

    for (auto obj : gameObjects) {
        obj->render();
    }
}

void MainMenuState::update()
{
    for (auto obj : gameObjects) {
        obj->update();
    }
}

void MainMenuState::startMenu()
{
    Button* nivel1 = new Button(this, game->getTexture(Game::NIVEL1), { auxposX, nivel1posY });
    nivel1->connect([this]() { loadLevel(1); });
    addButton(nivel1);

    Button* nivel2 = new Button(this, game->getTexture(Game::NIVEL2), { auxposX, nivel2posY });
    nivel2->connect([this]() { loadLevel(2); });
    addButton(nivel2);

    Button* salir = new Button(this, game->getTexture(Game::SALIR), { auxposX, salirposY });
    salir->connect([this]() { game->endGame(); });
    addButton(salir);
}

void MainMenuState::loadLevel(int level)
{
    GameState* playS = new PlayState(game, level);

    game->getGameSTMachine()->pushState(playS);
}