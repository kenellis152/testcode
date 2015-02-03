#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <globalvariables.h>


extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;

class LTexture
{
    public:
        //constructor
        LTexture();

        //destructor
        virtual ~LTexture();

        //load image at specified path
        bool loadFromFile(std::string path);

        //creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textcolor);

        //deallocates texture
        void free();

        //set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //set alpha modulation
        void setAlpha(Uint8 alpha);

        //renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        bool loadFont(std::string path);

        void renderTextAt(std::string message, int x, int y, SDL_Color color = {255, 255, 255});

        //gets image dimensions
        int getWidth();
        int getHeight();


    protected:
    private:
        //pointer to texture
        SDL_Texture* mTexture;

        //image dimensions
        int mWidth;
        int mHeight;

        TTF_Font *mFont;
};


#endif // LTEXTURE_H
