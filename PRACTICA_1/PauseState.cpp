#include "PauseState.h"
#include "PlayState.h"
#include "button.h"
#include "Game.h"
#include "background.h"
#include <SDL.h>
#include "MainMenuState.h"

using namespace std;

PauseState::PauseState(Game* game) : GameState(game), gamePointer(game) {
	int hTam = 160;
	int vTam = 35;

	//Texture* titulo = game->getTexture(Game::PORTADA);
	//fondo = new background(this, titulo);
	//fondo->setTexture(titulo);
	//addObject(fondo);

	Vector2D<int> ContinuePos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 3);
	Vector2D<int> BackToMenuPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2);
	Vector2D<int> ExitPos = Vector2D<int>(game->WIN_WIDTH / 2 - hTam / 2, game->WIN_HEIGHT / 2 + vTam * 3);
	
	button* ContinueButton = new button(game, game->getTexture(Game::CONTINUAR), ContinuePos, hTam + vTam, vTam);
	addObject(ContinueButton);
	ContinueButton->connect([game]() {
		cout << "CONTINUAR PULSADO" << endl;
		game->popCurrentState();
	});
	addEventListener(ContinueButton);

	button* BackToMenuButton = new button(game, game->getTexture(Game::VOLVERALMENU), BackToMenuPos, hTam + vTam, vTam);
	addObject(BackToMenuButton);
	BackToMenuButton->connect([game]() {
		cout << "REGRESAR AL MENU PULSADO" << endl;
		game->changeState(new MainMenuState(game));
	});
	addEventListener(BackToMenuButton);

	button* ExitButton = new button(game, game->getTexture(Game::SALIR), ExitPos, hTam + vTam, vTam);
	addObject(ExitButton);
	ExitButton->connect([game]() {
		cout << "EXIT PULSADO" << endl;
		game->exitStates();
	});
	addEventListener(ExitButton);
}

PauseState::~PauseState() {
	//delete fondo;
}