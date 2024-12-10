#include "PauseState.h"
#include "Game.h"

PauseState::PauseState(Game* _game, GameState* _gameState) :
    GameState(_game), gameState(_gameState)
{
    auxposX = Game::WIN_WIDTH / 2;
    startMenu();
}

void PauseState::update()
{
    for (auto obj : gameObjects) {
        obj->update();
    }
}

void PauseState::render() const
{
    gameState->render();

    for (auto obj : gameObjects) {
        obj->render();
    }
}

void PauseState::startMenu()
{
    Button* volver = new Button(this, game->getTexture(Game::VOLVERALMENU), { auxposX, volverposY });
    volver->connect([this]() { 
        game->getGameSTMachine()->popState();
        game->getGameSTMachine()->popState();
        });
    addButton(volver);

    Button* continuar = new Button(this, game->getTexture(Game::CONTINUAR), { auxposX, continuarposY });
    continuar->connect([this]() { game->getGameSTMachine()->popState(); });
    addButton(continuar);

    Button* salir = new Button(this, game->getTexture(Game::SALIR), { auxposX, salirposY });
    salir->connect([this]() { game->endGame(); });
    addButton(salir);
}

void PauseState::addButton(Button* _button)
{
    gameObjects.push_back(_button);
    eventHandlers.push_back(_button);
}
