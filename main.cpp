#include <iostream>
#include "Window.h"
#include "Canvas.h"

int main() {

    /* SDL2 Singleton Window */
    Window *window = Window :: getInstance();

    /* Variable to register all the events in the window */
    SDL_Event event;

    Canvas canvas = Canvas(36,64,720, 1280);

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

        window->update();
        // Clear the entire screen to our selected color.
        SDL_RenderClear(window->getRenderer());
        SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 0, 0, 0, 200);
        canvas.draw();


    } while (!window->getQuitState());

    return 0;
}