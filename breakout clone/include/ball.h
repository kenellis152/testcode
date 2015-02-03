#ifndef BALL_H
#define BALL_H

#include <Object.h>
#include <gameStates.h>
#include <math.h>
#include <sdl.h>
#include <Block.h>
#include <cmath>


class Block;

class ball : public Object
{
    public:
        //initialize ball with x+y coords, velocity, and angle
        ball(int x, int y, double velocity = 8, int angle = 45);

        //destructor
        virtual ~ball();

        //render at x, y coordinates
        void render(int x, int y);
        //render at current location
        void render();

        //return collision type
        int checkCollision(int, int, int, int,int xchange, int ychange);

        //update position
        void updatePosition(int paddlex, int paddley, int paddlewidth, int paddleheight);

    protected:
    private:
        //radius
        int _r;
        //velocity
        double _velocity;
        //angle
        int _angle;


};

#endif // BALL_H
