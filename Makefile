
all:
	
	nvcc kernel.cu main.cpp Timer.cpp Window.cpp  Grid.cpp  Canvas.cpp  Utils.cpp OpenCLCanvas.cpp CUDACanvas.cpp  CPUCanvas.cpp -w -lSDL2 -lSDL2_image -lOpenCL -lcuda -o main 
clean:
	rm main
