#ifndef SNAKE_SNAKESECTION_H
#define SNAKE_SNAKESECTION_H

#include<SFML/Graphics.hpp>

using namespace sf;

class SnakeSection {
private:
    RectangleShape section;

public:
    explicit SnakeSection(Vector2f startPosition);
    void setPosition(Vector2f newPosition);

    RectangleShape getShape();
};


#endif //SNAKE_SNAKESECTION_H
