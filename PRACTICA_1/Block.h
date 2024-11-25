#pragma once

#include "SceneObject.h"
#include <vector>
#include <sstream>

class Game;

class Block : public SceneObject
{
public:
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
private:
	//Vector2D<int> position; position del SceneObject
	//Texture* texture;
	Type type;
	Action action;
	//Game* game; //gamePointer del GameObject
	//int frameBlock; frame del SceneObject
	//int previousOffset; previousOffset del SceneObject
	bool object;
	//bool ended; ended del SceneObject
public:

	Block(Game* game, std::istream& atributos);

	//~Block();

	//void render() const override;

	void update() override;

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	//SDL_Rect getRect() const;

	bool ObtainObject();

	void itemObtained();

	//bool isAlive() const;
};

