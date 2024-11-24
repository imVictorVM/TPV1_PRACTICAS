#include "GameObject.h"
#include "Game.h"
GameObject::GameObject(Game* g) {
	gamePointer = g;
}

GameObject::~GameObject() {
	//delete gamePointer;
}