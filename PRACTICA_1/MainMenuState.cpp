#include "MainMenuState.h"
#include "PlayState.h"
#include "button.h"
#include "Game.h"
#include <SDL.h>

using namespace std;

MainMenuState::MainMenuState(Game* game) : GameState(game), gamePointer(game) {
    // Botón para iniciar nivel 1
    auto startButton = std::make_unique<button>(game);
    startButton->connect([game]() {
        game->changeState(new PlayState(game)); // Cambia al estado PlayState
    });
    addEventListener(startButton.get());
    MenuButtons.push_back(std::move(startButton));

    // Botón para salir del juego
    auto exitButton = std::make_unique<button>(game);
    exitButton->connect([game]() {
        game->popCurrentState(); // Sale del juego
    });
    addEventListener(exitButton.get());
    MenuButtons.push_back(std::move(exitButton));
}

void MainMenuState::update() {
    for (auto& button : MenuButtons) {
        button->update();
    }
}

void MainMenuState::render() const {
    SDL_SetRenderDrawColor(gamePointer->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(gamePointer->getRenderer());
    for (const auto& button : MenuButtons) {
        button->render();
    }
    SDL_RenderPresent(gamePointer->getRenderer());
}

void MainMenuState::handleEvent(const SDL_Event& event) {
    for (auto& button : MenuButtons) {
        button->handleEvent(event);
    }
}
