#include "Block.h"


Block::Block(int x, int y, int type, int width, int height)
{
    //ctor

    //check if this is the first block or not. if it is, set the static pointer to this
    //if it's not the first block, traverse the list to get the last block
    if(firstBlock == NULL)
        firstBlock = this;
    else
    {
        Block* currentBlock = firstBlock;
        while(currentBlock->getNextBlock() != NULL)
        {
            currentBlock = currentBlock->getNextBlock();
        }
        currentBlock->setNextBlock(this);
        _prevBlock = currentBlock;
    }

    _x = x;
    _y = y;
    _hp = 2;
    _width = width;
    _height = height;
    _texture = getTexture(type);
    _crackTexture = getTexture(CRACK);
    _nextBlock = NULL;
}

Block::~Block()
{
    //dtor



}

void Block::render()
{
    _texture->render(_x - _width / 2 + GAME_X, _y - _height / 2 + GAME_Y);
    if(_hp == 1)
        _crackTexture->render(_x - _width / 2 + GAME_X, _y - _height / 2 + GAME_Y);
}
void Block::setNextBlock(Block *nextblock)
{
    _nextBlock = nextblock;
}
void Block::setPrevBlock(Block *prevblock)
{
    _prevBlock = prevblock;
}

Block* Block::getNextBlock()
{
    return _nextBlock;
}
Block* Block::getPrevBlock()
{
    return _prevBlock;
}

//return width of ball
int Block::getWidth()
{
    return _width;
}

//return height of block
int Block::getHeight()
{
    return _height;
}

//call this function when the block gets hit by a ball. take a pointer to the ball so that its velocity and position can be modified
void Block::gotHit()
{
    _hp -= 1;
    printf("block hp = : %i\n", _hp);
    if(_hp == 0)
    {

        //if there is a previous block in the linked list, link that block to this block's next block and set next block's prev block to this one's previous
        if(_prevBlock != NULL && _nextBlock != NULL)
        {
            //if there is a previous block in the linked list, link that block to this block's next block and set next block's prev block to this one's previous
            _prevBlock->setNextBlock(_nextBlock);
            _nextBlock->setPrevBlock(_prevBlock);
        }
        else if(_prevBlock != NULL && _nextBlock ==NULL)
        {
            //if this is the last block in the list, the previous block is the new last block in the linked list
            _prevBlock->setNextBlock(NULL);
        }
        else if(_prevBlock == NULL && _nextBlock != NULL)
        {
            //if this is the first block and there are more to come, the next block needs to be made into the start of the linked list
            _nextBlock->setPrevBlock(NULL);
            firstBlock = _nextBlock;
        }
        else if(_prevBlock == NULL && _nextBlock == NULL)
        {
            //game is over
            firstBlock = NULL;
        }
        else
        {
            //something is wrong. every case should be covered by previous if statements
            printf("error: linked list is screwed up");
        }
        delete this;

    }

}
