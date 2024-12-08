#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"



using namespace std;

MainMenuState::MainMenuState(Game* game) : GameState(game), gamePointer(game) {

    int hTam = 160;
    int vTam = 35;

    Texture* titulo = game->getTexture(Game::PORTADA);
    fondo = new background(this, titulo);
    fondo->setTexture(game->getTexture(Game::PORTADA));
    addObject(fondo);

    Vector2D<int> startPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam);
    Vector2D<int> exitPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam*3);

    // Botón para iniciar nivel 1
    button* startButton = new button(game,game->getTexture(Game::NIVEL1),startPos,hTam + vTam,vTam);
    addObject(startButton);
    startButton->connect([game]() {
        game->popCurrentState();
        game->pushNewState(new PlayState(game)); // Cambia al estado PlayState
    });
    addEventListener(startButton);

    // Botón para salir del juego
    button* exitButton = new button(game,game->getTexture(Game::SALIR),exitPos,hTam,vTam);
    addObject(exitButton);
    exitButton->connect([game]() {
        game->popCurrentState(); // Sale del juego
    });
    addEventListener(exitButton);
}

MainMenuState::~MainMenuState() {
    delete fondo;
}
