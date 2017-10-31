#include <iostream>
#include <fstream>
#include "Window.h"
#include "CPUCanvas.h"
#include "OpenCLCanvas.h"
#include "CUDACanvas.h"



void getResults(int h, int w) {
    std::ofstream myfile;
    std::string fileName = "results_restrain_ifs_h";
    fileName = fileName + std::to_string(h) + "_w" + std::to_string(w) + ".txt";
    myfile.open (fileName);

    CPUCanvas canvas = CPUCanvas(h,w,720, 1280);
    std::cout << "aaaaa" << std::endl;
    OpenCLCanvas openCLCanvas = OpenCLCanvas(h,w,720,1280);
    CUDACanvas cudaCanvas = CUDACanvas(h,w,720,1280);

    int numIterations = 20;
    Timer capTimer;
    myfile << "CPU" << " " << " OpenCL" << " " << "CUDA" << std::endl;
    for (int i = 0; i < numIterations; ++i) {
        capTimer.start();
        int cpuCount =  0;
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
        myfile << cpuCount << " " << openCLCount << " " << cudaCount << std::endl;

    }

    myfile.close();

}


int main() {
    /* SDL2 Singleton Window */
    int a[10] = {16,20,32,64,100,128,256,512,1024,1280};
    int b[10] = {16,20,64,64,100,128,256,512,1024,720};
    for (int i = 0; i < 10; ++i) {
        getResults(a[i],b[i]);
    }
    Window *window = Window :: getInstance();

    /* Variable needed to get all events*/
    SDL_Event event;
    int h = 32;
    int w = 64;
    /*Canvas that has the Conways Game of Life logic */
    CPUCanvas canvas = CPUCanvas(h,w,720, 1280);
    OpenCLCanvas openCLCanvas = OpenCLCanvas(h,w,720,1280);
    CUDACanvas cudaCanvas = CUDACanvas(h,w,720,1280);
    Timer capTimer;

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
//        capTimer.start();
//        int cpuCount = 0;
//        while (capTimer.getTicks() <= 1000) {
//            canvas.update();
//            cpuCount++;
//        }
//        int openCLCount = 0;
//        capTimer.start();
//        while (capTimer.getTicks() <= 1000) {
//            openCLCanvas.update();
//            openCLCount++;
//        }
//        int cudaCount = 0;
//        capTimer.start();
//        while (capTimer.getTicks() <= 1000) {
//            cudaCanvas.update();
//            cudaCount++;
//        }
//
//        std::cout << "CPU: " << cpuCount << std::endl;
//        std::cout << "OpenCL: " << openCLCount << std::endl;
//        std::cout << "CUDA: " << cudaCount << std::endl;
//        //Update cells in canvas and then draw the living ones
//        canvas.update();
//        canvas.draw();
//
//        openCLCanvas.draw();
//        openCLCanvas.update();
        cudaCanvas.draw();
        cudaCanvas.update();
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