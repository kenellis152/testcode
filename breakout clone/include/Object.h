#ifndef OBJECT_H
#define OBJECT_H

#include <LTexture.h>


class Object
{
    public:
        Object(int x = 100, int y =100);

        virtual ~Object();



        //render object
        virtual void render(int x, int y);
        //return x position
        int getXPos();
        //return y position
        int getYPos();

    protected:
        //x position
        int _x;
        //y position
        int _y;

        //these should be declared in the subclasses. not all objects have "velocity" or "angle"
        //velocity
        //double _velocity;
        //angle of velocity
        //int _angle;

        //velocity components
        //makes sense to break out velocity components into x, y instead of just storing angle + magnitude so that it doesn't have to be recalculated for every frame
        double _xvel;
        double _yvel;

        //pointer to draw texture
        LTexture *_texture;

    private:

};

#endif // OBJECT_H
