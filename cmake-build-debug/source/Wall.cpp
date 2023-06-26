#include "../headers/Wall.h"

Wall::Wall(Vector2f position,Vector2f size){
    wallShape.setSize(size);
    wallShape.setFillColor(Color(1,0,39));
    wallShape.setPosition(position);
}

RectangleShape Wall::getShape() {
    return wallShape;
}