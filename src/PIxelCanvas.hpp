#pragma once

#include <vector>
#include <cstdint>
#include <functional>

// Simple RGB pixel buffer class
class PixelCanvas {
protected:
    int width, height;
    bool texture_dirty;
    std::vector<uint8_t> pixels; // RGB data: width * height * 3 bytes
public:
    int get_width(){return width;}

    int get_height(){return height;}

    PixelCanvas(int w, int h) ;

    virtual ~PixelCanvas() ;

    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) ;

    void Clear(uint8_t r, uint8_t g, uint8_t b) ;

    void DrawLine(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b) ;

    void DrawCircle(int cx, int cy, int radius, uint8_t r, uint8_t g, uint8_t b) ;

    void forEach(std::function<void(int x, int y, int w, int h, uint8_t &r, uint8_t &g, uint8_t &b)>);
};
