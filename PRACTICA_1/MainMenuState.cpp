#include "MainMenuState.h"
#include "PlayState.h"
#include "button.h"
#include "Game.h"
#include "background.h"
#include <SDL.h>

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
        game->changeState(new PlayState(game)); // Cambia al estado PlayState
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

void MainMenuState::update() {
    //GameState::update();
    std::cout << "UPDATE MAIN MENU" << std::endl;
}

void MainMenuState::render() const {

    //GameState::render();
    
    //SDL_SetRenderDrawColor(gamePointer->getRenderer(), 0, 0, 0, 255);
    //SDL_RenderClear(gamePointer->getRenderer());
    //for (const auto& button : MenuButtons) {
    //    button->render();
    //}
    //SDL_RenderPresent(gamePointer->getRenderer());
    std::cout << "RENDER MAIN MENU" << std::endl;
}

void MainMenuState::handleEvent(const SDL_Event& event) {
   // GameState::handleEvent(event);
}
