#include "checkML.h"
#include "TileMap.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

TileMap::TileMap(const string& mapa, PlayState* gameState) : SceneObject(gameState) {

	playState = gameState;

	texture = gameState->getGame()->getTexture(Game::BACKGROUND);
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
	int mapOffset = playState->getMapOffset();  

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / PlayState::TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % PlayState::TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = PlayState::TILE_SIDE;
	rect.h = PlayState::TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < PlayState::WINDOW_WIDTH + 2; ++i) {
		for (int j = 0; j < PlayState::WINDOW_HEIGHT; ++j) {
			// Índice en el conjunto de patrones de la matriz de índices
			//int indice = indices[x0 + i][j];
			if (j < matriz.size() && i + x0 < matriz[j].size()) {
				int indice = matriz[j][i + x0];
				if (indice != -1) {
					// Separa número de fila y de columna
					int fx = indice % 9;
					int fy = indice / 9;

					rect.x = -d0 + i * PlayState::TILE_SIDE;
					rect.y = j * PlayState::TILE_SIDE;

					// Usa renderFrame para pintar la tesela
					//background->renderFrame(rect, fy, fx);
					texture->renderFrame(rect, fy, fx);
				}
			}
		}
	}
}

void 
TileMap::update() {
	//if (game->getPlayerPosition().getY() >= 470) game->ResetMapOffset();
}

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	vector<vector<int>> matrix = matriz; // Atributos de TileMap
	//Texture* texture = game->getTexture(Game::BACKGROUND);
	Collision colision = { false, false, {0, 0, 0, 0} };

	constexpr int OBSTACLE_THRESHOLD = 4; // Constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / PlayState::TILE_SIDE;
	int col0 = rect.x / PlayState::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / PlayState::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / PlayState::TILE_SIDE;

	for (int row = row0; row <= row1; ++row) {
		for (int col = col0; col <= col1; ++col) {
			if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size()) {
				int indice = matrix[row][col];
				if (indice == 34 || indice == 43) { //Si el jugador toca el mastil es victoria
					cout << "VICTORIA" << endl;
					playState->setCurrentLevel();
					playState->loadNextLevel();
					return colision;
				}
				if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD) { //Si el jugador toca cualquier bloque de colision lo guardamos
					SDL_Rect tileRect = {
						col * PlayState::TILE_SIDE,
						row * PlayState::TILE_SIDE,
						PlayState::TILE_SIDE,
						PlayState::TILE_SIDE
					};
					SDL_Rect intersection;
					if (SDL_IntersectRect(&rect, &tileRect, &intersection)) {
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