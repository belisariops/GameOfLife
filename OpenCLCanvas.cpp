//
// Created by belisariops on 10/28/17.
//

#include "OpenCLCanvas.h"

OpenCLCanvas::OpenCLCanvas(int height, int width, int screenWidth, int screenHeight) : Canvas(height, width,
                                                                                              screenWidth,
                                                                                              screenHeight) {
    N_ELEMENTS= height * width;
    int platform_id=0, device_id=0;

    try {
        // Query for platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        // Get a list of devices on this platform
        std::vector<cl::Device> devices;
        // Select the platform.
        platforms[platform_id].getDevices(CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_CPU, &devices);

        // Create a context
        cl::Context context(devices);

        // Create a command queue
        // Select the device.
        queue = cl::CommandQueue(context, devices[device_id]);

        // Create the memory buffers
        bufferCurrentGrid = cl::Buffer(context, CL_MEM_READ_ONLY, N_ELEMENTS * sizeof(int));
        bufferNextGrid = cl::Buffer(context, CL_MEM_READ_ONLY, N_ELEMENTS * sizeof(int));


        // Read the program source
        std::ifstream sourceFile("kernel.cl");
        std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));
        cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length()));

        // Make program from the source code
        cl::Program program = cl::Program(context, source);

        // Build the program for the devices
        program.build(devices);

        // Make kernel
        kernel = cl::Kernel(program, "update");
    }
        catch (cl::Error err) {
            std::cout << "Error: " << err.what() << "(" << err.err() << ")" << std::endl;
        }
}

void OpenCLCanvas::update() {
    try {
        // Copy the input data to the input buffers using the command queue.
        queue.enqueueWriteBuffer(bufferCurrentGrid, CL_FALSE, 0, N_ELEMENTS * sizeof(int), currentGrid->values);

        // Set the kernel arguments
        kernel.setArg( 0, bufferCurrentGrid );
        kernel.setArg( 1, bufferNextGrid );

        // Execute the kernel
        cl::NDRange global( N_ELEMENTS );
        cl::NDRange local( 256 );
        queue.enqueueNDRangeKernel( kernel, cl::NullRange, global, local );

        // Copy the output data back to the host
        queue.enqueueReadBuffer( bufferNextGrid, CL_TRUE, 0, N_ELEMENTS * sizeof(int), nextGrid->values );


    }
    catch (cl::Error err) {
        std::cout << "Error: " << err.what() << "(" << err.err() << ")" << std::endl;
    }
}

OpenCLCanvas::~OpenCLCanvas() {
}
