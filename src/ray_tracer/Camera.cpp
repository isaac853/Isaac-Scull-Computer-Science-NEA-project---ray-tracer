#include "ray_tracer/Camera.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>
#include "math/Vector3.hpp"
#include <cstdint>

namespace isaac::ray_tracer {

using namespace isaac::math;

Camera::Camera(floating focalLength, floating w, floating h) : 
  focalLength(focalLength),
  w(w),
  h(h)
{
}

inline void scaleColourComponent(floating cc, floating cs,  uint8_t &c){
    //scale up
    const floating sc = cc * cs;
    const int32_t ic = (int32_t)sc;
    if(ic < 0){
        c = 0;
        return;
    }

    if(ic > 255){
        c = 255;
        return;
    }

    c = ic;
}

//uses xorshifting to make an almost random number really quick
inline floating perturb()
{
    static uint32_t state = 123456789u;                 // This value persists between calls to this function

    // xorshift32
    state ^= state << 13;                               // This is excellent
    state ^= state >> 17;
    state ^= state << 5;

    // Convert to float in (0,1)
    constexpr floating inv = 1.0 / 4294967296.0; // 2^32  // This happens at compile time
    return state * inv - 0.5;                             // This happens at run time
}

void Camera::render(
    PixelCanvas& pixelCanvas,
    const uint8_t samplesPerPixel,
    std::function<void(Vector3& dir, Vector3& colour, int x, int y)> callback // Speed ?
){

    const floating offset_x = 0.5 - (floating)pixelCanvas.get_width()*0.5;
    const floating offset_y = 0.5 - (floating)pixelCanvas.get_height()*0.5;

    const floating scale_x = w / (floating)pixelCanvas.get_width();
    const floating scale_y = h / (floating)pixelCanvas.get_height();
    const floating scale_c = 255.0 / (floating)samplesPerPixel;
    pixelCanvas.forEach(
        [&](const int x, const int y, const int w, const int h, uint8_t &r, uint8_t &g, uint8_t &b) {

            const floating cx = -(offset_x + (floating)x);
            const floating cy = (offset_y + (floating)y);
            const floating cz = -focalLength; 

            //std::cout << "x=" << x << " cx=" << cx << "\n";

            // TODO Over-sampling
            // TODO We probaly want to randomly perturb cx and cy, by a random number between +/-0.5
            // TODO Then we want to trace a path/ray and get some colour... a few times
            // TODO Then we want to scale down the colours and return them to the canvas
            // TODO This needs to be testable

            
            Vector3 colour;
            
            
            for(uint8_t i = 0; i < samplesPerPixel; i++){
                const floating perturb_y = 0.0;//perturb(); // TODO put these back
                const floating perturb_x = 0.0;//perturb();
                
                Vector3 path(
                    (perturb_x -cx) * scale_x,
                    (perturb_y -cy) * scale_y,
                    -cz);
                    
                // Make it a unit vector
                path.normalise();
                
                Vector3 tempColour;
                
                //gets the values for colour given a unit vector starting from origin
                callback(path, tempColour, x, y);


                //cumulate colours from each sub-pixel sample
                colour.add(tempColour);

            }

            scaleColourComponent(colour.v[0], scale_c, r);
            scaleColourComponent(colour.v[1], scale_c, g);
            scaleColourComponent(colour.v[2], scale_c, b);


        }
    );
}


}  // namespace isaac::ray_tracer