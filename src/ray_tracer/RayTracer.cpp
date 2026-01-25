#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    void RayTracer::render(PixelCanvas& pixelCanvas) {
        std::cout << "Render button pressed"  << "\n";
        pixelCanvas.forEach(
            [&](int x, int y, int w, int h, uint8_t &r, uint8_t &g, uint8_t &b) {
                r = x & 255;
                b = y & 255;
                g = (x + y) & 255; 
                 
            }
        );
    }
}
