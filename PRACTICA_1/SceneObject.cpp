#include "checkML.h"

#include "SceneObject.h"

using namespace std;



void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}