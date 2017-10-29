#include <iostream>
#include "Window.h"
#include "CPUCanvas.h"
#include "OpenCLCanvas.h"

int main() {

    /* SDL2 Singleton Window */
    Window *window = Window :: getInstance();

    /* Variable needed to get all events*/
    SDL_Event event;

    /*Canvas that has the Conways Game of Life logic */
    CPUCanvas canvas = CPUCanvas(36,64,720, 1280);
    OpenCLCanvas openCLCanvas = OpenCLCanvas(36,64,720,1280);

    Timer fpsTimer;
    Timer capTimer;
    fpsTimer.start();
    std::cout << (!-1) << std::endl;
    /*Game loop*/
    do {
        capTimer.start();
        //Read events
        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                window->setQuitState(true);
            }

        }

        //Update SDL2 window, to render the draw cavnas
        window->update();


        // Clear the entire screen to our selected color.
        SDL_RenderClear(window->getRenderer());
        SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 0, 0, 0, 200);

        //Update cells in canvas and then draw the living ones
//        canvas.update();
//        canvas.draw();

        openCLCanvas.draw();
        openCLCanvas.update();
        //If frame finished early, add a delay so it can be seen
        int frameTicks = capTimer.getTicks();
        if( frameTicks < window->getScreenTicks() )
        {
            //Wait remaining time
            SDL_Delay( window->getScreenTicks() - frameTicks );
        }



    } while (!window->getQuitState());

    delete(window);
    return 0;
}