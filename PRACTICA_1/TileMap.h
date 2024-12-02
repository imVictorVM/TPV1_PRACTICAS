#pragma once

#include "SceneObject.h"

class PlayState;
class Game;

class TileMap : public SceneObject
{

	std::vector<std::vector<int>> matriz;

public:
	TileMap(const std::string& mapa, PlayState* game);

	void render() const override;

	void update() override;

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;
};

