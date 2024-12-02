#pragma once

#include <SDL.h>
#include "Texture.h"
#include <vector>

#include "GameObject.h"
#include "EventHandler.h"

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

	std::vector<ButtonListener*> clickListener; //lista de oyentes
	void emit() const; //transmite el evento de cick a todos los oyentes
public:
	button(/*Game* game*/); //HEREDADO EL PUNTERO EN GAMEOBJECT
	~button(); 

	//void update(); HEREDADO EN GAMEOBJECT
	//void render() const; HEREDADO EN GAMEOBJECT
	//void handleEvent(const SDL_Event& event); HEREDADO COMO METODO VIRTUAL EN EventHandler
	void callBack();
	void addClickListener(ButtonListener* lis);
};

