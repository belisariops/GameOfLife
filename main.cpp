#include <iostream>
#include "Window.h"
#include "Canvas.h"

int main() {
    /* SDL2 Singleton Window */
    Window *window = Window :: getInstance();

    /* Variable to register all the events in the window */
    SDL_Event event;

    Canvas canvas = Canvas(4,4,720, 1280);

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

        SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 255, 255, 255, 255);
        canvas.draw();
        window->update();

    } while (!window->getQuitState());

    return 0;
}