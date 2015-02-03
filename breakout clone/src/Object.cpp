#include "Object.h"

Object::Object(int x, int y)
{
    //ctor
    _x = x;
    _y = y;
    //_velocity = 0;
    //_angle = 0;
}

Object::~Object()
{
    //dtor
}
void Object::render(int x, int y)
{

}

int Object::getXPos()
{
    return _x;
}
int Object::getYPos()
{
    return _y;
}
