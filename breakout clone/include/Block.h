#ifndef BLOCK_H
#define BLOCK_H

#include <Object.h>
#include <gameStates.h>
#include <math.h>
#include <sdl.h>


//each block is also a node in a linked list
//private members include pointers to next and previous blocks.
//the linked list will be used for both rendering and checking collision with the ball
//the start node will be passed to render/checkcollision and the operation will loop until the entire list is traversed
class ball;

class Block : public Object
{
    public:
        Block(int x, int y, int type = BLOCK1, int width = 50, int height = 15);
        virtual ~Block();

        void render();

        void setNextBlock(Block *nextblock);
        void setPrevBlock(Block *prevblock);
        Block* getNextBlock();
        Block* getPrevBlock();

        int getWidth();
        int getHeight();

        //call this function when it gets hit by the ball.
        void gotHit();

        static Block* firstBlock;

    protected:
    private:
        int _width;
        int _height;
        int _hp;
        Block * _nextBlock;
        Block * _prevBlock;
        LTexture *_crackTexture;
};

#endif // BLOCK_H
