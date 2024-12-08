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
#include "SceneObject.h"
#include "gameList.h"
#include "GameState.h"

class Block;
class Goomba;
class Koopa;
class Mushroom;
class Lift;
class Coin;
class PlayState;
class Game;

using uint = unsigned int;

class PlayState : public GameState
{
public:
	static constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	static constexpr int WINDOW_WIDTH = 18;
	static constexpr int WINDOW_HEIGHT = 16;

private:
	int mapOffset = 0;
	//SDL_Window* window = nullptr;
	SDL_Renderer* renderer; // = game->getRenderer();
	bool seguir;


	Game* game;
	TileMap* tilemap = nullptr;
	Player* player = nullptr;
	GameList<SceneObject> gameList;

public:
	//void run();
	void update();
	void render() const;
	void handleEvents();
	void clearActualLevel();
	void loadNextLevel();
	void loadObjectMap(const std::string& mapFile, const std::string& objectFile);
	int getMapOffset() const;
	Collision checkPlayerCollision(const SDL_Rect& rect, bool fromPlayer);
	Collision checkEnemyCollision(const SDL_Rect& rect, bool fromPlayer);

	//AÑADIDOS PERO NO ESPECIFICAOS EN ENUNCIADO
	void setMapOffset(int playerOffset);
	void ResetMapOffset();

	// Constante globales
	static constexpr uint WIN_WIDTH = 600;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 50;

	PlayState(Game* game);
	~PlayState();
};


