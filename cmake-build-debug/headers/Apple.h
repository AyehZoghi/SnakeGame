#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Apple {
private:
    RectangleShape sprite;

public:
    Apple();

    void setPosition(Vector2f *newPosition);
    RectangleShape getSprite();
};


#endif //SNAKE_APPLE_H
