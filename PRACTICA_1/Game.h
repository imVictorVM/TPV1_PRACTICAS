#pragma once

// Biblioteca estándar de C++
#include <array>
#include <vector>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"
#include "Collision.h"

#include "gameStateMachine.h"
#include "SceneObject.h"
#include "gameList.h"

class Block;
class Goomba;
class Koopa;
class Mushroom;
class Lift;
class Coin;

using uint = unsigned int;
//
// Clase que representa el juego y controla todos sus aspectos
//
class Game : private GameStateMachine
{
public:
	//using GameStateMachine::pushState();
	static constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	static constexpr int WINDOW_WIDTH = 18;
	static constexpr int WINDOW_HEIGHT = 16;

	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIANO,
		BLOCK,
		GOOMBA,
		KOOPA,
		MUSHROOM,
		SUPERMARIANO,
		LIFT,
		COIN,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
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
	//TileMap* tilemap = nullptr;
	//Player* player = nullptr;
	//std::vector<Block*> blocks;
	//std::vector<Goomba*> goombas;
	//std::vector<Koopa*> koopas;
	//std::vector<Lift*> lifts;
	//std::vector<Coin*> coins;
	//std::vector<Mushroom*> mushrooms;
	//GameList<SceneObject> gameList;


public:
	//void run();
	//
	//void update();
	//void render() const;
	//void handleEvents();
	//void clearActualLevel();
	//void loadNextLevel();
	//void loadObjectMap(const std::string& mapFile, const std::string& objectFile);
	//int getMapOffset();
	//Collision checkPlayerCollision(const SDL_Rect& rect, bool fromPlayer);
	//Collision checkEnemyCollision(const SDL_Rect& rect, bool fromPlayer);

	//AÑADIDOS PERO NO ESPECIFICAOS EN ENUNCIADO
	//void setMapOffset(int playerOffset);
	//void ResetMapOffset();
	//Vector2D<int> getPlayerPosition() const;
	// Constante globales
	static constexpr uint WIN_WIDTH = 600;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 50;

	Texture* getTexture(TextureName name) const;

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}


