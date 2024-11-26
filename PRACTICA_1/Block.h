#pragma once

#include "SceneObject.h"


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
	Type type;
	Action action;
	bool object;

public:

	Block(Game* game, std::istream& atributos);

	~Block();

	void update() override;

	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;


	bool ObtainObject();

	void itemObtained();

};

