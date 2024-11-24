#include "GameObject.h"

GameObject::GameObject(Game* g) {
	gamePointer = g;
}

GameObject::~GameObject() {
	delete gamePointer;
}