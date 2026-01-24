#pragma once

// #include <iostream>
#include <vector>
// #include <cstring>
#include <cstdint>
// #include <SDL.h>
#include <GL/gl.h>
// #include <imgui.h>
// #include <imgui_impl_sdl2.h>
// #include <imgui_impl_opengl3.h>


// Simple RGB pixel buffer class
class PixelCanvas {
private:
    int width, height;
    GLuint texture_id;
    bool texture_dirty;
    std::vector<uint8_t> pixels; // RGB data: width * height * 3 bytes
public:

    PixelCanvas(int w, int h) ;

    ~PixelCanvas() ;

    void CreateTexture() ;

    void UpdateTexture() ;

    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) ;

    void Clear(uint8_t r, uint8_t g, uint8_t b) ;

    void DrawLine(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b) ;

    void DrawCircle(int cx, int cy, int radius, uint8_t r, uint8_t g, uint8_t b) ;

    GLuint get_texture_id() { return texture_id; }
};
