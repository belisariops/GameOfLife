#include <iostream>
#include "Window.h"
#include "Canvas.h"

int main() {

    /* SDL2 Singleton Window */
    Window *window = Window :: getInstance();

    /* Variable to register all the events in the window */
    SDL_Event event;

    /*Canvas that has the Conways Game of Life logic */
    Canvas canvas = Canvas(36,64,720, 1280);

    Timer fpsTimer;
    Timer capTimer;
    fpsTimer.start();

    /*Game loop*/
    do {
        capTimer.start();
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
        canvas.update();
        canvas.draw();

        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if( frameTicks < window->getScreenTicks() )
        {
            //Wait remaining time
            SDL_Delay( window->getScreenTicks() - frameTicks );
        }
        //cout<< capTimer.getTicks()<<endl;
        //cout<<fpsTimer.getTicks()<<"\n";
        if (fpsTimer.getTicks() >1000.f){
            fpsTimer.start();
        }


    } while (!window->getQuitState());

    return 0;
}