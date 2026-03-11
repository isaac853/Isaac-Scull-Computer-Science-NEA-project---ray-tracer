#include "PixelCanvas.hpp" //needs access to the header file
#include <cmath> //allows maths in c

PixelCanvas::PixelCanvas(int w, int h) : width(w), height(h), texture_dirty(true) {
    pixels.resize(width * height * 3, 0); //constructor uses width and height * 3 to resize the pixels array
}

PixelCanvas::~PixelCanvas() { //destructor
}

//changes all colours of a pixel given its x,y coord in the canvas
void PixelCanvas::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 0 && x < width && y >= 0 && y < height) {//&& is AND, range check for x and y
        int idx = (y * width + x) * 3; //converts x,y coordinates into start of r,g,b in pixels
        pixels[idx] = r;
        pixels[idx + 1] = g;
        pixels[idx + 2] = b;
        texture_dirty = true;
    }
}

//sets all pixels to default colour
void PixelCanvas::Clear(uint8_t r, uint8_t g, uint8_t b) {
    for (size_t i = 0; i < pixels.size(); i += 3) {// for loop, until i reaches end of pixels with step 3
        pixels[i] = r;
        pixels[i + 1] = g;
        pixels[i + 2] = b;
    }
    texture_dirty = true;
}
//applies given function to all pixels
void PixelCanvas::forEach(std::function<void(int x, int y, int w, int h, uint8_t& r, uint8_t& g, uint8_t& b)> callback) {
    for (int i = 0; i < width; i++) { // loops through x,y coord of every pixel
        for (int j = 0; j < height; j++) {
            uint8_t r, g, b; //create r, g, b variables
            callback(i, j, width, height, r, g, b); //mutates r g and b in an undefined manner
            SetPixel(i, j, r, g, b); //applies new colours to pixel
        }
    }
}
