#pragma once

#include "PixelCanvas.hpp"
#include <GL/gl.h>

// extended pixel canvas to handle openGL boilerplate so that i can use imGUI to draw pixel canvas onto screen
// adapted from imGUI demo code
class GlPixelCanvas : public PixelCanvas {
    
private:
    //openGL handle to a texture (the whole canvas on the graphics card)
    GLuint texture_id;

    // Create an openGL texture that can be used to display the pixel texture
    void CreateTexture();
  
public:

    // Constructor
    GlPixelCanvas(int w, int h);

    //destructor
    virtual ~GlPixelCanvas();

    // Copy the pixel data into the openGL texture
    void UpdateTexture();

    GLuint get_texture_id() { return texture_id; }
};
