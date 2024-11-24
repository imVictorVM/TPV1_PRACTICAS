#pragma once

#include "Enemy.h"


class Game;

class Koopa :public Enemy
{
protected:

	//Vector2D<int> position; SceneObject position
	//Vector2D<int> direction; SceneObject direction
	//Texture* texture; SceneObject texture
	//Game* game; 
	//GameObject gamePointer 

	// Atributos SceneObject
	//int frame;
	//int frameRunner;
	//bool frozen;
	//int previousOffset;
	//int velocity;
	//bool ended;
	//int velocityGravity;

public:

	Koopa(Game* game, std::stringstream& atributos);

	//void render() const;

	void update();

	//Collision hit(const SDL_Rect& rect, bool fromPlayer);

	//SDL_Rect getRect() const;

	bool isAlive() const;
};