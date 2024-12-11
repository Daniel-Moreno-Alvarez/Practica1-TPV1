#include "EndState.h"
#include "Game.h"

EndState::EndState(Game* _game, bool _win) :
	GameState(_game), win(_win)
{
	auxposX = Game::WIN_WIDTH / 2;
    if (win) {
        texture = game->getTexture(Game::GAMEWIN);
    }
    else {
        texture = game->getTexture(Game::GAMEOVER);
    }
    rect.w = texture->getFrameWidth();
    rect.h = texture->getFrameHeight();
    rect.x = auxposX - rect.w / 2;
    rect.y = tituloposY - rect.h / 2;

    SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
    startMenu();
}

void EndState::render() const
{
    texture->render(rect);

    for (auto obj : gameObjects) {
        obj->render();
    }
}

void EndState::update()
{
    for (auto obj : gameObjects) {
        obj->update();
    }
}

void EndState::startMenu()
{
    Button* volver = new Button(this, game->getTexture(Game::VOLVERALMENU), { auxposX, volverposY });
    volver->connect([this]() {
        game->getGameSTMachine()->popState();
        game->getGameSTMachine()->popState();
        });
    addButton(volver);

    Button* salir = new Button(this, game->getTexture(Game::SALIR), { auxposX, salirposY });
    salir->connect([this]() { game->endGame(); });
    addButton(salir);
}