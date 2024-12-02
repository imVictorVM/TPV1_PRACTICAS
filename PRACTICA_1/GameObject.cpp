#include "GameObject.h"
#include "Game.h"
#include "PlayState.h"
GameObject::GameObject(PlayState* g) {
	gamePointer = g;
}

GameObject::~GameObject() {
	//delete gamePointer;
}