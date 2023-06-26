#include "../headers/Apple.h"

Apple::Apple() {
    Vector2f startingPosition(450,300);
    sprite.setSize(Vector2f(20,20));
    sprite.setFillColor(Color(128,0,0));
    sprite.setPosition(startingPosition);
}
void Apple::setPosition(Vector2f *newPosition) {
    sprite.setPosition(*newPosition);
}
RectangleShape Apple::getSprite() {
    return sprite;
}