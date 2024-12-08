#include "EndState.h"
#include "MainMenuState.h"

#include "Game.h"

using namespace std;

EndState::EndState(Game* game) : GameState(game) {
	gamePointer = game;

    int hTam = 160;
    int vTam = 35;

    Texture* fondoNegro = game->getTexture(Game::ENDFONDO);
    fondo = new background(this, fondoNegro);
    fondo->setTexture(game->getTexture(Game::ENDFONDO));
    addObject(fondo);


    Vector2D<int> backMenuPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam);
    Vector2D<int> exitPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam * 3);

    // Botón para volver al menu
    button* backMenuButton = new button(game, game->getTexture(Game::VOLVERALMENU), startPos, hTam + vTam, vTam);
    addObject(backMenuButton);
    backMenuButton->connect([game]() {
        game->popCurrentState();
        game->pushNewState(new MainMenuState(game)); // Cambia al estado PlayState
        });
    addEventListener(backMenuButton);

    // Botón para salir del juego
    button* exitButton = new button(game, game->getTexture(Game::SALIR), exitPos, hTam, vTam);
    addObject(exitButton);
    exitButton->connect([game]() {
        game->popCurrentState(); // Sale del juego
        });
    addEventListener(exitButton);

}