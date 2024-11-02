#pragma once
#include "Vector2D.h"
#include "Game.h"

class Block
{
private:
	Vector2D<int> position;
	Texture* TextureBlock;
	enum Type
	{
		normal,
		surprise,
		empty,
		hidden
	};
	enum Action {
		powerup,
		coin
	};
	Game* game;

public:

	Block();

	void Render() const;

	void Update();

	bool hit();

};

