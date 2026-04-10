#include "ray_tracer/Camera.hpp"
#include <iostream>
#include "math/Vector3.hpp"
#include <cstdint>

namespace isaac::ray_tracer {

using namespace isaac::math;

Camera::Camera(floating focalLength, floating w, floating h) : 
  focalLength(focalLength),
  w(w), //width of camera object
  h(h) //height of camera object
{
}
/// @brief takes floating point value of colour and scales to 0 to 255 scale
/// @param cc colour component to be scaled
/// @param cs scale needed to get to 0 to 255 scale
/// @param c return value
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

//camera render translates the pixel canvas into pixels with all the vectors we need, and gives to the raytracer render (callback)
void Camera::render(
    //parameter list
    PixelCanvas& pixelCanvas,
    const uint8_t samplesPerPixel,
    std::function<void(Vector3& dir, Vector3& colour, int x, int y)> callback //function to be passed as a parameter
){// body of function

    //offset needed to get from center of camera to middle of top left pixel in terms of pixels
    const floating offset_x = 0.5 - (floating)pixelCanvas.get_width()*0.5;
    const floating offset_y = 0.5 - (floating)pixelCanvas.get_height()*0.5;

    // converts pixels from the pixelcanvas into sizes in world coordinates
    const floating scale_y = h / (floating)pixelCanvas.get_height(); // multiplies by any value inside camera to make it 1x1
    const floating scale_x = scale_y; // w / (floating)pixelCanvas.get_width(); // maintains aspect ratio, instead of stretching it
    const floating scale_c = 255.0 / (floating)samplesPerPixel; // multiplied by sum of oversamples to get mean colours in rgb

    pixelCanvas.forEach(
        [&](const int x, const int y, const int w, const int h, uint8_t &r, uint8_t &g, uint8_t &b) {
            //defining inline the function that foreach will apply to each pixel

            //offset values from center of camera for current pixel in terms of pixels
            //flipped due to image flipping 
            const floating cx = -(offset_x + (floating)x);
            const floating cy = -(offset_y + (floating)y);
            
            //moves the camera back so focal point is at (0,0,0) in world coords
            const floating cz = -focalLength; 

            //using 3d vector to represent colour (scales from 0.0 to 1.0 instead of 0 to 255)
            Vector3 colour;
            
            // oversampling x times per pixel
            for(uint8_t i = 0; i < samplesPerPixel; i++){

                //randomly perturb vector start point from center of pixel
                const floating perturb_y = perturb();
                const floating perturb_x = perturb();
                
                //direction vector pointing to focal point from pixel location
                Vector3 path(
                    (perturb_x -cx) * scale_x, 
                    (perturb_y -cy) * scale_y,
                    -cz); // focal length
                    
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