#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"



using namespace std;

MainMenuState::MainMenuState(Game* game) : GameState(game), gamePointer(game) {

    int hTam = 160;
    int vTam = 35;

    Texture* titulo = game->getTexture(Game::PORTADA);
    fondo = new background(this, titulo,0,0, game->WIN_WIDTH, game->WIN_HEIGHT);
    fondo->setTexture(game->getTexture(Game::PORTADA));
    addObject(fondo);

    Vector2D<int> lvl1Pos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam/2);
    Vector2D<int> lvl2Pos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam * 2);
    Vector2D<int> exitPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam*4);

    // Botón para iniciar nivel 1
    button* lvl1Button = new button(game,game->getTexture(Game::NIVEL1), lvl1Pos,hTam + vTam,vTam);
    addObject(lvl1Button);
    lvl1Button->connect([game]() {
        game->popCurrentState();
        game->pushNewState(new PlayState(game, 0)); // Cambia al estado PlayState
    });
    addEventListener(lvl1Button);


    //Botón para iniciar nivel 2
    button* lvl2Button = new button(game, game->getTexture(Game::NIVEL2), lvl2Pos, hTam + vTam, vTam);
    addObject(lvl2Button);
    lvl2Button->connect([game]() {
        game->popCurrentState();
        game->pushNewState(new PlayState(game, 1)); // Cambia al estado PlayState
        });
    addEventListener(lvl2Button);

    // Botón para salir del juego
    button* exitButton = new button(game,game->getTexture(Game::SALIR),exitPos,hTam,vTam);
    addObject(exitButton);
    exitButton->connect([game]() {
        game->exitStates(); // Sale del juego
    });
    addEventListener(exitButton);
}

MainMenuState::~MainMenuState() {
    delete fondo;
}
