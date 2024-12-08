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

PlayState::PlayState(Game* game, int lvl) : GameState(game)
{
	currentLevel = lvl;
	seguir = true;
	mapOffset = 0;
	//BACKGROUND
	R = 0;
	G = 0;
	B = 0;
	renderer = game->getRenderer();
	loadNextLevel();
	//run();
}

void
PlayState::loadNextLevel() {

	vector<pair<string, string>> levels = {
		{"../assets/maps/world1.csv","../assets/maps/world1.txt"},
		{"../assets/maps/world2.csv","../assets/maps/world2.txt"},
	};

	if (currentLevel < levels.size()) {
		clearActualLevel();
		loadObjectMap(levels[currentLevel].first, levels[currentLevel].second);
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
	color >> R >> G >> B;
	SDL_SetRenderDrawColor(renderer, R, G, B, 255);

	GameObject* obj = nullptr;

	while (getline(file, line)) {
		stringstream lineStream(line);
		char type;
		lineStream >> type;

		switch (type) {
		case 'M':
			if (player == nullptr) player = new Player(this, lineStream);
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

	if (player != nullptr) {
		
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


int PlayState::getMapOffset() const {
	return mapOffset;
};


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

void PlayState::setCurrentLevel() {
	currentLevel++;
}

int
PlayState::getBackgroundColor(int pos) {
	switch (pos) {
	case 0: return R;
		break;
	case 1: return G;
		break;
	case 2: return B;
		break;
	default: return 0;
		break;
	}
}