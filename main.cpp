#include <iostream>
#include "Window.h"
#include "CPUCanvas.h"
#include "OpenCLCanvas.h"
#include "CUDACanvas.h"

int main() {

    /* SDL2 Singleton Window */
    Window *window = Window :: getInstance();

    /* Variable needed to get all events*/
    SDL_Event event;
    int x = 1280;
    int y = 1280;
    /*Canvas that has the Conways Game of Life logic */
    CPUCanvas canvas = CPUCanvas(x,y,720, 1280);
    OpenCLCanvas openCLCanvas = OpenCLCanvas(x,y,720,1280);
    CUDACanvas cudaCanvas = CUDACanvas(x,y,720,1280);

    Timer fpsTimer;
    Timer capTimer;
    fpsTimer.start();
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

        //Update SDL2 window, to render the drew canvas
        window->update();


        // Clear the entire screen to our selected color.
        SDL_RenderClear(window->getRenderer());
        SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 0, 0, 0, 200);
        int cpuCount = 0;
        while (capTimer.getTicks() <= 1000) {
            canvas.update();
            cpuCount++;
        }
        int openCLCount = 0;
        capTimer.start();
        while (capTimer.getTicks() <= 1000) {
            openCLCanvas.update();
            openCLCount++;
        }
        int cudaCount = 0;
        capTimer.start();
        while (capTimer.getTicks() <= 1000) {
            cudaCanvas.update();
            cudaCount++;
        }

        std::cout << "CPU: " << cpuCount << std::endl;
        std::cout << "OpenCL: " << openCLCount << std::endl;
        std::cout << "CUDA: " << cudaCount << std::endl;
//        //Update cells in canvas and then draw the living ones
//        canvas.update();
//        canvas.draw();
//
//        openCLCanvas.draw();
//        openCLCanvas.update();
//        cudaCanvas.draw();
//        cudaCanvas.update();
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