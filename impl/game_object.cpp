#include "headers/game_object.hpp"
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;

GameObject::GameObject(int x, int y, string asset, int width, int height)
{
    this->x = x;
    this->y = y;
    texture.loadFromFile(asset);
    // Set the texture to the sprite
    sprite.setTexture(texture);
    sprite.setScale(width / 100.0f, height / 100.0f);
}

void GameObject::draw(RenderTarget &target, RenderStates states) const
{
    target.draw(sprite, states);
}

int GameObject::getX() const
{
    return x;
}

int GameObject::getY() const
{
    return y;
}