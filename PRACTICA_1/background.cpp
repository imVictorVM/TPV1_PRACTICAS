#include "background.h"
#include "Game.h"
#include <SDL.h>

background::background(GameState* gameState, Texture* texture) : GameObject(gameState), texture(texture)
{ }

background::~background()
{ }

void
background::setTexture(Texture* newTexture) {
	texture = newTexture;
}

void background::update()
{
}

void background::render() const
{
	if (texture) {
		SDL_Rect rect = { 0,0,Game::WIN_WIDTH,Game::WIN_HEIGHT};
		texture->render(rect);
	}
}

