#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>

#include "Color.hpp"

class Object
{
    public:
        Object(int width, int height, float x, float y, SDL_Color color = Color::Grey());
        void DrawRect(SDL_Renderer* renderer);
        bool Collides(Object* object);

    public:
        static bool OnCollision(Object* a, Object* b);

    public:    
        inline int Right() { return (int)Position.x + Width; }
        inline int Left() { return (int)Position.x; }
        inline int Top() { return (int)Position.y; }
        inline int Bottom() { return (int)Position.y + Height; }

    public:
        SDL_FPoint Position;
        SDL_Color Color;
        int Width;
        int Height;
};

#endif