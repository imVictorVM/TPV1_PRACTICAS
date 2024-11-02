#pragma once

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"
//#include "Dog.h"
#include "TileMap.h"
#include "Player.h"
#include "Block.h"

using uint = unsigned int;
//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	static constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	static constexpr int WINDOW_WIDTH = 18;
	static constexpr int WINDOW_HEIGHT = 16;

	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIANO,
		BLOCK,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:

	//mapoffset
	int mapOffset = 0;
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool seguir;

	// Objetos del juego
	//Dog* perro;
	TileMap* tilemap = nullptr;
	Player* player = nullptr;
	Block* blocks = { nullptr };
	

public:
	void run();

	void update();
	void render() const;
	void handleEvents();
	void loadObjectMap();

	int getMapOffset();
	void setMapOffset(int playerOffset);

	Texture* getTexture(TextureName name) const;

	// Constante globales
	static constexpr uint WIN_WIDTH = 600;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 50;

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}


