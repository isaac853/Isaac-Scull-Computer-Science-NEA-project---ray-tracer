#pragma once

#include <vector> //used for std::vector type 
#include <cstdint> // standard integer types
#include <functional> // provides a hash function

// Simple RGB pixel buffer class
//  creates an area to draw pixels on
class PixelCanvas {
protected:
    int width, height;
    bool texture_dirty; //has it been modified, true or false
    std::vector<uint8_t> pixels; // RGB data: width * height * 3 bytes
public:
    // gets the width of the pixel canvas
    int get_width(){return width;}

    // gets the height of the canvas
    int get_height(){return height;}

    // constructs the canvas with width and height
    PixelCanvas(int w, int h) ;

    // virtual destructor so inherited class can also destruct
    virtual ~PixelCanvas() ;

    //sets a pixel to a colour
    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) ;

    //clears whole canvas to given colour
    void Clear(uint8_t r, uint8_t g, uint8_t b) ;

    //applies a supplied function to every pixel
    void forEach(std::function<void(int x, int y, int w, int h, uint8_t &r, uint8_t &g, uint8_t &b)>);
};
