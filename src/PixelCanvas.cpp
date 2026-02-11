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

void PixelCanvas::DrawLine(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g, uint8_t b) {
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

void PixelCanvas::DrawCircle(int cx, int cy, int radius, uint8_t r, uint8_t g, uint8_t b) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SetPixel(cx + x, cy + y, r, g, b);
            }
        }
    }
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
