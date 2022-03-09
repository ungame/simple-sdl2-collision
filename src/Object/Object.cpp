#include <SDL2/SDL.h>

#include "Object.hpp"
#include "Color.hpp"

Object::Object(int width, int height, float x, float y, SDL_Color color)
{
    Position = { x, y };
    Color = color;
    Width = width;
    Height = height;
}

void Object::DrawRect(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_Rect rect = { (int)Position.x, (int)Position.y, Width, Height };
    SDL_RenderFillRect(renderer, &rect);
}

bool Object::OnCollision(Object* a, Object* b)
{
    if(a->Bottom() <= b->Top())
        return false;

    if(a->Top() >= b->Bottom())
        return false;

    if(a->Right() <= b->Left())
        return false;

    if(a->Left() >= b->Right())
        return false;

    return true;
}