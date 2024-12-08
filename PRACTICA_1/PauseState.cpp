#include "checkML.h"
#include "PauseState.h"
#include "PlayState.h"
#include "Game.h"
#include "MainMenuState.h"

using namespace std;


PauseState::PauseState(Game* game, PlayState* pS) : GameState(game), gamePointer(game), playState(pS)
{
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

void
PauseState::render() const {
	playState->render();

	SDL_Rect rect = { 0,0,800,600 };
	SDL_SetRenderDrawBlendMode(gamePointer->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gamePointer->getRenderer(), 0,0,0,180);
	SDL_RenderFillRect(gamePointer->getRenderer(), &rect);
	SDL_SetRenderDrawBlendMode(gamePointer->getRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(gamePointer->getRenderer(), playState->getBackgroundColor(0), playState->getBackgroundColor(1), playState->getBackgroundColor(2), 180);

	GameState::render();
}

void
PauseState::update() {
	GameState::update();
}