#pragma once

// Biblioteca estándar de C++
#include <array>
#include <vector>
#include <string>

// Biblioteca SDL
#include <SDL.h>
#include <functional>
#include "checkML.h"

// Nuestras clases
#include "Texture.h"
#include "TileMap.h"
#include "Collision.h"

#include "gameStateMachine.h"

using uint = unsigned int;
using SDLEventCallback = std::function<void(const SDL_Event&)>;
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
		NIVEL1,
		NIVEL2,
		SALIR,
		CONTINUAR,
		VOLVERALMENU,
		PORTADA,
		ENDFONDO,
		GAMEOVERTEXT,
		GAMEWINTEXT,
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
	//bool seguir;
	std::list<SDLEventCallback> eventCallbacks;

	void emit(const SDL_Event& event) const;
public:
	void run();

	static constexpr uint WIN_WIDTH = 600;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 50;

	Texture* getTexture(TextureName name) const;

	Game();
	~Game();
	SDL_Renderer* getRenderer();
	void connect(const SDLEventCallback& cb);

	void changeState(GameState* newState);
	void pushNewState(GameState* newState);
	void popCurrentState();
	void exitStates();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

inline SDL_Renderer*
Game::getRenderer() {
	return renderer;
}
//LO USARA PLAYSTATE


