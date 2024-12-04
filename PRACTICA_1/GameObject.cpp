#include "GameObject.h"
#include "GameState.h"

GameObject::GameObject(GameState* g) {
	gamePointer = g;
}

GameObject::~GameObject() {
	//delete gamePointer;
}

void GameObject::setListAnchor(GameList<GameObject>::anchor&& setter)
{
	anc = std::move(setter);
}
