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

// Formato de la especificación de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificación de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	TextureSpec{"mario.png", 12, 1},
	TextureSpec{"blocks.png", 6, 1},
	TextureSpec{"goomba.png",3,1},
	TextureSpec{"koopa.png",4,1},
	TextureSpec{"mushroom.png",1,1},
	TextureSpec{"supermario.png",22,1},
	TextureSpec{"lift.png",1,1},
	TextureSpec{"coin.png",4,1},
};

Game::Game()
 : seguir(true)
{
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          WIN_WIDTH,
	                          WIN_HEIGHT,
	                          SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//SDL_RenderSetLogicalSize(renderer, WIN_WIDTH, WIN_HEIGHT);

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	mapOffset = 0;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
		                          (textureRoot + textureSpec[i].name).c_str(),
		                          textureSpec[i].numRows,
					  textureSpec[i].numColumns);

	// Crea los objetos del juego
	//perro = new Dog(this, -textures[DOG]->getFrameWidth(), 390);
	//stringstream ss;
	//player = new Player(this,ss);
	loadNextLevel();
}

void
Game::loadNextLevel() {
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

}

void
Game::loadObjectMap(const string& mapFile, const string& objectFile) {

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
	SDL_SetRenderDrawColor(renderer, R, G, B, 255); //Color de fondo leyendo la primera linea

	while (getline(file, line)) {
		
		stringstream lineStream(line);
		char let;
		lineStream >> let;

		switch (let) {
		case 'M':
			if (player == nullptr) player = new Player(this, lineStream);
			break;
		case 'B':
			//gameList.push_back(new Block(this, lineStream));
			blocks.push_back(new Block(this, lineStream));
			break;
		case 'G':
			//gameList.push_back(new Goomba(this, lineStream));
			goombas.push_back(new Goomba(this, lineStream));
			break;
		case 'K':
			//gameList.push_back(new Koopa(this, lineStream));
			koopas.push_back(new Koopa(this, lineStream));
			break;
		case 'L':
			//gameList.push_back(new Lift(this, lineStream));
			lifts.push_back(new Lift(this, lineStream));
			break;
		case 'C':
			//gameList.push_back(new Coin(this, lineStream));
			coins.push_back(new Coin(this, lineStream));
			break;
		}

	}
	file.close();
}

void
Game::clearActualLevel() {

	if (tilemap != nullptr) {
		delete tilemap;
		tilemap = nullptr;
	}

	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

	// OTRAS APLICACIONES DE BORRADO 
	//for (Block* block : blocks) delete block;
	//blocks.clear();
	for (auto it = blocks.begin(); it != blocks.end(); ++it) {
		delete* it;
		it = blocks.erase(it);
	}
	////for (Goomba* goomba : goombas) delete goomba;
	////goombas.clear();
	for (auto it = goombas.begin(); it != goombas.end(); ++it) {
		delete* it;
		it = goombas.erase(it);
	}
	////for (Koopa* koopa : koopas) delete koopa;
	////koopas.clear();
	for (auto it = koopas.begin(); it != koopas.end(); ++it) {
		delete* it;
		it = koopas.erase(it);
	}
	////for (Lift* lift : lifts) delete lift;
	////lifts.clear();
	for (auto it = lifts.begin(); it != lifts.end(); ++it) {
		delete* it;
		it = lifts.erase(it);
	}
	////for (Coin* coin : coins) delete coin;
	////coins.clear();
	for (auto it = coins.begin(); it != coins.end(); ++it) {
		delete* it;
		it = coins.erase(it);
	}
	////for (Mushroom* mushroom : mushrooms) delete mushroom;
	////mushrooms.clear();
	for (auto it = mushrooms.begin(); it != mushrooms.end(); ++it) {
		delete* it;
		it = mushrooms.erase(it);
	}

	// Actualiza el offset del mapa
	ResetMapOffset();
}

