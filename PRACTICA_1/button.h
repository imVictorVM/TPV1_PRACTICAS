#pragma once

#include <SDL.h>
#include "Texture.h"
#include <vector>
#include <functional>

#include "Vector2D.h"
#include "GameObject.h"
#include "EventHandler.h"
#include "checkML.h"

using SDLEventCallBack = std::function<void(void)>;

//Oyente de eventos del botón (click).
class ButtonListener {
public:
	virtual void handleClick() = 0;
};

//Boton que emite eventos con ButtonListener
class button : public GameObject, public EventHandler
{
private:
	
	Game* game;
	SDL_Rect boundingBox;
	bool hover;
	bool onPoint;
	Vector2D<float> position;
	Texture* buttonTexture;
	Texture* mushroomTexture;

	std::vector<ButtonListener*> clickListener; //lista de oyentes
	std::list<SDLEventCallBack> callbacks;

	void emit() const; //transmite el evento de cick a todos los oyentes
public:
	button(Game* g,Texture* texture, Vector2D<int> pos, int tamX, int tamY);
	~button(); 

	void connect(SDLEventCallBack rCallback);
	void render() const;
	void update();
	void addClickListener(ButtonListener* lis);
	void handleEvent(const SDL_Event& event);
};

