#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <string>
#include <sdl.h>
#include <sdl_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <globalvariables.h>
#include <LTimer.h>
#include <cstdlib>
#include <LTexture.h>
#include <Object.h>
#include <ball.h>
#include <math.h>
#include <Paddle.h>
#include <Block.h>


int gameLoop();

void loadScore(std::string (*data)[10][2]);

void scoreScreen();

void addScore(int score, std::string name);

bool loadMedia();

void close();

void loadLevel(int level);

void spawnBlock(int x, int y, int type);

//draw given SDL Rect with given thickness
void drawThickRect(SDL_Rect drawRect, int thickness);

//return pointer to a texture
LTexture* getTexture(int type);



std::string getName();

#endif // GAMESTATES_H
