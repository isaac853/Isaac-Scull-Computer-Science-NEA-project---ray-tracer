#include "ray_tracer/Camera.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

using namespace isaac::math;

Camera::Camera(floating focalLength, floating w, floating h) : 
  focalLength(focalLength),
  w(w),
  h(h)
{
}

void Camera::render(
    PixelCanvas& pixelCanvas,
    RayTracer& rayTracer
){

    floating offset_x = 0.5 - (floating)pixelCanvas.get_width()*0.5;
    // account for camera inversion in the vertical axis maybe
    floating offset_y = 0.5 - (floating)pixelCanvas.get_height()*0.5;

    floating scale_x = w / (floating)pixelCanvas.get_width();
    floating scale_y = h / (floating)pixelCanvas.get_height();

    pixelCanvas.forEach(
        [&](int x, int y, int w, int h, uint8_t &r, uint8_t &g, uint8_t &b) {

            floating cx = (offset_x + (floating)x) * scale_x;
            floating cy = (offset_y + (floating)y) * scale_y;
            floating cz = -focalLength; 

            std::cout << "x=" << x << " cx=" << cx << "\n";


            r = x & 255;
            b = y & 255;
            g = (x + y) & 255; 
    
        }
    );
}


}  // namespace isaac::ray_tracer