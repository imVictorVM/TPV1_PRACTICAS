#include "checkML.h"
#include "Player.h"

#include "Game.h"

#include "PlayState.h"

using namespace std;

Player::Player(PlayState* gameState, stringstream& atributes) : SceneObject(gameState)
{
	GamePlayer = gameState;

	string line;

	//Leemos la linea y pasamos los valores de atributos al string line, atributes se desecha
	getline(atributes, line);

	//Al estar atributes vacio necesitamos llamar a un nuevo stringstream que vaya leyendo los valores de uno en uno
	stringstream lineStream(line);

	//Aplicamos numero de vidas con el tercer parametro
	lineStream >> vidas;

	texture = gameState->getGame()->getTexture(Game::MARIANO);
	TextureSuperMario = gameState->getGame()->getTexture(Game::SUPERMARIANO);


	//Pasamos los parametros al constructor del player despues de leerlos
	//position = Vector2D<int>((positionx) * PlayState::TILE_SIDE, (positiony - 1) * PlayState::TILE_SIDE);
	
	direction = Vector2D<int>(0, velocityGravity);
	InitialPositionX = position.getX();
	InitialPositionY = position.getY();
	leftLimit = false;
	lookingLeft = false;
	damageCooldown = 15;
	SuperMario = false;
	groundPositionY = (position.getY() - 1) * PlayState::TILE_SIDE;
	frameRunner = 0;
}

void
Player::render() const {

	SDL_Rect MPosition;
	MPosition = getRect();
	MPosition.x -= GamePlayer->getMapOffset();
		
	if (!SuperMario) {
		int frame = 0;
		//Si el jugador esta saltando ponemos el frame 6
		if (jump) frame = 6;
		//elegimos el frame de movimiento del jugador en funcion del valor de frameRunner, si esta quieto se descarta por la siguiente condicional
		else {
			if (frameRunner == 0) frame = 0;
			else if (frameRunner == 1) frame = 2;
			else if (frameRunner == 2) frame = 3;
			else frame = 4;
		}

		//Si el jugador esta quieto en horizontal y puede saltar ponemos el frame 0
		if (direction.getX() == 0 && !jump) frame = 0;
		if (damageCooldown < 15) frame = 1;

		//Esto es para comprobar si esta mirando a la izquierda o a la derecha y en funcion de eso girar el render en funcion de donde mire
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (lookingLeft) {
			flip = SDL_FLIP_HORIZONTAL;
		}

		//Renderizamos con los parametros actualizados
		texture->renderFrame(MPosition, 0, frame, flip);
	}
	else {
		int frame = 0;

		if (jump) frame = 6;
		else if (damageCooldown < 15) {
			frame = 21;
		}
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

		TextureSuperMario->renderFrame(MPosition, 0, frame, flip);
	}

}

void Player::update() {

	// CALCULO DE LA NUEVA POSICION EN FUNCION DE LA DIRECCION PULSANDO TECLA
	Vector2D<int> newPosition = position + direction;

	SDL_Rect MarioRect = getRect();

	MarioRect.y += direction.getY();
	MarioRect.x += direction.getX();

	// CAMBIAR: Verifica colisión en todas las direcciones
	Collision collision = GamePlayer->checkPlayerCollision(MarioRect, true);
	
	//FUNCIONAL: CONTROL DE SALTO
	int jumpMaxDistance = 4 * PlayState::TILE_SIDE;
	if (jump && position.getY() <= groundPositionY - jumpMaxDistance) {
		direction.setY(velocity);
	}
	
	//COLISION VERTICAL
	if (!collision.collides) position.setY(newPosition.getY());
	else {
		if (collision.intersection.y > position.getY()) { 
			groundPositionY = position.getY();
			//Hacer una resta con la diferente entre la altura del rect del bloque y del jugador atravesado
			jump = false;
		} //SUELO
		else if (collision.intersection.y < position.getY()) { 
			direction.setY(velocity);
		} //TECHO
	}
	
	//RECALCULO DE LA COLISION
	MarioRect.y = position.getY();
	MarioRect.x += direction.getX();
	
	collision = GamePlayer->checkPlayerCollision(MarioRect, true);
	
	//COLISION HORIZONTAL
	if (!collision.collides) position.setX(newPosition.getX());
	else {
		if (collision.intersection.x > position.getX()) { 
			//direction.setY(velocity);
		} //MURO A LA IZQUIERDA
		else if (collision.intersection.x < position.getX()) { 
			//direction.setY(velocity);
		} // MURO A LA DERECHA
	}

	// FUNCIONAL: CONTROL EN CASO DE DAÑO Y DE DERROTA
	if (position.getY() >= 470 || damageCooldown >= 15 && collision.damages) {
		if (vidas == 0) cout << "DERROTA" << endl;
		else {
			if (!SuperMario) {
				vidas--;
				damageCooldown = 0;
				position = Vector2D<int>(InitialPositionX * PlayState::TILE_SIDE, (InitialPositionY - 1) * PlayState::TILE_SIDE);
				GamePlayer->ResetMapOffset();
				cout << "Vidas restantes: " << vidas << endl;
				return;
			}
			else {
				damageCooldown = 0;
				TransformacionMario();
			}
		}
	}
	damageCooldown++;

	// FUNCIONAL: MARIO CRUZA EL LIMITE DEL MAPA IZQUIERDO
	if (position.getX() < GamePlayer->getMapOffset()) {
		position.setX(GamePlayer->getMapOffset());
	}

	// FUNCIONAL: CAMBIO DE LA ANIMACION AL CORRER
	if (frameRunner > 3) frameRunner = 0;
	else frameRunner++;

	bool midMap = false;
	int midMapPositionX = (PlayState::WINDOW_WIDTH * PlayState::TILE_SIDE / 2) + GamePlayer->getMapOffset();

	// FUNCIONAL: Condicional para mover el mapa a la derecha
	if (position.getX() > midMapPositionX && direction.getX() > 0) midMap = true;
	else midMap = false;

	// FUNCIONAL: Desplazamiento del mapa cuando se mueve a la derecha
	if (midMap) {
		GamePlayer->setMapOffset(velocity);
	}

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

//Obtenemos la direccion para la colision de bloques cuando mario salta desde abajo
Vector2D<int> 
Player::getDirection() const {
	return direction;
}

SDL_Rect 
Player::getRect() const{
	SDL_Rect playerRect;
	playerRect.x = position.getX();
	playerRect.y = position.getY();
	if (SuperMario) {
		playerRect.w = texture->getFrameWidth() * 2;
		playerRect.h = texture->getFrameHeight() * 4;
	}
	else {
		playerRect.w = TextureSuperMario->getFrameWidth() * 2;
		playerRect.h = TextureSuperMario->getFrameHeight();
	}

	return playerRect;
}

int Player::getVidas() const {
	return vidas;
}

void Player::TransformacionSuperMario(){
	position.setY(position.getY() - PlayState::TILE_SIDE);
	SuperMario = true;
}

void Player::TransformacionMario() {
	SuperMario = false;
}

bool Player::IsSuperMario() const {
	return SuperMario;
}