#include "checkML.h"
#include "Mushroom.h"
#include "Game.h"

using namespace std;

Mushroom::Mushroom(Game* game, SDL_Rect rect) : Pickable(game)
	//position(), direction(), mushroomTexture(game->getTexture(Game::MUSHROOM)), mushroomGame(game), velocity(2), previousOffset(0), ended(false), velocityGravity(8)
{
	//posicion de la seta
	int posX = rect.x + gamePointer->getMapOffset();
	int posY = rect.y - Game::TILE_SIDE;
	position = Vector2D<int>(posX, posY);
	direction = Vector2D<int>(velocity, 0);
	frozen = false;
	texture = gamePointer->getTexture(Game::MUSHROOM);
	
}

Mushroom::~Mushroom() {

}


void
Mushroom::update() {

	if (!ended) {
		Vector2D<int> newPosition = position + direction;

		SDL_Rect MushRect = getRect();
		MushRect.y += direction.getY();
		MushRect.x += direction.getX();

		Collision collision = gamePointer->checkEnemyCollision(MushRect, false);

		//COLISION VERTICAL
		if (!collision.collides) {
			direction.setY(velocityGravity);
			position.setY(newPosition.getY());
		}
		else {
			if (collision.intersection.y > position.getY()) {
				direction.setY(0);
			} //SUELO
			else if (collision.intersection.y < position.getY()) {
				direction.setY(velocityGravity);
			} //TECHO
		}

		MushRect.x += direction.getX();
		MushRect.y = position.getY();

		collision = gamePointer->checkEnemyCollision(MushRect, false);

		//COLISION HORIZONTAL
		if (!collision.collides) {
			position.setX(newPosition.getX());
		}
		else {
			if (collision.intersection.x > position.getX()) {
				direction.setX(-direction.getX());
			}
			else if (collision.intersection.x < position.getX()) {
				direction.setX(-direction.getX());
			}
		}

		if (position.getX() < 0 - Game::TILE_SIDE || position.getY() >= 470) {
			ended = true;
			cout << "Seta: Me he muerto por limite de mapa" << endl;
		}
	}

	//Los bloques se mueven en funcion el offset del mapa
	int newOffset = gamePointer->getMapOffset();
	int offsetChange = newOffset - previousOffset;
	if (offsetChange != 0) {
		position.setX(position.getX() - offsetChange);
		previousOffset = newOffset;
	}

}
