#include "button.h"
#include "PlayState.h"
#include "checkML.h"
#include "Game.h"

button::button(Game* g) : GameObject(g), boundingBox{50,50,200,100}, hover(false), onPoint(false), buttonTexture(), mushroomTexture()
{
	game->connect([this](auto event) { handleEvent(event); });
}

void
button::connect(SDLEventCallBack rCallback) {
	/*if (rCallback)*/ callbacks.push_back(rCallback);
	//Si existe rCallback (usar en caso de errores)
}

void
button::render() const {
	if (onPoint) {
		SDL_Color color;
		color.r = 0;
		color.g = 0;
		color.b = 0;
		buttonTexture->render(boundingBox, color);
		mushroomTexture->render(boundingBox, color);
	}
	else {
		buttonTexture->render(boundingBox);
	}
}

void
button::update() {
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);
	onPoint = SDL_PointInRect(&point, &boundingBox);
}

void
button::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (onPoint) {
			emit();
		}
	}
}

void
button::addClickListener(ButtonListener* lis) {
	/*if(lis)*/ clickListener.push_back(lis);
	//Si existe lis (usar en caso de errores)
}

void button::emit() const {
	// Llamar a todos los oyentes de clickListener
	for (const auto& listener : clickListener) {
		if (listener) {
			listener->handleClick();
		}
	}

	// Llamar a todos los callbacks registrados
	for (const auto& callback : callbacks) {
		callback();
	}
}