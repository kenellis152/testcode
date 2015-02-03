//stuff that will be used
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

//include the sdl libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <gameStates.h>

#include <globalvariables.h>

extern SDL_Renderer* gRenderer = NULL;
extern SDL_Window* gWindow = NULL;

bool init();

int main(int argc, char* args[])
{
    //initialize sdl and other stuff
    if(!init())
    {
        printf("failed to initialize! Reason: %s", SDL_GetError());
        return 0;
    }


    bool quit = false;
    SDL_Event e;

/*
    //main menu loop
    while(quit==false)
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

            }
        }
    }*/
    gameLoop();

    close();
}

bool init()
{
    bool success = true;

    //start up SDL and other supporting libraries here
    if(SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf("sdl could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
    if(! (IMG_Init(imgFlags) & imgFlags)) //IMG_Init is supposed to return the argument that it is passed if it is succesful
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    if(TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error %s\n", TTF_GetError() );
        return false;
    }

    //create window
    gWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        printf("Window could not be created! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //create renderer for window
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(gRenderer == NULL)
        {
            printf("Renderer could not be created! SDL Error %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //initialize renderer color to white
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            //initialize png loading
            int imgFlags = IMG_INIT_PNG;
            if( !(IMG_Init(imgFlags) & imgFlags) )
            {
                printf("SDL_image could not initialize! SDL_image Error %s\n", IMG_GetError() );
                success = false;
            }
        }
    }

    return success;
}
