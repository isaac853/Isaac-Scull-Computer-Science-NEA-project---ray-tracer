// Tell SDL not to take over our main method
#define SDL_MAIN_HANDLED

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

// Canvas parameters
const int CANVAS_WIDTH = 512;
const int CANVAS_HEIGHT = 512;


int main(int argc, char** argv) {
    (void)argc; (void)argv;
    std::cout << "Hello world and Isaac"  << "\n";
    
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    // Create SDL window with OpenGL support
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* win = SDL_CreateWindow("ImGui SDL2 Example",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1280, 720,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!win) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // Create OpenGL context
    SDL_GLContext gl_context = SDL_GL_CreateContext(win);
    if (!gl_context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_GL_MakeCurrent(win, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(win, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Demo state
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    // Dialog state
    static float slider_value = 0.5f;
    static int counter = 0;
    static char text_input[256] = "Type something...";

    // Canvas setup
    GlPixelCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
    canvas.Clear(32, 32, 64); // Dark blue background

    //make a camera with focal length to size ratio similar to human eye
    isaac::ray_tracer::Camera camera(0.96, 1.0, 1.0);
    const int32_t samplesPerPixel = 4; // TODO make this a variable and put it on a slider
    
    // Draw some demo patterns
    canvas.DrawCircle(128, 128, 50, 255, 0, 0);     // Red circle
    canvas.DrawCircle(384, 128, 50, 0, 255, 0);     // Green circle
    canvas.DrawLine(256, 50, 256, 462, 255, 255, 0); // Yellow vertical line

    isaac::ray_tracer::RayTracer rayTracer;

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Show demo window
        // TODO - To get rid of the demo window delete the three lines below here:
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // Example dialog with controls
        {
            ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
            ImGui::Begin("Example Dialog", &show_another_window, ImGuiWindowFlags_None);

            ImGui::Text("This is an example ImGui dialog with various controls.");
            ImGui::Separator();

            // Slider control
            ImGui::SliderFloat("Slider", &slider_value, 0.0f, 1.0f);

            // Button control
            if (ImGui::Button("Click Me!", ImVec2(100, 0))) {
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("Counter: %d", counter);

            // Text input
            ImGui::InputText("Text Input", text_input, IM_ARRAYSIZE(text_input));
            ImGui::Text("You entered: %s", text_input);

            // Color picker
            ImGui::ColorEdit4("Clear Color", (float*)&clear_color);

            // Checkbox
            static bool checkbox_value = false;
            ImGui::Checkbox("Example Checkbox", &checkbox_value);

            // Radio buttons
            static int radio_value = 0;
            ImGui::RadioButton("Option 1", &radio_value, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Option 2", &radio_value, 1);
            ImGui::SameLine();
            ImGui::RadioButton("Option 3", &radio_value, 2);

            ImGui::Separator();
            ImGui::Text("FPS: %.1f", io.Framerate);

            ImGui::End();
        }
            // Canvas drawing window
            {
                ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowSize(ImVec2(650, 650), ImGuiCond_FirstUseEver);
                ImGui::Begin("Pixel Canvas", nullptr, ImGuiWindowFlags_None);

                ImGui::Text("Dynamic RGB Pixel Canvas (512x512)");
                ImGui::Separator();

                // Update and display the canvas texture
                canvas.UpdateTexture();
                ImGui::Image((void*)(intptr_t)canvas.get_texture_id(), ImVec2(512, 512), ImVec2(0, 1), ImVec2(1, 0));
                
                ImGui::Separator();

                // Render Button 
                if (ImGui::Button("Render", ImVec2(0, 0))) {
                    // Render a frame
                    camera.render(
                        canvas,
                        samplesPerPixel,
                        [&](isaac::math::Vector3& dir, isaac::math::Vector3& colour, int x, int y){
                            rayTracer.render(dir, colour);
                        }
                    );                    
                }

                ImGui::Separator();
                ImGui::Text("Drawing Tools:");

                static float draw_color[3] = {1.0f, 0.0f, 0.0f}; // RGB [0-1]
                ImGui::ColorEdit3("Draw Color", draw_color);

                static int shape = 0;
                ImGui::RadioButton("Circle##shape", &shape, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Line##shape", &shape, 1);

                if (shape == 0) {
                    // Circle drawing
                    static int circle_x = 256, circle_y = 256, circle_radius = 30;
                    ImGui::DragInt("Circle X##pos", &circle_x, 1, 0, 511);
                    ImGui::DragInt("Circle Y##pos", &circle_y, 1, 0, 511);
                    ImGui::DragInt("Radius##circ", &circle_radius, 1, 1, 256);
                    if (ImGui::Button("Draw Circle")) {
                        uint8_t r = (uint8_t)(draw_color[0] * 255);
                        uint8_t g = (uint8_t)(draw_color[1] * 255);
                        uint8_t b = (uint8_t)(draw_color[2] * 255);
                        canvas.DrawCircle(circle_x, circle_y, circle_radius, r, g, b);
                    }
                } else {
                    // Line drawing
                    static int line_x0 = 100, line_y0 = 100, line_x1 = 400, line_y1 = 400;
                    ImGui::DragInt("Start X##line", &line_x0, 1, 0, 511);
                    ImGui::DragInt("Start Y##line", &line_y0, 1, 0, 511);
                    ImGui::DragInt("End X##line", &line_x1, 1, 0, 511);
                    ImGui::DragInt("End Y##line", &line_y1, 1, 0, 511);
                    if (ImGui::Button("Draw Line")) {
                        uint8_t r = (uint8_t)(draw_color[0] * 255);
                        uint8_t g = (uint8_t)(draw_color[1] * 255);
                        uint8_t b = (uint8_t)(draw_color[2] * 255);
                        canvas.DrawLine(line_x0, line_y0, line_x1, line_y1, r, g, b);
                    }
                }

                if (ImGui::Button("Clear Canvas##btn")) {
                    canvas.Clear(32, 32, 64);
                }

                ImGui::End();
            }
        // Rendering
        ImGui::Render();

        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(win);
        SDL_Delay(10);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(win);
    SDL_Quit();

    std::cout << "Exited cleanly\n";
    return 0;
}
