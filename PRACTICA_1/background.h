#pragma once

#include "GameObject.h"
#include "Texture.h"

class background : public GameObject {
private:
    Texture* texture;
    
    int xPos;
    int yPos;
    int w;
    int h;
public:
    background(GameState* gameState, Texture* texture,int x, int y, int widht, int height);
    virtual ~background();
    void setTexture(Texture* newTexture);
    virtual void update() override;
    virtual void render() const override;
};

