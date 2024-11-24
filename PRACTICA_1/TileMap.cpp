#include "checkML.h"
#include "TileMap.h"
#include "Game.h"
#include "Collision.h"
#include <fstream>

using namespace std;

TileMap::TileMap(const string& mapa, Game* game) : SceneObject(game) {

	patrones = game->getTexture(Game::BACKGROUND);
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
			if (j < matriz.size() && i + x0 < matriz[j].size()) {
				int indice = matriz[j][i + x0];
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
}

void 
TileMap::update() {
	if (game->getPlayerPosition().getY() >= 470) game->ResetMapOffset();
	//if (game->getPlayerPosition().getX() > Game::WINDOW_WIDTH / 2 && game->getPlayerDirection().getX() > 0) game->setMapOffset(Game::getMapOffset() +=
}

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	vector<vector<int>> matrix = matriz; // Atributos de TileMap
	Texture* texture = game->getTexture(Game::BACKGROUND);
	Collision colision = { false, false, {0, 0, 0, 0} };

	constexpr int OBSTACLE_THRESHOLD = 4; // Constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / Game::TILE_SIDE;
	int col0 = rect.x / Game::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / Game::TILE_SIDE;

	for (int row = row0; row <= row1; ++row) {
		for (int col = col0; col <= col1; ++col) {
			if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size()) {
				int indice = matrix[row][col];
				if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD) {
					SDL_Rect tileRect = {
						col * Game::TILE_SIDE,
						row * Game::TILE_SIDE,
						Game::TILE_SIDE,
						Game::TILE_SIDE
					};
					//std::cout << "Rectángulo del tile: (" << tileRect.x << ", " << tileRect.y << ", " << tileRect.w << ", " << tileRect.h << ")\n";
					SDL_Rect intersection;
					if (SDL_IntersectRect(&rect, &tileRect, &intersection)) {
						//std::cout << "¡Colisión detectada! Intersección: (" << intersection.x << ", " << intersection.y << ", " << intersection.w << ", " << intersection.h << ")\n";
						colision.collides = true;
						colision.intersection = intersection;
						return colision;
					}
				}
			}
		}
	}
	// No hay colisión
	return colision;

}