#pragma once
struct Collision {
    bool collides;
    bool damages;
    SDL_Rect intersection; // Rectángulo de intersección para ajustes

    operator bool() const { return collides; }
};