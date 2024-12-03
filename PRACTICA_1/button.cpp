#include "button.h"
#include "PlayState.h"

button::button(PlayState* g, SDL_Rect boundingBox, Vector2D<float> position, Texture* buttonTexture, Texture* mushroomTexture) {
	boundingBox.x = position.getX();
	boundingBox.y = position.getY();
	boundingBox.w = PlayState::TILE_SIDE;
	boundingBox.h = PlayState::TILE_SIDE;
}

void
button::connect(CallBack rCallback) {
	if(rCallback) callbacks.push_back(rCallback);
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
		emit();
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

//void
//button::handleEvent(const SDL_Event& event) {
//	if (onPoint) {
//		emit();
//	}
//}

void
button::addClickListener(ButtonListener* lis) {
	if(lis) clickListener.push_back(lis);
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