#include "checkML.h"
#include "Game.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "PlayState.h"

using namespace std;
class TileMap;
class GameStateMachine;

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
	TextureSpec{"nivel1.png",1,1},
	TextureSpec{"nivel2.png",1,1},
	TextureSpec{"salir.png",1,1},
	TextureSpec{"continuar.png",1,1},
	TextureSpec{"volverAlMenu.png",1,1},
	TextureSpec{"portada.png",1,1},
	TextureSpec{"endFondo.jpg",1,1},
	TextureSpec{"gameOver.png",1,1},
	TextureSpec{"hasGanado.png",1,1},
};

Game::Game() : GameStateMachine()
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

	//mapOffset = 0;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	//pushState(new PlayState(this));
	pushState(new MainMenuState(this));
}

Game::~Game()
{
	//clearActualLevel();

	// Elimina las texturas
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::emit(const SDL_Event& event) const {
	for (const auto& callback : eventCallbacks) {
		callback(event); // Llama a cada callback registrado
	}
}

void
Game::run()
{

	// Bucle principal del juego
	while (!empty()) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		SDL_Event events;
		while (SDL_PollEvent(&events)) { // Maneja los eventos de la SDL
			handleEvent(events);
		}

		update();       // Actualiza el estado de los objetos del juego
		SDL_RenderClear(renderer);
		render();       // Dibuja los objetos en la venta;
		SDL_RenderPresent(renderer);
		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::connect(const SDLEventCallback& cb) {
	eventCallbacks.push_back(cb);
}

void
Game::changeState(GameState* newState) {
	replaceState(std::shared_ptr<GameState>(newState)); //Accedemos al metodo privado 
}

void
Game::pushNewState(GameState* newState) {
	pushState(std::shared_ptr<GameState>(newState)); //Accedemos al metodo privado
}

void
Game::popCurrentState() {
	popState(); //Accedemos la metodo privado
}

void
Game::exitStates() {
	exit();
}