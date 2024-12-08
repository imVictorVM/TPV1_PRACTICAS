#include "checkML.h"
#include "button.h"
#include "PlayState.h"
#include "Game.h"
#include "GameObject.h"

button::button(Game* g, Texture* texture, Vector2D<int> pos, int tamX, int tamY) : GameObject(gamePointer), boundingBox(), hover(false), onPoint(false), buttonTexture(texture), mushroomTexture(g->getTexture(Game::MUSHROOM))
{
	boundingBox.x = pos.getX();
	boundingBox.y = pos.getY();
	boundingBox.w = tamX;
	boundingBox.h = tamY;
	std::cout << "Bounding box: (" << boundingBox.x << ", " << boundingBox.y << ", " << boundingBox.w << ", " << boundingBox.h << ")" << std::endl;
	g->connect([this](auto event) { handleEvent(event); });
}

button::~button() {
	for ( ButtonListener* cl : clickListener) {
		delete cl;
	}
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
		color.g = 255;
		color.b = 0;

		int offsetX = 40;
		int offsetY = 6;
		SDL_Rect mushRect;
		mushRect.x = boundingBox.x - offsetX;
		mushRect.y = boundingBox.y - offsetY;
		mushRect.w = game->TILE_SIDE;
		mushRect.h = game->TILE_SIDE;

		buttonTexture->render(boundingBox,color);
		mushroomTexture->render(mushRect);
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