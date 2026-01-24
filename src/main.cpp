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

// Canvas parameters
const int CANVAS_WIDTH = 512;
const int CANVAS_HEIGHT = 512;

// Simple RGB pixel buffer class
class PixelCanvas {
public:
    std::vector<uint8_t> pixels; // RGB data: width * height * 3 bytes
    GLuint texture_id;
    int width, height;
    bool texture_dirty;

    PixelCanvas(int w, int h) : width(w), height(h), texture_id(0), texture_dirty(true) {
        pixels.resize(width * height * 3, 0);
        CreateTexture();
    }

    ~PixelCanvas() {
        if (texture_id != 0) {
            glDeleteTextures(1, &texture_id);
        }
    }

    void CreateTexture() {
        if (texture_id == 0) {
            glGenTextures(1, &texture_id);
        }
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    }

    void UpdateTexture() {
        if (texture_dirty) {
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
            texture_dirty = false;
        }
    }

    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            int idx = (y * width + x) * 3;
            pixels[idx] = r;
            pixels[idx + 1] = g;
            pixels[idx + 2] = b;
            texture_dirty = true;
        }
    }

    void Clear(uint8_t r, uint8_t g, uint8_t b) {
        for (size_t i = 0; i < pixels.size(); i += 3) {
            pixels[i] = r;
            pixels[i + 1] = g;
            pixels[i + 2] = b;
        }
        texture_dirty = true;
    }

    void DrawLine(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b) {
        // Simple Bresenham-like line drawing
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        int x = x0, y = y0;
        while (true) {
            SetPixel(x, y, r, g, b);
            if (x == x1 && y == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x += sx;
            }
            if (e2 < dx) {
                err += dx;
                y += sy;
            }
        }
    }

    void DrawCircle(int cx, int cy, int radius, uint8_t r, uint8_t g, uint8_t b) {
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    SetPixel(cx + x, cy + y, r, g, b);
                }
            }
        }
    }
};

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
        PixelCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
        canvas.Clear(32, 32, 64); // Dark blue background
    
        // Draw some demo patterns
        canvas.DrawCircle(128, 128, 50, 255, 0, 0);     // Red circle
        canvas.DrawCircle(384, 128, 50, 0, 255, 0);     // Green circle
        canvas.DrawLine(256, 50, 256, 462, 255, 255, 0); // Yellow vertical line

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
                ImGui::Image((void*)(intptr_t)canvas.texture_id, ImVec2(512, 512), ImVec2(0, 1), ImVec2(1, 0));
                
                ImGui::Separator();

                // Render Button 
                if (ImGui::Button("Render", ImVec2(0, 0))) {
                    // TODO this should render a frame
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
