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

Player::Player(Game* game, stringstream& atributes) : position(), TexturePlayer(game->getTexture(Game::MARIANO)), GamePlayer(game), vidas(0), jump(false), frameRunner(0), leftLimit(), damageCooldown(60){
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
	position = Vector2D<int>((positionx-1) * Game::TILE_SIDE, (positiony-1) * Game::TILE_SIDE);
	InitialPositionX = positionx;
	InitialPositionY = positiony;
	vidas = nvidas;
	lookingLeft = false;
	groundPosition = Vector2D<int>((positionx - 1) * Game::TILE_SIDE, (positiony - 1) * Game::TILE_SIDE);
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
	/*if (direction.getX() < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}*/
	if (lookingLeft) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	//Renderizamos con los parametros actualizados
	TexturePlayer->renderFrame(MPosition, 0, frame, flip);

}

void Player::update() {
	// Verifica colisión en todas las direcciones
	Collision collision = hit(getRect(), true);

	// Calcula la nueva posición
	Vector2D<int> newPosition = position + direction;

	// Verifica si el jugador ha salido por debajo del mapa
	if (newPosition.getY() >= 510) {
		vidas--;
		return; // Podrías usar `position = ResetPosition()` si quieres reiniciar la posición
	}

	if (jump && position.getY() <= groundPosition.getY() - (4 * Game::TILE_SIDE)) {
		jump = false;
		direction = Vector2D<int>(0, Game::TILE_SIDE / 2);
	}

	//if (collision.collides) {
	//	// Lógica de ajuste en caso de colisión
	//	if (collision.intersection.h > 0 && collision.intersection.w > 0) {
	//		if (direction.getY() > 0 && collision.intersection.y > position.getY()) {
	//			// Colisión desde abajo (suelo)
	//			newPosition = Vector2D<int>(position.getX(), position.getY());
	//			jump = true;
	//		}
	//		else if (direction.getY() < 0 && collision.intersection.y < position.getY()) {
	//			// Colisión desde arriba
	//			newPosition = Vector2D<int>(position.getX(), position.getY());
	//			jump = false;
	//		}
	//		else if (direction.getX() > 0 && collision.intersection.x > position.getX()) {
	//			// Colisión desde la izquierda
	//			newPosition = Vector2D<int>(position.getX(), position.getY());
	//			jump = false;
	//		}
	//		else if (direction.getX() < 0 && collision.intersection.x < position.getX()) {
	//			// Colisión desde la derecha
	//			newPosition = Vector2D<int>(position.getX(), position.getY());
	//			jump = false;
	//		}
	//	}
	//	position = newPosition;
	//}
	//else {
	//	// No hay colisión, actualizar la posición libremente
		position = newPosition;
	//}

	// Desplazamiento del mapa cuando se mueve a la derecha
	if (position.getX() > Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 && direction.getX() > 0) {
		GamePlayer->setMapOffset(Game::TILE_SIDE / 2);
		position = Vector2D<int>(Game::WINDOW_WIDTH * Game::TILE_SIDE / 2 + 16, position.getY());
	}
	// Restricción de movimiento a la izquierda del borde de la pantalla
	else if (position.getX() < 0) {
		position = Vector2D<int>(0, position.getY());
	}

	// Verifica si el jugador está en el suelo
	/*if (position.getY() >= GroundPosition - 100 && GroundCollision()) {
		jump = true;
	}
	else {
		jump = false;
	}*/

	// Actualización del frame de animación
	if (frameRunner > 3) frameRunner = 0;
	frameRunner++;

	// Control de daño
	if (damageCooldown >= 30 && collision.damages) {
		vidas--;
		damageCooldown = 0;
	}
	damageCooldown++;
}



bool
Player::GroundCollision() {
	bool onGround = false;
	SDL_Rect marioRect = getRect();
	marioRect.y += 1; // Aumenta Y para detectar el borde inferior del jugador.
	
	// Revisa si hay colisión con el suelo.
	Collision collision = hit(marioRect, true);
	/*if (collision.collides) GroundPosition = position.getY();
	return collision.collides;*/
	
	if (collision.collides) {
		// Ajusta GroundPosition a la altura del tile para que el jugador se alinee al suelo.
		int tileY = position.getY();
		//GroundPosition = tileY;
		//std::cout << "Colisión detectada. GroundPosition: " << GroundPosition << std::endl;
		return true;
	}
	return true;
	////std::cout << "No se detectó colisión con el suelo." << std::endl;
	//return false;
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
			direction = Vector2D<int>(1 * Game::TILE_SIDE / 2, direction.getY());
			lookingLeft = false;
			break;
		case SDLK_LEFT:
			if (!leftLimit) {
				direction = Vector2D<int>(-1 * Game::TILE_SIDE / 2, direction.getY());
				lookingLeft = true;
			}
			break;
		case SDLK_UP:
			if (!jump && GroundCollision()) {
				jump = true;
				groundPosition = position;
				direction = direction + Vector2D<int>(0, -Game::TILE_SIDE / 2);
			}
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
		case SDLK_LEFT:
			direction = Vector2D<int>(0, direction.getY());
			break;
		case SDLK_UP:
			if (!jump && direction.getY() < 0) {
				direction = Vector2D<int>(direction.getX(), Game::TILE_SIDE);
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
	Vector2D<int> position(InitialPositionX * Game::TILE_SIDE, InitialPositionY * Game::TILE_SIDE);
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
	playerRect.y = position.getY() + Game::TILE_SIDE;
	playerRect.w = Game::TILE_SIDE;
	playerRect.h = Game::TILE_SIDE;
	return playerRect;
}

int Player::getVidas() const {
	return vidas;
}