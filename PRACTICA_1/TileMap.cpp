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
	//SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}