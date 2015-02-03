#ifndef PADDLE_H
#define PADDLE_H

#include <Object.h>
#include <gameStates.h>
#include <math.h>
#include <sdl.h>


class Paddle : public Object
{
    public:
        Paddle();
        virtual ~Paddle();

        //handle input
        int handleInput();
        //render at position
        void render();
        //change velocity by passed increment
        void changeVelocity(int increment);

        int getWidth();
        int getHeight();


    protected:
    private:
        int _width;
        int _height;
        double _velocity;
        double _maxvelocity;
        int _thickness;
};

#endif // PADDLE_H
