#include "checkML.h"
#include "Player.h"
#include "Block.h"
#include "TileMap.h"
#include "Game.h"
#include "Collision.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

Player::Player(Game* game, stringstream& atributes) : position(), TexturePlayer(game->getTexture(Game::MARIANO)), GamePlayer(game), vidas(0), jump(false), frameRunner(0), leftLimit(), damageCooldown(60), velocity(8){
	string line;

	//Leemos la linea y pasamos los valores de atributos al string line, atributes se desecha
	getline(atributes, line);

	//Al estar atributes vacio necesitamos llamar a un nuevo stringstream que vaya leyendo los valores de uno en uno
	stringstream lineStream(line);

	//Aplicamos posicion en x con el primer parametro
	int positionx;
	lineStream >> positionx;
	//Aplicamos posicion en y con el segundo parametro
	int positiony;
	lineStream >> positiony;
	//Aplicamos numero de vidas con el tercer parametro
	int nvidas;
	lineStream >> nvidas;

	//Pasamos los parametros al constructor del player despues de leerlos
	position = Vector2D<int>((positionx) * Game::TILE_SIDE, (positiony - 1) * Game::TILE_SIDE);
	InitialPositionX = positionx;
	InitialPositionY = positiony;
	vidas = nvidas;
	lookingLeft = false;
	groundPositionY = (positiony - 1) * Game::TILE_SIDE;
}

void
Player::render() const {
	SDL_Rect MPosition;
	MPosition.x = position.getX();
	MPosition.y = position.getY();
	MPosition.w = Game::TILE_SIDE;
	MPosition.h = Game::TILE_SIDE;

	int frame = 0;
	//Si el jugador esta saltando ponemos el frame 6
	if (jump) frame = 6;
	else if (damageCooldown < 60) {
		frame = 1;
	}
	//elegimos el frame de movimiento del jugador en funcion del valor de frameRunner, si esta quieto se descarta por la siguiente condicional
	else {
		if (frameRunner == 0) frame = 0;
		else if (frameRunner == 1) frame = 2;
		else if (frameRunner == 2) frame = 3;
		else frame = 4;
	}
	//Si el jugador esta quieto en horizontal y puede saltar ponemos el frame 0
	if (direction.getX() == 0 && !jump) frame = 0;

	//Esto es para comprobar si esta mirando a la izquierda o a la derecha y en funcion de eso girar el render en funcion de donde mire
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (lookingLeft) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	//Renderizamos con los parametros actualizados
	TexturePlayer->renderFrame(MPosition, 0, frame, flip);

}