Game::~Game()
{
	clearActualLevel();

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	if (tilemap != nullptr)
	{
		delete tilemap;
	}
	if (player != nullptr) {
		delete player;
	}
	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::run()
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
Game::render() const

{	// Pinta los objetos del juego
	SDL_RenderClear(renderer);
	tilemap->render();
	player->render();
	for (const Block* block : blocks) {
		block->render();
	}
	for (const Goomba* goomba : goombas) {
		goomba->render();
	}
	for (const Koopa* koopa : koopas) {
		koopa->render();
	}
	for (const Mushroom* mushroom : mushrooms) {
		mushroom->render();
	}
	for (const Lift* lift : lifts) {
		lift->render();
	}
	for (const Coin* coin : coins) {
		coin->render();
	}

	/*for (const SceneObject* sceneObj : gameList) {
		sceneObj->render();
	}*/

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	tilemap->update();
	player->update();

	//IMPORTANTE SI LO HACEMOS ASI SE PRODUCEN FUGAS DE MEMORIA MEJOR USAR EL OTRO
	//for (Block* block : blocks) {
	//	block->update();
	//	if (!block->isAlive()) delete block;
	//}

	/*for (SceneObject* sceneObj : gameList) {
		sceneObj->update();
	}*/

	//Actualiza y elimina bloques
	for (auto it = blocks.begin(); it != blocks.end();) {
		(*it)->update();
		if (!(*it)->isAlive()) {
			delete* it;
			it = blocks.erase(it);
		}
		else ++it;
	}
	
	// Actualiza y elimina Goombas
	for (auto it = goombas.begin(); it != goombas.end();) {
		(*it)->update();
		if (!(*it)->isAlive()) {
			delete* it;
			it = goombas.erase(it);
		}
		else ++it;
	}

	// Actualiza y elimina Koopas
	for (auto it = koopas.begin(); it != koopas.end();) {
		(*it)->update();
		if (!(*it)->isAlive()) {
			delete* it;                      
			it = koopas.erase(it);            
		}
		else ++it;
	}

	// Actualiza lifts
	for (auto it = lifts.begin(); it != lifts.end(); ++it) {
		(*it)->update();
	}

	// Actualiza y elimina Mushrooms
	for (auto it = mushrooms.begin(); it != mushrooms.end();) {
		(*it)->update();
		if (!(*it)->isAlive()) {
			delete* it;                      
			it = mushrooms.erase(it);        
		}
		else ++it;                             
	}

	// Actualiza y elimina Mushrooms
	for (auto it = coins.begin(); it != coins.end();) {
		(*it)->update();
		if (!(*it)->isAlive()) {
			delete* it;
			it = coins.erase(it);
		}
		else ++it;
	}
}

int Game::getMapOffset() {
	return mapOffset;
};

void
Game::handleEvents()
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
Game::checkPlayerCollision(const SDL_Rect& rect, bool fromPlayer) {
	//fromPlayer se encargara de comprobar si viene de arriba o de abajo
	//rect es el rectangulo de la interseccion provocada entre dos objetos

	Collision colision = { false,false,{0,0,0,0} };

	// Primero verificamos colisión con el tilemap
	colision = tilemap->hit(rect, fromPlayer);
	if (colision.collides) return colision;
	
		
	// Luego verificamos colisión con cada bloque
	for (Block* block : blocks) {
		colision = block->hit(rect, fromPlayer);
		if (block->ObtainObject()) {
			mushrooms.push_back(new Mushroom(this, block->getRect()));
			block->itemObtained();
		}
			
		if (colision.collides) return colision;
	}

	if (!mushrooms.empty()) {
		for (Mushroom* mushroom : mushrooms) {
			colision = mushroom->hit(rect, fromPlayer);
			if (colision.collides) {
				player->TransformacionSuperMario();
				return colision;
			}
		}
	}

	for (Goomba* goomba : goombas) {
		colision = goomba->hit(rect, fromPlayer);
		if (colision.damages) return colision;
	}

	for (Koopa* koopa : koopas) {
		colision = koopa->hit(rect, fromPlayer);
		if (colision.damages) return colision;
	}

	for (Lift* lift : lifts) {
		colision = lift->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}

	for (Coin* coin : coins) {
		colision = coin->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}

	/*for (SceneObject* sceneObj : gameList) {
		colision = sceneObj->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}*/

	return colision;
}

Collision
Game::checkEnemyCollision(const SDL_Rect& rect, bool fromPlayer) {
	
	Collision colision = { false,false,{0,0,0,0} };

	colision = tilemap->hit(rect, fromPlayer);
	if (colision.collides) return colision;

	for (Block* block : blocks) {
		colision = block->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}
	/*for (SceneObject* sceneObj : gameList) {
		colision = sceneObj->hit(rect, fromPlayer);
		if (colision.collides) return colision;
	}*/

	return colision;
}

//AQUI ESTAN LOS METODOS PUBLICOS ADICIONALES, NECESARIOS PARA LA LOGICA DEL JUEGO PERO NO ESPECIFICADOS EN ENUNCIADO
//Son necesarios todos, pero podriamos prescindir de alguno para optimizar codigo y no hacerlo público todo

void Game::setMapOffset(int playerOffset) {
	mapOffset += playerOffset;
}

void Game::ResetMapOffset() {
	mapOffset = 0;
}

//Vector2D<int> Game::getPlayerPosition() const {
//	return player->getPosition();
//}