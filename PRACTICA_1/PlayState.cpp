#include "PlayState.h"
#include "checkML.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Lift.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Collision.h"
#include "GameObject.h"
#include "SceneObject.h"


using namespace std;
class TileMap;

PlayState::PlayState(Game* game) : GameState(game)
{
	seguir = true;
	mapOffset = 0;

	loadNextLevel();
	run();
}

void
PlayState::loadNextLevel() {
	static int currentLevel = 0;

	vector<pair<string, string>> levels = {
		{"../assets/maps/world1.csv","../assets/maps/world1.txt"},
		{"../assets/maps/world2.csv","../assets/maps/world2.txt"},
	};

	if (currentLevel < levels.size()) {
		clearActualLevel();
		loadObjectMap(levels[currentLevel].first, levels[currentLevel].second);
		currentLevel++;
	}
	else seguir = false;
	//Llamar al menu principal
}

void
PlayState::loadObjectMap(const string& mapFile, const string& objectFile) {

	tilemap = new TileMap(mapFile, this);
	const string DEFAULT_MAP = objectFile;

	// Carga el mapa
	ifstream file(DEFAULT_MAP);

	if (!file.is_open()) return; //false

	string line;

	getline(file, line);
	stringstream color(line);
	int R = 0, G = 0, B = 0;
	color >> R >> G >> B;
	SDL_SetRenderDrawColor(getGame()->getRenderer(), R, G, B, 255); //Color de fondo leyendo la primera linea

	while (getline(file, line)) {

		stringstream lineStream(line);
		char let;
		lineStream >> let;

		switch (let) {
		case 'M':
			if (player == nullptr) player = new Player(this, lineStream);
			break;
		case 'B':
			gameList.push_back(new Block(this, lineStream));
			//blocks.push_back(new Block(this, lineStream));
			break;
		case 'G':
			gameList.push_back(new Goomba(this, lineStream));
			//goombas.push_back(new Goomba(this, lineStream));
			break;
		case 'K':
			gameList.push_back(new Koopa(this, lineStream));
			//koopas.push_back(new Koopa(this, lineStream));
			break;
		case 'L':
			gameList.push_back(new Lift(this, lineStream));
			//lifts.push_back(new Lift(this, lineStream));
			break;
		case 'C':
			gameList.push_back(new Coin(this, lineStream));
			//coins.push_back(new Coin(this, lineStream));
			break;
		}

	}
	file.close();
}

void
PlayState::clearActualLevel() {

	if (tilemap != nullptr) {
		delete tilemap;
		tilemap = nullptr;
	}

	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i] != nullptr) {
			delete blocks[i];
		}
		blocks[i] = nullptr;
	}
	blocks.clear();
	for (int i = 0; i < goombas.size(); i++) {
		if (goombas[i] != nullptr) {
			delete goombas[i];
		}
		goombas[i] = nullptr;
	}
	goombas.clear();
	for (int i = 0; i < koopas.size(); i++) {
		if (koopas[i] != nullptr) {
			delete koopas[i];
		}
		koopas[i] = nullptr;
	}
	koopas.clear();
	for (int i = 0; i < lifts.size(); i++) {
		if (lifts[i] != nullptr) {
			delete lifts[i];
		}
		lifts[i] = nullptr;
	}
	lifts.clear();
	for (int i = 0; i < coins.size(); i++) {
		if (coins[i] != nullptr) {
			delete coins[i];
		}
		coins[i] = nullptr;
	}
	coins.clear();
	for (int i = 0; i < mushrooms.size(); i++) {
		if (mushrooms[i] != nullptr) {
			delete mushrooms[i];
		}
		mushrooms[i] = nullptr;
	}
	mushrooms.clear();


	/*for (const SceneObject* sceneObj : gameList) {
		delete sceneObj;
	}*/

	// Actualiza el offset del mapa
	ResetMapOffset();
}

PlayState::~PlayState()
{
	clearActualLevel();

	// Elimina las texturas
	//for (Texture* texture : textures)
	//	delete texture;

	if (tilemap != nullptr)
	{
		delete tilemap;
	}
	if (player != nullptr) {
		delete player;
	}
	// Desactiva la SDL
	//SDL_DestroyRenderer(renderer);
	//SDL_DestroyWindow(window);
	//SDL_Quit();
}

void
PlayState::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
PlayState::render() const

{	// Pinta los objetos del juego
	SDL_RenderClear(renderer);
	tilemap->render();
	player->render();

	for (const SceneObject* sceneObj : gameList) {
		sceneObj->render();
	}

	SDL_RenderPresent(renderer);
}

void
PlayState::update()
{
	// Actualiza los objetos del juego
	tilemap->update();
	player->update();

	for (SceneObject* sceneObj : gameList) {
		sceneObj->update();
	}
}

int PlayState::getMapOffset() {
	return mapOffset;
};

void
PlayState::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
			//perro->handleEvent(evento);
			player->HandleEvent(evento);

		}
	}
}

Collision
PlayState::checkPlayerCollision(const SDL_Rect& rect, bool fromPlayer) {
	//fromPlayer se encargara de comprobar si viene de arriba o de abajo
	//rect es el rectangulo de la interseccion provocada entre dos objetos

	Collision colision = { false,false,{0,0,0,0} };

	// Primero verificamos colisión con el tilemap
	colision = tilemap->hit(rect, fromPlayer);
	if (colision.collides) return colision;

	for (SceneObject* sceneObj : gameList) {
		colision = sceneObj->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}

	return colision;
}

Collision
PlayState::checkEnemyCollision(const SDL_Rect& rect, bool fromPlayer) {

	Collision colision = { false,false,{0,0,0,0} };

	colision = tilemap->hit(rect, fromPlayer);
	if (colision.collides)
		return colision;

	for (Block* block : blocks) {
		colision = block->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}

	return colision;
}

//AQUI ESTAN LOS METODOS PUBLICOS ADICIONALES, NECESARIOS PARA LA LOGICA DEL JUEGO PERO NO ESPECIFICADOS EN ENUNCIADO
//Son necesarios todos, pero podriamos prescindir de alguno para optimizar codigo y no hacerlo público todo

void PlayState::setMapOffset(int playerOffset) {
	mapOffset += playerOffset;
}

void PlayState::ResetMapOffset() {
	mapOffset = 0;
}

//Vector2D<int> Game::getPlayerPosition() const {
//	return player->getPosition();
//}