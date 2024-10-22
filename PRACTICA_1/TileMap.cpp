#include "TileMap.h"
#include <fstream>

using namespace std;

TileMap::TileMap(string mapa){
	ifstream entrada(mapa);
	if (!entrada.is_open()) throw new exception("Error leyendo archivo");
	char c;
	entrada >> c;
	entrada.get() + '\n';
}


void 
TileMap::render() const
{
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;  // atributo de TileMap

	constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	constexpr int WINDOW_WIDTH = 18;
	constexpr int WINDOW_HEIGHT = 16;

	int mapOffset;  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) {
		for (int j = 0; j < WINDOW_HEIGHT; ++j) {
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = indices[x0 + i][j];
			if (indice != -1) {
				// Separa número de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * TILE_SIDE;
				rect.y = j * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				background->renderFrame(rect, fy, fx);
			}

		}
	}
}