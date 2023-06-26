#include "../headers/SnakeSection.h"

SnakeSection::SnakeSection(Vector2f startPosition) {
    section.setSize(Vector2f(20,20));
    section.setFillColor(Color::White);
    section.setPosition(startPosition);
}


void SnakeSection::setPosition(Vector2f newPosition) {
    section.setPosition(newPosition);
}

RectangleShape SnakeSection::getShape() {
    return section;
}
