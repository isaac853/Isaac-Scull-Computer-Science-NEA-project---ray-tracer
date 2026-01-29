#include "ray_tracer/Camera.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>
#include "math/Vector3.hpp"

namespace isaac::ray_tracer {

using namespace isaac::math;

Camera::Camera(floating focalLength, floating w, floating h) : 
  focalLength(focalLength),
  w(w),
  h(h)
{
}



//     void forEach(std::function<void(int x, int y, int w, int h, uint8_t &r, uint8_t &g, uint8_t &b)>);


void Camera::render(
    PixelCanvas& pixelCanvas,
    RayTracer& rayTracer
){

    const floating offset_x = 0.5 - (floating)pixelCanvas.get_width()*0.5;
    const floating offset_y = 0.5 - (floating)pixelCanvas.get_height()*0.5;

    const floating scale_x = w / (floating)pixelCanvas.get_width();
    const floating scale_y = h / (floating)pixelCanvas.get_height();

    pixelCanvas.forEach(
        [&](const int x, const int y, const int w, const int h, uint8_t &r, uint8_t &g, uint8_t &b) {

            const floating cx = (offset_x + (floating)x) * scale_x;
            const floating cy = (offset_y + (floating)y) * scale_y;
            const floating cz = -focalLength; 

            std::cout << "x=" << x << " cx=" << cx << "\n";

            // TODO Over-sampling
            // TODO We probaly want to randomly perturb cx and cy, by a random number between +/-0.5
            // TODO Then we want to trace a path/ray and get some colour... a few times
            // TODO Then we want to scale down the colours and return them to the canvas
            // TODO This needs to be testable

            Vector3 path(-cx, -cy, -cz);

            // Make it a unit vector
            path.normalise();
            


            r = x & 255;
            b = y & 255;
            g = (x + y) & 255; 
    
        }
    );
}


}  // namespace isaac::ray_tracer