#include "Coin.h"
#include "checkML.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

Coin::Coin(PlayState* game, std::istream& atributes) : Pickable(game, atributes) {

	texture = gamePointer->getTexture(PlayState::COIN);

}

Coin::~Coin()
{
}

void
Coin::update() {

	int newOffset = gamePointer->getMapOffset();

	if (position.getX() < newOffset + PlayState::WINDOW_WIDTH * PlayState::TILE_SIDE) {
		frozen = false;
	}

	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}

	if (frameRunner == 0 || frameRunner > 3) frame = 0;
	if (frameRunner == 1) frame = 1;
	if (frameRunner == 2) frame = 2;
	if (frameRunner == 3) frame = 3;
	if (frameRunner > 3) frameRunner = 0;
	frameRunner++;
}



