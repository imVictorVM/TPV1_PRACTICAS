#include <string>
#include <fstream>
#include <sstream>
#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Collision.h"

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
const string textureRoot = "../assets/imgs/";

// Especificación de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	TextureSpec{"mario.png", 12, 1},
	TextureSpec{"blocks.png", 6, 1},
	TextureSpec{"goomba.png",3,1},
	TextureSpec{"koopa.png",4,1},
	TextureSpec{"mushroom.png",1,1},
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

	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255); //color azul

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
	tilemap = new TileMap("../assets/maps/world1.csv", this);
	//stringstream ss;
	//player = new Player(this,ss);
	loadObjectMap();
}

void
Game::loadObjectMap() {
	const string DEFAULT_MAP = "../assets/maps/world1.txt";

	// Carga el mapa
	ifstream file(DEFAULT_MAP);

	if (!file.is_open()) return; //false

	string line;

	while (getline(file, line)) {
		
		stringstream lineStream(line);
		char let;
		lineStream >> let;

		switch (let) {
		case 'M':
			if (player == nullptr) player = new Player(this, lineStream);
			break;
		case 'B':
			blocks.push_back(new Block(this, lineStream));
			break;
		case 'G':
			//goomba
			break;
		case 'K':
			//koopa
			break;
		}
	}
	file.close();
}

Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;
	for (Block* block : blocks) {
		delete block;
	}
	blocks.clear();
	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

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
{
	SDL_RenderClear(renderer);
	tilemap->render();
	player->render();
	for (const Block* block : blocks) {
		block->render();
	}
	// Pinta los objetos del juego
	//textures[BACKGROUND]->render();
	//perro->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	//perro->update();
	tilemap->update();
	player->update();
	for (Block* block : blocks) {
		block->update();
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
Game::checkCollision(const SDL_Rect& rect, bool fromPlayer) {
	//fromPlayer se encargara de comprobar si viene de arriba o de abajo
	//rect es el rectangulo de la interseccion provocada entre dos objetos
	//
	//Collision colision;
	//colision.collides = false;
	//colision.damages = false;
	//SDL_Rect playerRect = player->getRect();
	//
	////Accedemos a todos los tiles del mapa y comparamos
	//colision.collides = tilemap->hit(rect, fromPlayer);
	//for (Block* block : blocks) {
	//	colision.collides = block->hit(rect, fromPlayer);
	//}
	//
	//return colision;

	Collision colision;
	return colision;
}

Collision
Game::checkPlayerCollision(const SDL_Rect& rect, bool fromPlayer) {
	//fromPlayer se encargara de comprobar si viene de arriba o de abajo
	//rect es el rectangulo de la interseccion provocada entre dos objetos

	Collision colision;
	colision.collides = false;
	colision.damages = false;
	SDL_Rect playerRect = player->getRect();

	//Accedemos a todos los tiles del mapa y comparamos
	colision = tilemap->hit(rect, fromPlayer);
	for (Block* block : blocks) {
		colision = block->hit(rect, fromPlayer);
	}

	return colision;
}

Collision
Game::checkEnemyCollision(const SDL_Rect& rect, bool fromPlayer) {

}

//AQUI ESTAN LOS METODOS PUBLICOS ADICIONALES, NECESARIOS PARA LA LOGICA DEL JUEGO PERO NO ESPECIFICADOS EN ENUNCIADO
//Son necesarios todos, pero podriamos prescindir de alguno para optimizar codigo y no hacerlo público todo

void Game::setMapOffset(int playerOffset) {
	mapOffset += playerOffset;
}

Vector2D<int> Game::getPlayerPosition() const {
	return player->getPosition();
}

//PARA QUITAR
std::vector<Block*>& Game::getBlocks() {
	return blocks;
}

//PARA QUITAR
int Game::getTile() {
	return tilemap->tileRect(player->getPosition());
}

//PARA QUITAR
Vector2D<int> Game::getPlayerDirection() const {
	return player->getDirection();
}