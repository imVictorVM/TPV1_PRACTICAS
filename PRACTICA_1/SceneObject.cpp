#include "checkML.h"

#include "SceneObject.h"

#include "Game.h"

using namespace std;


SceneObject::SceneObject(Game* g, istream& atributes) : GameObject(g) {
	
	 posX = 0;
	 posY = 0;
	atributes >> posX;
	atributes >> posY;
	position =  Vector2D(posX * Game::TILE_SIDE ,(posY-1) * Game::TILE_SIDE);
	direction = Vector2D(0,0);
	frame = 0;
	frameRunner = 0;
	previousOffset = 0;
	velocity = 2;
	velocityGravity = 8;
	width = Game::TILE_SIDE;
	height = Game::TILE_SIDE;
	//rect = SDL_Rect(position.getX(), position.getY(), width, height);

	frozen = true;
	ended = false;
	
}

SceneObject::SceneObject(Game* g) : GameObject(g) {

	posX = 0;
	posY = 0;
	position = Vector2D(posX * Game::TILE_SIDE, (posY - 1) * Game::TILE_SIDE);
	direction = Vector2D(0, 0);
	frame = 0;
	frameRunner = 0;
	previousOffset = 0;
	velocity = 2;
	velocityGravity = 8;
	width = Game::TILE_SIDE;
	height = Game::TILE_SIDE;
	//rect = SDL_Rect(position.getX(), position.getY(), width, height);

	frozen = true;
	ended = false;

}

SceneObject::~SceneObject() {
	//delete texture;
	//GameObject::~GameObject();
}

void
SceneObject::render() const {

	if (!ended && !frozen) {
		SDL_Rect BPosition;
		BPosition.x = position.getX();
		BPosition.y = position.getY();
		BPosition.w = width;
		BPosition.h = height;

		texture->renderFrame(BPosition, 0, frame);
	}

}

Collision
SceneObject::tryToMove(const Vector2D<int>& speed, Collision::Target attack) {

	direction = speed;

	// CALCULO DE LA NUEVA POSICION EN FUNCION DE LA DIRECCION PULSANDO TECLA
	Vector2D<int> newPosition = position + direction;

	Collision colision = { false, false, {0,0,0,0} };

	if (attack == Collision::Target::PLAYER) colision = gamePointer->checkPlayerCollision(rect, true);
	else if (attack == Collision::Target::ENEMIES) colision = gamePointer->checkEnemyCollision(rect, false);

	rect.y += direction.getY();
	rect.x += direction.getX();

	//COLISION VERTICAL
	if (!colision.collides) position.setY(newPosition.getY());
	else {
		//position.setY(colision.intersection.y - rect.h);
		//Hacer una resta con la diferente entre la altura del rect del bloque y del jugador atravesado
		colision.result == 2; //OBSTACLE
		position.setY(position.getY());
		cout << "COLISION" << endl;
		//jump = false;
		return colision;

		//if (colision.intersection.y > position.getY()) {
		//	//position.setY(colision.intersection.y - rect.h);
		//	//Hacer una resta con la diferente entre la altura del rect del bloque y del jugador atravesado
		//	colision.result == 2; //OBSTACLE
		//	position.setY(position.getY());
		//	cout << "COLISION" << endl;
		//	//jump = false;
		//	return colision;
		//} //SUELO
		//else if (colision.intersection.y < position.getY()) {
		//	colision.result == 2; //OBSTACLE
		//	direction.setY(velocity);
		//	return colision;
		//} //TECHO
	}

	//RECALCULO DE LA COLISION
	rect.y = position.getY();
	rect.x += direction.getX();

	if (attack == Collision::Target::PLAYER) colision = gamePointer->checkPlayerCollision(rect, true);
	else if (attack == Collision::Target::ENEMIES) colision = gamePointer->checkEnemyCollision(rect, false);

	//COLISION HORIZONTAL
	if (!colision.collides) position.setX(newPosition.getX());
	else {
		colision.result == 2; //OBSTACLE
		if (colision.intersection.x > position.getX()) {
			//direction.setY(velocity);
			return colision;
		} //MURO A LA IZQUIERDA
		else if (colision.intersection.x < position.getX()) {
			//direction.setY(velocity);
			return colision;
		} // MURO A LA DERECHA
	}
	return colision;
}

SDL_Rect
SceneObject::getRect() const {
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = width;
	rect.h = height;
	return rect;
}

bool
SceneObject::isAlive() const {
	return !ended;
}


void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}
