#include "LTexture.h"
#include <stdio.h>


extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;

LTexture::LTexture()
{
    //ctor
    mTexture = NULL;
    mWidth = 20;
    mHeight = 20;
}

LTexture::~LTexture()
{
    //dtor
    free();
}

//destroy the texture stored by the wrapper class
void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

//render the texture at given coordinates
void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, clip, & renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}
int LTexture::getHeight()
{
    return mHeight;
}

//load a texture from a file
bool LTexture::loadFromFile(std::string path)
{
    //the final texture
    SDL_Texture* newTexture = NULL;

    //load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );

    }
    else
    {
        //Clear screen
		//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		//SDL_RenderClear( gRenderer );
        //create texture from surface pixels

        //color key for green = 255 blue = 1;
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 1 ));

        //set width and height to surface dimensions
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("unable to create texture from %s\n", path.c_str(), SDL_GetError() );
        }

        //get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

//load from rendered text
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //get rid of preexisting texture
    free();

    //render etxt surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textureText.c_str(), textColor);
    if(textSurface == NULL)
    {
        printf("unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if(mTexture == NULL)
        {
            printf("unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //return success
    return mTexture != NULL;
}

//load font into gFont at the given path
bool LTexture::loadFont(std::string path)
{
    bool success;
    mFont = TTF_OpenFont(path.c_str(), 28);
    if(mFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    return success;
}

void LTexture::renderTextAt(std::string message, int x, int y, SDL_Color color)
{
    loadFromRenderedText(message, color);
    render(x, y);
}