void Player::update() {

	SDL_Rect MarioRect = getRect();
	MarioRect.y += direction.getY();
	MarioRect.x += GamePlayer->getMapOffset();

	// Verifica colisión en todas las direcciones
	Collision collision = GamePlayer->checkPlayerCollision(MarioRect, true);

	// CALCULO DE LA NUEVA POSICION EN FUNCION DE LA DIRECCION PULSANDO TECLA
	Vector2D<int> newPosition = position + direction;

	// CONTROL EN CASO DE DERROTA
	if (newPosition.getY() >= 510 || damageCooldown >= 30 && collision.damages) {
		vidas--;
		position = ResetPosition(); //Reseteamos la posicion de mario
		GamePlayer->ResetMapOffset(); //Reseteamos el mapoffset
		return;
	}
	damageCooldown++;

	int jumpMaxDistance = 4 * Game::TILE_SIDE;
	if (jump && position.getY() <= groundPositionY - jumpMaxDistance) {
		jump = false;
		direction.setY(velocity);
	}

	if (collision.collides) {
		// Lógica de ajuste en caso de colisión
		//if (direction.getY() > 0 && collision.intersection.y > position.getY()) {
		//	// Colisión desde abajo (suelo)
		//	newPosition = Vector2D<int>(newPosition.getX(), newPosition.getY() - collision.intersection.h);
		//	jump = true;
		//}
		//else if (direction.getY() < 0 && collision.intersection.y < position.getY()) {
		//	// Colisión desde arriba
		//	newPosition = Vector2D<int>(newPosition.getX(), newPosition.getY() + collision.intersection.h);
		//	jump = false;
		//}
		//position = Vector2D<int>(newPosition.getX(),position.getY());
		groundPositionY = position.getY();
		jump = false;
		if (collision.intersection.y > position.getX()) {
			
		}
		else if (collision.intersection.y < position.getX()) {

		}
	}
	else {
		// No hay colisión, actualizar la posición libremente
		position.setY(newPosition.getY());
		
	}

	MarioRect.y = position.getY();
	MarioRect.x += direction.getX();

	collision = GamePlayer->checkPlayerCollision(MarioRect, true);

	if (collision.collides) {
		//if (direction.getX() > 0 && collision.intersection.x > position.getX()) {
		//	// Colisión desde la izquierda
		//	newPosition = Vector2D<int>(position.getX() - collision.intersection.w, position.getY());
		//	jump = false;
		//}
		//else if (direction.getX() < 0 && collision.intersection.x < position.getX()) {
		//	// Colisión desde la derecha
		//	newPosition = Vector2D<int>(position.getX() + collision.intersection.w, position.getY());
		//	jump = false;
		//}
		if (collision.intersection.x > position.getX()) {

		}
		else if (collision.intersection.x < position.getX()) {

		}
	} 
	else {
		position.setX(newPosition.getX());
	}
		
	// Desplazamiento del mapa cuando se mueve a la derecha
	if (position.getX() > Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 && direction.getX() > 0) {
		GamePlayer->setMapOffset(position.getX() / Game::TILE_SIDE);
		//position = Vector2D<int>(Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 + 16, position.getY());
	}

	// Restricción de movimiento a la izquierda del borde de la pantalla
	if (position.getX() < 0) {
		position.setX(0);
	}

	// Actualización del frame de animación
	if (frameRunner > 3) frameRunner = 0;
	frameRunner++;
}

Collision 
Player::hit(const SDL_Rect& rect, bool fromPlayer) {
	return GamePlayer->checkPlayerCollision(rect, fromPlayer);
}

void 
Player::HandleEvent(SDL_Event event) {
	//La direccion tambien cuenta como si fuese la velocidad, uso tileside por ser una variable global y accesible para todos
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			direction.setX(velocity);
			lookingLeft = false;
			break;
		case SDLK_LEFT:
			if (!leftLimit) { //Verifica que el jugador no se pase del borde izquierdo de la pantalla
				direction.setX(-velocity);
				lookingLeft = true;
			}
			break;
		case SDLK_SPACE:
			if (!jump) {
				jump = true;
				groundPositionY = position.getY();
				direction.setY(-velocity);
			}
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			direction.setX(0);
			break;
		case SDLK_LEFT:
			direction.setX(0);
			break;
		case SDLK_SPACE:
			if (!jump && direction.getY() < 0) {
				direction.setY(velocity);
			}
			break;
		}
	}
}

//Obtenemos la posicion para la colision
Vector2D<int> 
Player::getPosition() const {
	return position;
}

Vector2D<int>
Player::ResetPosition() const {
	Vector2D<int> position((InitialPositionX-1) * Game::TILE_SIDE, (InitialPositionY-1) * Game::TILE_SIDE);
	return position;
}

//Obtenemos la direccion para la colision de bloques cuando mario salta desde abajo
Vector2D<int> 
Player::getDirection() const {
	return direction;
}

//Recordemos que el rect del jugador tiene el origen distinto al de los tiles para colisionar con el entorno, por eso puede atravesarlos
SDL_Rect 
Player::getRect() const{
	SDL_Rect playerRect;
	playerRect.x = position.getX();
	playerRect.y = position.getY();
	playerRect.w = Game::TILE_SIDE;
	playerRect.h = Game::TILE_SIDE;
	return playerRect;
}

int Player::getVidas() const {
	return vidas;
}