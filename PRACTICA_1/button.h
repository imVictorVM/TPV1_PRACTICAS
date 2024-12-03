#pragma once

#include <SDL.h>
#include "Texture.h"
#include <vector>
#include <functional>

#include "Vector2D.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "checkML.h"

using CallBack = std::function<void(void)>;

//Oyente de eventos del botón (click).
class ButtonListener {
public:
	virtual void handleClick() = 0;
};

//Boton que emite eventos con ButtonListener
class button : public GameObject, public EventHandler
{
private:
	SDL_Rect boundingBox;
	bool hover;
	bool onPoint;
	Vector2D<float> position;
	Texture* buttonTexture;
	Texture* mushroomTexture;

	std::vector<ButtonListener*> clickListener; //lista de oyentes
	std::list<CallBack> callbacks;

	void emit() const; //transmite el evento de cick a todos los oyentes
public:
	button(PlayState* g, SDL_Rect box, Vector2D<float>position, Texture* buttonTexture, Texture* mushroomTexture);
	//~button(); 

	void connect(CallBack rCallback);
	void render() const override;
	void update() override;
	void addClickListener(ButtonListener* lis);
};

