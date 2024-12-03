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

using uint = unsigned int;

class PlayState : public GameState
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
		GOOMBA,
		KOOPA,
		MUSHROOM,
		SUPERMARIANO,
		LIFT,
		COIN,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};
private:
	int mapOffset = 0;
	//SDL_Window* window = nullptr;
	//SDL_Renderer* renderer = nullptr;
	//std::array<Texture*, NUM_TEXTURES> textures;
	bool seguir;

	TileMap* tilemap = nullptr;
	Player* player = nullptr;
	std::vector<Block*> blocks;
	std::vector<Goomba*> goombas;
	std::vector<Koopa*> koopas;
	std::vector<Lift*> lifts;
	std::vector<Coin*> coins;
	std::vector<Mushroom*> mushrooms;

	GameList<SceneObject> gameList;

public:
	void run();
	void update();
	void render() const;
	void handleEvents();
	void clearActualLevel();
	void loadNextLevel();
	void loadObjectMap(const std::string& mapFile, const std::string& objectFile);
	int getMapOffset();
	Collision checkPlayerCollision(const SDL_Rect& rect, bool fromPlayer);
	Collision checkEnemyCollision(const SDL_Rect& rect, bool fromPlayer);

	//AÑADIDOS PERO NO ESPECIFICAOS EN ENUNCIADO
	void setMapOffset(int playerOffset);
	void ResetMapOffset();
	//Vector2D<int> getPlayerPosition() const;

	//Texture* getTexture(TextureName name) const;

	// Constante globales
	static constexpr uint WIN_WIDTH = 600;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 50;

	PlayState();
	~PlayState();
};

//inline Texture*
//PlayState::getTexture(TextureName name) const
//{
//	return textures[name];
//}


