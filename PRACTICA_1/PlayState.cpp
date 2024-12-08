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
	renderer = game->getRenderer();
	loadNextLevel();
	//run();
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

void PlayState::loadObjectMap(const string& mapFile, const string& objectFile) {
	tilemap = new TileMap(mapFile, this);
	addObject(tilemap); // Añade a la lista principal de objetos

	ifstream file(objectFile);
	if (!file.is_open()) return;

	string line;
	getline(file, line); // Leer color de fondo
	stringstream color(line);
	int R = 0, G = 0, B = 0;
	color >> R >> G >> B;
	SDL_SetRenderDrawColor(renderer, R, G, B, 255);

	GameObject* obj = nullptr;

	while (getline(file, line)) {
		stringstream lineStream(line);
		char type;
		lineStream >> type;

		switch (type) {
		case 'M':
			player = new Player(this, lineStream);
			addObject(player);
			addEventListener(player);
			break;
		case 'B':
			obj = new Block(this, lineStream);
			break;
		case 'G':
			obj = new Goomba(this, lineStream);
			break;
		case 'K':
			obj = new Koopa(this, lineStream);
			break;
		case 'L':
			obj = new Lift(this, lineStream);
			break;
		case 'C':
			obj = new Coin(this, lineStream);
			break;
		}

		if (obj) {
			addObject(obj);
			// Verifica si obj es un SceneObject y lo añade a gameList
			SceneObject* sceneObj = static_cast<SceneObject*>(obj);
			if (sceneObj) {
				gameList.push_back(sceneObj);
			}
			obj = nullptr;
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

	for (const SceneObject* sceneObj : gameList) {
		delete sceneObj;
	}

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

//void
//PlayState::run()
//{
//	// Bucle principal del juego
//	while (seguir) {
//		// Marca de tiempo del inicio de la iteración
//		uint32_t inicio = SDL_GetTicks();
//
//		update();       // Actualiza el estado de los objetos del juego
//		render();       // Dibuja los objetos en la venta
//		handleEvents(); // Maneja los eventos de la SDL
//
//		// Tiempo que se ha tardado en ejecutar lo anterior
//		uint32_t elapsed = SDL_GetTicks() - inicio;
//
//		// Duerme el resto de la duración del frame
//		if (elapsed < FRAME_RATE)
//			SDL_Delay(FRAME_RATE - elapsed);
//	}
//}

//void
//PlayState::render() const
//
//{	// Pinta los objetos del juego
//	SDL_RenderClear(renderer);
//	tilemap->render();
//	player->render();
//
//	for (const SceneObject* sceneObj : gameList) {
//		sceneObj->render();
//	}
//
//	SDL_RenderPresent(renderer);
//}
//
//void
//PlayState::update()
//{
//	// Actualiza los objetos del juego
//	tilemap->update();
//	player->update();
//
//	for (SceneObject* sceneObj : gameList) {
//		sceneObj->update();
//	}
//}


int PlayState::getMapOffset() const {
	return mapOffset;
};

//void
//PlayState::handleEvents()
//{
//	// Procesamiento de eventos
//	SDL_Event evento;
//
//	while (SDL_PollEvent(&evento)) {
//		if (evento.type == SDL_QUIT)
//			seguir = false;
//		else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
//			//perro->handleEvent(evento);
//			player->handleEvent(evento);
//
//		}
//	}
//}


Collision
PlayState::checkCollision(const SDL_Rect& rect, bool fromPlayer) {
	//fromPlayer se encargara de comprobar si viene de arriba o de abajo
	//rect es el rectangulo de la interseccion provocada entre dos objetos

	Collision colision = { true,false,{0,0,0,0} };

	// Primero verificamos colisión con el tilemap
	colision = tilemap->hit(rect, fromPlayer);
	if (colision.collides) return colision;

	for (SceneObject* sceneObj : gameList) {
		colision = sceneObj->hit(rect, fromPlayer);
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