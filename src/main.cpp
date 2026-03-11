// Tell SDL not to take over our main method
#define SDL_MAIN_HANDLED

//imports
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <SDL.h>
#include <GL/gl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include "GlPixelCanvas.hpp"
#include "ray_tracer/RayTracer.hpp"
#include "ray_tracer/Camera.hpp"
#include "ray_tracer/objects/RenderableSphere.hpp"
#include "ray_tracer/PlainMaterial.hpp"
#include "ray_tracer/objects/RenderableCheckedPlane.hpp"
#include "ray_tracer/objects/RenderableLightPlane.hpp"

// Canvas size parameters in pixels
const int CANVAS_WIDTH = 512; 
const int CANVAS_HEIGHT = 512;

// entry point of main
int main(int argc, char** argv) {
    //stop the compiler complaining about unused arguments
    (void)argc; (void)argv;
    
    // Initialize SDL2, window abstraction library
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { //runs initialiser and checks if initialiser fails...
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";//output an error 
        return 1;
    }

    // openGL interacts with operating system and graphics card, SDL uses it to draw stuff.
    // SDL interacts with the OS to make windows, menus ect

    // Create SDL window with OpenGL support
    // just some more initial parameter setting to make SDL use openGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);// using openGL 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // create the main window
    SDL_Window* win = SDL_CreateWindow("Ray Tracer - Isaac 2026", //title
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, //start coords
                                       1280, 720, //size
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!win) { //presence check for window creation
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n"; // error output
        SDL_Quit();
        return 1;
    }

    // Create OpenGL context
    SDL_GLContext gl_context = SDL_GL_CreateContext(win); //try to init gl_context
    if (!gl_context) { // if failiure...
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << "\n";//output error message
        SDL_DestroyWindow(win); //close
        SDL_Quit();
        return 1;
    }

    SDL_GL_MakeCurrent(win, gl_context); //make the opengl context this files active one
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup ImGui context
    // ImGUI gives UI elements to work with on the window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); //opens context
    ImGuiIO& io = ImGui::GetIO(); //input output handling
    ImGui::StyleColorsDark(); //sets style to dark

    // Setup Platform/Renderer backends
    // Lets imGUI know to use SDL2 and that SDL2 is using openGL
    ImGui_ImplSDL2_InitForOpenGL(win, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    // application state
    bool show_demo_window = true; // TODO delete 
    bool show_controls_window = true; // don't delete

    //main window background colour
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); // cool blue

    // sky colour, defaults to grey
    ImVec4 skyColour = ImVec4(35.0/255.0, 35.0/255.0, 35.0/255.0, 1.00f);
    
    // Canvas setup
    GlPixelCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
    canvas.Clear(32, 32, 64); // Dark blue background

    //make a camera with focal length to size ratio similar to human eye
    // is always at (0,0,0) and looking down the z axis
    isaac::ray_tracer::Camera camera(0.96, 1.0, 1.0);
    int32_t samplesPerPixel = 16;

    //create a raytracer
    isaac::ray_tracer::RayTracer rayTracer;

    // Put some things in the world to look at
    
    //transform list    
    isaac::math::Transform t1;
    isaac::math::Transform t2;
    isaac::math::Transform t3;
    isaac::math::Transform t4;
    isaac::math::Transform t5;

    t1.tz = 10.0;
    t1.ty = 0.5;
    t2.tz = 6.0;
    t2.tx = -2.1;
    t2.ty = -1.0;
    t3.tz = 11.0;
    t3.tx = 4.0;
    t3.ty = 0.0;
    t4.ty = -10.0;
    //light
    t5.tz = 20.0;
    t5.ty = 3.0;
    t5.tx = -6.0;

    //colour list
    isaac::math::Vector3 c1(0.5, 0.1, 0.5);
    isaac::math::Vector3 c2(0.5, 0.5, 0.1);
    isaac::math::Vector3 c3(0.1, 0.5, 0.5);
    isaac::math::Vector3 c4(0.0, 0.0, 0.0);    
    isaac::math::Vector3 c5(1.0, 1.0, 1.0);
    isaac::math::Vector3 c6(0.1, 1.0, .10); //c6(0.8, 1.0, 1.0);

    //material list
    isaac::ray_tracer::PlainMaterial mat1(1.0, 1.0, c1);
    isaac::ray_tracer::PlainMaterial mat2(1.0, 1.0, c2);
    isaac::ray_tracer::PlainMaterial mat3(1.0, 1.0, c3);
    isaac::ray_tracer::PlainMaterial mat4(1.0, 1.0, c4);
    isaac::ray_tracer::PlainMaterial mat5(1.0, 1.0, c5);    

    //sphere list
    isaac::math::Sphere s1(1.0);
    isaac::math::Sphere s2(2.0);
    isaac::math::Sphere s3(3.0);

    //  object list
    isaac::ray_tracer::RenderableSphere rs1(t1,mat1, s1);
    isaac::ray_tracer::RenderableSphere rs2(t2,mat2, s2);
    isaac::ray_tracer::RenderableSphere rs3(t3,mat3, s3);
    isaac::ray_tracer::RenderableCheckedPlane rcp(t4, mat4, mat5);
    isaac::ray_tracer::RenderableLightPlane rlp(t5, 2.0, 0.5, c6);

    //adding the objects defined above to the ray tracers renderable list
    rayTracer.add(&rs1);
    rayTracer.add(&rs2);
    rayTracer.add(&rs3);
    rayTracer.add(&rcp);
    rayTracer.add(&rlp);

    // Main loop
    // library updates window every frame
    bool running = true; //exit condition for run loop
    SDL_Event event; //SDL function, handles events such as mouse movement, clicks ect.

    while (running) {
        //looking for a windowing event, e.g mouse moves
        while (SDL_PollEvent(&event)) { // handles any event that occurs this is boilerplate
            ImGui_ImplSDL2_ProcessEvent(&event); //processes the event

            //handles closing window
            if (event.type == SDL_QUIT) {
                running = false; //closes if you quit
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {//also closes if you quit
                running = false;
            }
        }

        // Start ImGui frame (as in frames of a video)
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Show demo window
        // TODO - To get rid of the demo window delete the three lines below here:
        // if (show_demo_window) {
        //     ImGui::ShowDemoWindow(&show_demo_window);
        // }

        // dialog with tracer controls
        {
            ImGui::SetNextWindowPos(ImVec2(660, 20), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(600, 680), ImGuiCond_Always);
            ImGui::Begin("Tracer Controls", &show_controls_window, ImGuiWindowFlags_None); //title of tab and initialisation
            
            ImGui::Text("These are the parameters of the ray tracer."); // text will appear at the top of the tab
            ImGui::Separator(); //linebreak
            
            //Render Button 
            if (ImGui::Button("Render", ImVec2(0, 0))) {
                // Render a frame
                //for now just output a message
                std::cout << "Render button pressed\n";

                canvas.forEach(
                [&](int x, int y, int w, int h, uint8_t &r, uint8_t &g, uint8_t &b) {
                    r = x & 255;
                    b = y & 255;
                    g = (x + y) & 255; 
                    
                    }
                );
            }
            
            if (ImGui::Button("Clear Canvas", ImVec2(0, 0))) {
                // Render a frame
                //for now just output a message
                std::cout << "Clear button pressed\n";
                canvas.Clear(32, 32, 64);// sets the canvas to dark blue
            }             

            ImGui::End(); // stop talking about it
            }
            // // samples per pixel slider
            // ImGui::SliderInt("samples/pixel", &samplesPerPixel, 1, 32);
            
            // // bounce slider
            // ImGui::SliderInt("no. of bounces", &rayTracer.maxDepth, 1, 32);

            // //sky Color picker
            // ImGui::ColorEdit4("sky colour", (float*)&skyColour);

            // // Color picker
            // ImGui::ColorEdit4("Clear Color", (float*)&clear_color);

            // ImGui::Separator();
//            ImGui::Text("FPS: %.1f", io.Framerate);

        // Canvas drawing window
        {
            ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always); 
            ImGui::SetNextWindowSize(ImVec2(600, 680), ImGuiCond_Always);
            ImGui::Begin("Pixel Canvas", nullptr, ImGuiWindowFlags_None);//title of tab and initialisation
            
            ImGui::Text("Dynamic RGB Pixel Canvas"); //block of text at the top
            ImGui::Separator();
            
            // Update and display the canvas texture
            canvas.UpdateTexture();
            ImGui::Image((void*)(intptr_t)canvas.get_texture_id(), ImVec2(CANVAS_WIDTH, CANVAS_HEIGHT), ImVec2(0, 1), ImVec2(1, 0));
            
            ImGui::End();
        }
            // ImGui::Separator();
            
            // // Render Button 
            // if (ImGui::Button("Render", ImVec2(0, 0))) {
            //     // Render a frame
            //     camera.render(
            //         canvas,
            //         samplesPerPixel,
            //         //function given to cameras render method to handle each pixel
            //         //captures ray tracer from current scope by ref
            //         [&](isaac::math::Vector3& dir, isaac::math::Vector3& colour, int x, int y){
            //             rayTracer.render(dir, colour);
            //         }
            //     );                    
            // }
            // ImGui::SameLine();
            
            // //clear button
            // if (ImGui::Button("Clear Canvas##btn")) {
            //     canvas.Clear(32, 32, 64);
            // }

        
//      Rendering
        ImGui::Render();

        // Just the stuff you need to do to render a frame.
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y); //applies the window size
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w); // applies background colour
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Copy gui state to the ray tracer
        rayTracer.skyColour.v[0] = (double)skyColour.x;
        rayTracer.skyColour.v[1] = (double)skyColour.y;
        rayTracer.skyColour.v[2] = (double)skyColour.z;

        // More stuff you have to do to render a frame.
        SDL_GL_SwapWindow(win);
        SDL_Delay(10);
    }

    // Cleanup shutsdown and removes links between files
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(win);
    SDL_Quit(); 

    std::cout << "Exited cleanly\n";
    return 0;
}
