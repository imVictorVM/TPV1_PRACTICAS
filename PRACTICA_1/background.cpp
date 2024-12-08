#include "checkML.h"
#include "background.h"
#include "Game.h"
#include <SDL.h>

background::background(GameState* gameState, Texture* texture,int x, int y, int width, int height) : GameObject(gameState), texture(texture)
{
	xPos = x;
	yPos = y;
	w = width;
	h = height;
}

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
		SDL_Rect rect = { xPos,yPos,w,h};
		texture->render(rect);
	}
}

