#include "gameStates.h"

//initialize textures that will be used
//texture for the ball
LTexture ballTexture, block1Texture, crackTexture;
//game text texture
LTexture gameText;


extern SDL_Renderer* gRenderer;

extern SDL_Window* gWindow;

Block* Block::firstBlock;



int gameLoop()
{
    loadMedia();

    //Initialize game elements

    //Clear screen to black
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
	SDL_RenderClear( gRenderer );
	SDL_RenderPresent( gRenderer) ;

    //quit flag
    bool quit = false;
    //SDL Event handler
    SDL_Event e;

    //keep track of score
    int score = 0;
    //tracks interval between game ticks
    //Uint32 interval = 1000;
    //timer class
    LTimer timer;
    //store the time at last frame
    Uint32 lasttime = 0;
    //store the time changed since last frame
    Uint32 timechange = 0;
    //set text color
    SDL_Color textColor = {255, 255, 255};

    //start the game timer
    timer.start();

    //create game objects
    //create the starting ball
    ball firstball(500, 500);
    //create the player's paddle
    Paddle paddle;
    //create the pointers to start and end of the block linked list
    //Block *firstBlock = NULL;
    //Block *lastBlock = NULL;

    Block *currentBlock = NULL;
    //Block blockno1(100, 100);
    //Block blockno2(200, 100);
    //blockno1.setNextBlock(&blockno2);
    //blockno2.setPrevBlock(&blockno1);

    loadLevel(1);

    //store if game is paused or not
    bool paused = false;
    printf("entering main loop\n");
    //main loop
    while(quit == false)
    {
        //handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            //user requests quit
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            //handle other input here
            if(e.type == SDL_KEYDOWN && e.key.repeat ==0)
            {
                //adjust the velocity
                switch(e.key.keysym.sym)
                {
                    //left arrow key
                    case SDLK_LEFT:
                        paddle.changeVelocity(-1);
                        break;
                    //right arrow key
                    case SDLK_RIGHT:
                        paddle.changeVelocity(1);
                        break;
                }
            }
            else if(e.type == SDL_KEYUP && e.key.repeat ==0)
            {
                //adjust velocity
                switch(e.key.keysym.sym)
                {
                    //left key released
                    case SDLK_LEFT:
                        paddle.changeVelocity(1);
                        break;
                    case SDLK_RIGHT:
                        paddle.changeVelocity(-1);
                        break;
                }
            }

        }

        //update the game time
        timechange = timer.getTicks() - lasttime;
        lasttime = timer.getTicks();

        /* update the game state */

            //update ball position
            //i really wish i just passed a rect or a pointer instead of 4 ints in the form of function calls here, but oh well. too lazy to fix it
            //also pass the pointer to the first block so that the ball can traverse the entire linked list to check for collision against each block

            firstball.updatePosition(paddle.getXPos(), paddle.getYPos(), paddle.getWidth(), paddle.getHeight());

            //going to need to check for collision between paddle and powerups here in the future

            paddle.handleInput();


        //clear screen to black
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        //draw the user interface
       // gameText.loadFromRenderedText("score: " + std::to_string(score), textColor);
        gameText.render(1000, 200);

        //draw the boundary in white with thickness of 5
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_Rect gameBoundary = {GAME_X, GAME_Y, GAME_WIDTH, GAME_HEIGHT};
        drawThickRect(gameBoundary, 5);

        /* draw the game state */
        firstball.render();
        paddle.render();

        if(Block::firstBlock != NULL)
        {
            //traverse the block linked list and render each block
            currentBlock = Block::firstBlock;
            bool stoprender = false;
            while(stoprender == false)
            {
                currentBlock->render();
                if(currentBlock->getNextBlock() == NULL)
                {
                    stoprender = true;
                }
                else
                {
                    currentBlock = currentBlock->getNextBlock();
                }
            }
        }

        //traverse the powerup linked list and render each powerup

        /* render the present screen */
        SDL_RenderPresent(gRenderer);

        if(Block::firstBlock == NULL)
        {
            //no blocks remaining. Game is over
            quit = true;
        }

    }

/*
    //exited the main game loop check for high score or not
    std::string fileData[10][2];

    //load high score data into fileData
    loadScore(&fileData);

    //if score this time is higher than 10th highest score
    if(score > std::stoi(fileData[9][1]))
    {
        //prompt user for name entry:
        std::string name = getName();
        //add it to high score list
        addScore(score, name);
        scoreScreen();
    }*/
    return 0;
}

void loadScore(std::string (*data)[10][2])
{

}
void scoreScreen()
{

}
void addScore(int score, std::string name)
{

}

//prompt the user for their name. max characters of 8
std::string getName()
{
    bool quit = false;
    SDL_Event e;
    std::string input ="";
    SDL_StartTextInput();

    //main menu loop
    while(quit == false)
    {
        //handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            //user requests quit
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            //handle other input here
            if(e.type == SDL_KEYDOWN)
            {
                //handle backspace
                if(e.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0)
                {
                    //lops off character
                    input.pop_back();
                }
                else if(e.key.keysym.sym == SDLK_RETURN && input.length() > 0)
                {
                    SDL_StopTextInput();
                    return input;
                }
                else if(e.key.keysym.sym == SDLK_RETURN && input.length() == 0)
                    printf("did not enter a name!\n");
            }
            else if(e.type == SDL_TEXTINPUT && input.length() < 9)
            {
                input += e.text.text;
            }

        }

        //clear screen to black
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(gRenderer);

        gameText.renderTextAt("new high score!", 200, 175);
        gameText.renderTextAt("enter your name", 200, 200);
        if(input.length() > 0)
            gameText.renderTextAt(input, 200, 225);

        //render the present screen
        SDL_RenderPresent(gRenderer);
    }
}

//load textures, music, etc
bool loadMedia()
{
    if(!ballTexture.loadFromFile("files/ball.png"))
    {
        printf("unable to load blue ball texture!\n ");
        return false;
    }
    if(!block1Texture.loadFromFile("files/block1.png"))
    {
        printf("unable to load blue block1 texture!\n ");
        return false;
    }
    if(!crackTexture.loadFromFile("files/crack.png"))
    {
        printf("unable to load blue crack texture!\n ");
        return false;
    }


    gameText.loadFont("files/PTS75F.ttf");
    return true;
}
void close()
{
    ballTexture.free();
    block1Texture.free();
    crackTexture.free();
    gameText.free();

    IMG_Quit();
    TTF_Quit();
    //MIX_Quit();
    SDL_Quit();
}

LTexture* getTexture(int type)
{
    switch(type)
    {
        //dot texture
        case BALL:
            return &ballTexture;
            break;
       // case PADDLE:
         //   return &paddleTexture;
           // break;
        case BLOCK1:
            return &block1Texture;
            break;
        case CRACK:
            return &crackTexture;
            break;
    }
}

//draw a given rect with given thickness
//note this will automatically use whatever the current render colo is set to
void drawThickRect(SDL_Rect drawRect, int thickness)
{
    SDL_Rect draw;
    for(int i = 0; i < 5; i++)
    {
        draw = {drawRect.x - i, drawRect.y - i, drawRect.w + (2 * i), drawRect.h + (2*i)};
        SDL_RenderDrawRect(gRenderer, &draw);
    }
}

//loads the level, returns a pointer to the first block
void loadLevel(int level)
{

    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            new Block(100 + i * 50, 100 + j * 15, BLOCK1);
        }
    }

}

