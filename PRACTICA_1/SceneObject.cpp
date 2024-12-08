#include "checkML.h"

#include "SceneObject.h"

#include "Game.h"

#include "PlayState.h"

using namespace std;


SceneObject::SceneObject(PlayState* g, istream& atributes) : GameObject(g) {
	playState = g;
	posX = 0;
	posY = 0;
	atributes >> posX;
	atributes >> posY;
	position =  Vector2D(posX * PlayState::TILE_SIDE ,(posY-1) * PlayState::TILE_SIDE);
	velocity = 2;
	velocityGravity = 4;
	direction = Vector2D(-velocity,velocityGravity);
	frame = 0;
	frameRunner = 0;
	previousOffset = 0;
	width = PlayState::TILE_SIDE;
	height = PlayState::TILE_SIDE;
	rect = getRect();

	frozen = true;
	ended = false;
	
}

SceneObject::SceneObject(PlayState* g) : GameObject(g) {
	playState = g;
	posX = 0;
	posY = 0;
	position = Vector2D(posX * PlayState::TILE_SIDE, (posY - 1) * PlayState::TILE_SIDE);
	direction = Vector2D(0, 0);
	frame = 0;
	frameRunner = 0;
	previousOffset = 0;
	velocity = 2;
	velocityGravity = 8;
	width = PlayState::TILE_SIDE;
	height = PlayState::TILE_SIDE;
	rect = getRect();

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
		texture->renderFrame(getRect(), 0, frame);
	}

}

//LAS COLISIONES FUNCIONAN EN VERTICAL PERO NO EN HORIZONTAL
Collision
SceneObject::tryToMove(const Vector2D<int>& speed, Collision::Target attack) {

	Collision colision = { false, false, {0,0,0,0} };

	if (attack == Collision::Target::ENEMIES) {
		direction = speed;
		rect = getRect();

		// CALCULO DE LA NUEVA POSICION EN FUNCION DE LA DIRECCION PULSANDO TECLA
		Vector2D<int> newPosition = position + direction;

		if (attack == Collision::Target::PLAYER) colision = playState->checkCollision(rect, true);
		else if (attack == Collision::Target::ENEMIES) colision = playState->checkCollision(rect, false);

		//cout << "Collision status: " << colision.collides << ", Intersection: "
		//	<< colision.intersection.x << ", " << colision.intersection.y << endl;

		rect.y += direction.getY();
		rect.x += direction.getX();

		//COLISION VERTICAL
		if (!colision.collides) position.setY(newPosition.getY());
		else {
			if (colision.intersection.y < position.getY()) {
				//position.setY(colision.intersection.y - rect.h);
				colision.vertical = colision.intersection.y + colision.intersection.h - rect.h;
				//Hacer una resta con la diferente entre la altura del rect del bloque y del jugador atravesado
				colision.result == Collision::OBSTACLE; //OBSTACLE
				position.setY(position.getY() - colision.vertical);
			} //SUELO
			else if (colision.intersection.y > position.getY()) {
				colision.result == 2; //OBSTACLE
				direction.setY(velocity);
			} //TECHO
		}

		//RECALCULO DE LA COLISION
		rect.x += position.getX();
		rect.y = direction.getY();

		if (attack == Collision::Target::PLAYER) colision = playState->checkCollision(rect, true);
		else if (attack == Collision::Target::ENEMIES) colision = playState->checkCollision(rect, false);

		//COLISION HORIZONTAL
		if (!colision.collides) position.setX(newPosition.getX());
		else {
			colision.result == Collision::OBSTACLE; //OBSTACLE
			if (colision.intersection.x > position.getX()) {
				direction.setX(-direction.getX());
				cout << "COLISIONO" << endl;
			} //MURO A LA IZQUIERDA
			else if (colision.intersection.x < position.getX()) {
				direction.setY(-direction.getX());
				cout << "COLISIONO" << endl;
			} // MURO A LA DERECHA
		}

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
