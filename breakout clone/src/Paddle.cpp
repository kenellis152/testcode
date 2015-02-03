#include "Paddle.h"

Paddle::Paddle()
{
    //ctor
    _width = 75;
    _maxvelocity = 8;
    _velocity = 0;
    _height = 15;
    _texture = getTexture(PADDLE);
    _x = GAME_WIDTH / 2;
    _y = GAME_HEIGHT - 50;
    _thickness = 2;
}

Paddle::~Paddle()
{
    //dtor
}


//change velocity - increment = 1 to add max velocity, -1 to subtract max velocity, something anything else adds/sutracts that amount
void Paddle::changeVelocity(int increment)
{
    if(increment == 1)
        _velocity += _maxvelocity;
    else if(increment == -1)
        _velocity -= _maxvelocity;
   // else
     //   _velocity += increment;
}

//render at position
void Paddle::render()
{


    //define the rect to draw
    //add thickness to x and y so that the outer edge of the boundary of the drawn rectangle is the outer edge of the actual rectange
    SDL_Rect drawRect{_x - (_width / 2) + _thickness + GAME_X, _y - (_height / 2) + _thickness + GAME_Y, _width - 2 * _thickness, _height - 2 * _thickness};

    drawThickRect(drawRect, _thickness);

}

//input was technically already handled in the main key input switch statement where the velocity is modified
//here is where position is updated and collision is checked for against the game boundaries.
int Paddle::handleInput()
{
    //store new x position in newx
    int newx = _x + _velocity;

    //check to see if new x position is out of bounds. if it is make newx edge of game
    if( (newx - _width / 2) < 0)
        newx = 0 + _width / 2 + 1;
    if( (newx + (_width / 2) > GAME_WIDTH))
        newx = GAME_WIDTH - (_width / 2) - 1;

    _x = newx;
}


int Paddle::getWidth()
{
    return _width;
}
int Paddle::getHeight()
{
    return _height;
}
