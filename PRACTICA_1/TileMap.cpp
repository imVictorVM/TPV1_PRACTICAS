#include "TileMap.h"
#include "Game.h"
#include <fstream>

using namespace std;

TileMap::TileMap(const string& mapa, Game* game) : game(game), patrones(game->getTexture(Game::BACKGROUND)){

	ifstream entrada(mapa);
	if (!entrada.is_open()) throw new exception("Error leyendo archivo");
	while (entrada) {
		char cAux = ',';
		int c = 0;
		vector<int> aux;
		while (cAux == ',') {
			entrada >> c;
			aux.push_back(c);
			cAux = entrada.get();
		}
		matriz.push_back(aux);
	}
}


void 
TileMap::render() const
{

	// atributos de TileMap :
	// matriz : vector<vector<int>> indices; 
	// patrones : Texture* background;  


	// constantes estáticas en Game:
	//constexpr int TILE_SIDE = 32;  
	//constexpr int WINDOW_WIDTH = 18;
	//constexpr int WINDOW_HEIGHT = 16;

	// atributo de Game
	int mapOffset = game->getMapOffset();  

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / Game::TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % Game::TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = Game::TILE_SIDE;
	rect.h = Game::TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < Game::WINDOW_WIDTH + 2; ++i) {
		for (int j = 0; j < Game::WINDOW_HEIGHT; ++j) {
			// Índice en el conjunto de patrones de la matriz de índices
			//int indice = indices[x0 + i][j];
			int indice = matriz[j][i+x0];
			if (indice != -1) {
				// Separa número de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * Game::TILE_SIDE;
				rect.y = j * Game::TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				//background->renderFrame(rect, fy, fx);
				patrones->renderFrame(rect, fy, fx);
			}

		}
	}
}

void 
TileMap::update() {

}

void
TileMap::hit() {

}