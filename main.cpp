#include <iostream>
#include "Window.h"

int main() {
    /* SDL2 Singleton Window */
    Window *window = Window :: getInstance();
    /* Variable to register all the events in the window */
    SDL_Event event;
    /*Game loop*/
    do {

        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                window->setQuitState(true);
            }



        }

    } while (!window->getQuitState());
    return 0;
}