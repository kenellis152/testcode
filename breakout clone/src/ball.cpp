#include "ball.h"

ball::ball(int x, int y, double velocity, int angle)
{
    //ctor
    _x = x;
    _y = y;
    _r = 5;

    //how to initialize velocity?
    _velocity = velocity;
    _angle = angle;
    _texture = getTexture(BALL);

    _xvel = velocity * std::cos( angle * M_PI / 180);
    printf("x velocity = %f\n", _xvel);
    printf("cosin of 45 degrees: %f\n", std::cos(angle  * M_PI / 180.00));
    _yvel = velocity * std::sin( angle * M_PI / 180);
    printf("y velocity = %f\n", _yvel);
}

ball::~ball()
{
    //dtor
}
void ball::render(int x, int y)
{
    //first determine the x, y coordinates to render it at.
    _texture->render(x, y);

}

void ball::render()
{
    //offset by the radius of the ball
    _texture->render((_x - _r) + GAME_X, (_y - _r) + GAME_Y);
}

void ball::updatePosition(int paddlex, int paddley, int paddlewidth, int paddleheight)
{

    //the argument passed to this function is the ms passed since the last frame
    int xchange = _xvel;
    int ychange = _yvel;
    _x += xchange;
    _y += ychange;

    int moveResult = checkCollision(paddlex, paddley, paddlewidth, paddleheight, xchange, ychange);

    switch(moveResult)
    {
        //collision with bottom of game
        case 1:
            printf("case 1 collision\n");
            _x -= xchange;
            _y -= ychange;
            break;

        //collision with top or sides of game
        case 2:
            printf("case 2 collision\n");
            _x -= xchange;
            _y -= ychange;
            break;

        //collision with top or bottom of block
        case 3:
            printf("case 3 collision\n");
            _x -= xchange;
            _y -= ychange;
            _yvel = -_yvel;
            break;

        //collision with side of block
        case 4:
            printf("case 4 collision\n");
            _x -= xchange;
            _y -= ychange;
            _xvel = -_xvel;
            break;

        //collision with top of paddle
        case 5:
            //determine new vector based on where the ball collides with the paddle
            _yvel = -_yvel;
            printf("case 5 collision \n");
          /*  double ballxdouble = _x;
            double paddlexdouble = paddlex;
            double paddlewidthdouble = paddlewidth;
            _xvel = (ballxdouble - paddlexdouble)/(paddlewidthdouble / 2) * _velocity;
            printf("_xvel = %f\n", _xvel);
            // xvel^2 + yvel^2 = velocity^2 so yvel = sqrt( velocity^2 - xvel^2)
            _yvel = -std::sqrt(_velocity * _velocity - _xvel * _xvel);*/
            break;

    }
}

//return int based on collision result
//this should be called within the updatePosition function so that it is easier to undo the position change in the event of a collision
//decided to also pass xchange and ychange from the update position function so that the move can be undone here if necessary
int ball::checkCollision(int paddlex, int paddley, int paddlewidth, int paddleheight, int xchange, int ychange)
{
    //define collision box
    //SDL_Rect thisball{_x - _r, _y - _r, 2 * _r, 2 * _r};

    int result;

    //next check for collision with bottom of game (return 1)
    if( (_y + _r) > GAME_HEIGHT)
    {
        _yvel = _yvel * -1;

        //if ball is still out of bounds then set the height to game height - 1 manually to resolve the problem
        if(_y + _r > GAME_HEIGHT)
        {
            _y = GAME_HEIGHT - _r - 1;
        }
        return 1;
    }

    //check for collision with top and side of game (return 2)
    //left side check
    if(_x  - _r < 0)
    {
        _xvel = _xvel * -1;
        result = 2;
    }
    //right side check
    if( (_x + _r) > GAME_WIDTH)
    {
        _xvel = _xvel * -1;
        result = 2;
    }
    //top check
    if( _y  - _r < 0)
    {
        _yvel = _yvel * -1;
        result = 2;
    }
    if(result == 2)
    {
        return result;
    }

    //check for collision with top or bottom of block (return 3) or side of block (return 4)
    Block* currentBlock = Block::firstBlock;
    bool stoptraverse = false;
    bool collided = true;
    while(stoptraverse == false)
    {
        if(currentBlock->getNextBlock() == NULL)
            stoptraverse = true;

        //project the two objects to x and y axis

        //y-axis projections
        int ballytop = _y - _r;
        int ballybottom = _y + _r;
        int blockytop = currentBlock->getYPos() - currentBlock->getHeight() / 2;
        int blockybottom = currentBlock->getYPos() + currentBlock->getHeight() / 2;

        //x-axis projections
        int ballxleft = _x - _r;
        int ballxright = _x + _r;
        int blockxleft = currentBlock->getXPos() - currentBlock->getWidth() / 2;
        int blockxright = currentBlock->getXPos() + currentBlock->getWidth() / 2;

        collided = true;

        if(ballytop >= blockybottom)
            collided = false;
        if(ballybottom <= blockytop)
            collided = false;
        if(ballxright <= blockxleft)
            collided = false;
        if(ballxleft >= blockxright)
            collided = false;

        //at this point, if stoptraverse is true then there is no collision
        //if it's false, there was a collision and we need to determine which side it collided on
        if(collided==true)
        {
            currentBlock->gotHit();
            printf("block collision happened\n");
            ballytop -= ychange;
            ballybottom -= ychange;
            ballxleft -= xchange;
            ballxright -= xchange;
            if(ballytop >= blockybottom)
            {
                return 3;
            }
            if(ballybottom <= blockytop)
            {
                return 3;
            }
            if(ballxright <=blockxleft)
            {
                return 4;
            }
            if(ballxleft >= blockxright)
            {
                return 4;
            }
            else
            {
                return 4;
            }
        }

        if(stoptraverse == false)
            currentBlock = currentBlock->getNextBlock();
    }


    //check for collision with paddle (return 5)
    int xdif = std::abs(_x - paddlex);
    int ydif = std::abs(_y - paddley);
    if((xdif < _r + paddlewidth /2) && ydif < (_r + paddleheight / 2))
    {
        //collision has occured
        return 5;
    }

    //if no collision, return 0
    return 0;
}
