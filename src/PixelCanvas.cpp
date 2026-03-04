#include "PixelCanvas.hpp"
#include <cmath>

PixelCanvas::PixelCanvas(int w, int h) : width(w), height(h), texture_dirty(true) {
    pixels.resize(width * height * 3, 0);
}

PixelCanvas::~PixelCanvas() {
}

void PixelCanvas::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        int idx = (y * width + x) * 3;
        pixels[idx] = r;
        pixels[idx + 1] = g;
        pixels[idx + 2] = b;
        texture_dirty = true;
    }
}

void PixelCanvas::Clear(uint8_t r, uint8_t g, uint8_t b) {
    for (size_t i = 0; i < pixels.size(); i += 3) {
        pixels[i] = r;
        pixels[i + 1] = g;
        pixels[i + 2] = b;
    }
    texture_dirty = true;
}

void PixelCanvas::forEach(std::function<void(int x, int y, int w, int h, uint8_t& r, uint8_t& g, uint8_t& b)> callback) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            uint8_t r, g, b;
            callback(i, j, width, height, r, g, b);
            SetPixel(i, j, r, g, b);
        }
    }
}
