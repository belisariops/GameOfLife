//
// Created by belisariops on 6/15/16.
//

#include "Window.h"
#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

Window* Window::window=NULL;

Window :: Window(int width, int height) {
    SCREEN_WIDTH=width;
    SCREEN_HEIGHT=height;
    SCREEN_FPS = 30;
    SCREEN_TICK_PER_FRAME = 1000/SCREEN_FPS;
    quitState =false;
    init();
}

void Window :: init() {


    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Create renderer for window
            this->gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
            }
        }
    }

}

Window :: ~Window() {

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

Window* Window ::getInstance() {
    if (window == NULL)
        window = new Window(1280,720);
    return window;
}

bool Window ::getQuitState() {
    return this->quitState;
}

void Window ::setQuitState(bool boolean) {
    this->quitState = boolean;
}

void Window :: update() {
    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(this->gRenderer, 200, 200, 200, 255);

    SDL_RenderPresent(this->gRenderer);
}

SDL_Renderer * Window::getRenderer() {
    return this->gRenderer;
}

int Window ::getScreenTicks() {
    return this->SCREEN_TICK_PER_FRAME;
}