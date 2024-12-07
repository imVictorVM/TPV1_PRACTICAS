#pragma once

#include "GameObject.h"
#include "Texture.h"

class background : public GameObject {
private:
    Texture* texture;
public:
    background(GameState* gameState, Texture* texture);
    virtual ~background();
    void setTexture(Texture* newTexture);
    virtual void update() override;
    virtual void render() const override;
};

