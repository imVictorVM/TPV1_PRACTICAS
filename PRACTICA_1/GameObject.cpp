#include "GameObject.h"
#include "GameState.h"
#include "checkML.h"
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
