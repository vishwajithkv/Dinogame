#ifndef GAME_OBJECT_CPP
#define GAME_OBJECT_CPP
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;
using namespace std;

class GameObject : public Drawable
{
protected:
    Texture texture;
    Sprite sprite;
    int x;
    int y;

public:
    GameObject(int x, int y, const string asset, int width, int height);
    void draw(RenderTarget &target, RenderStates states) const;
    virtual void update() = 0;
    int getX() const;
    int getY() const;
};

#endif