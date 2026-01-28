#pragma once

#include "PixelCanvas.hpp"
#include <GL/gl.h>

class GlPixelCanvas : public PixelCanvas {
private:
    GLuint texture_id;
public:

    GlPixelCanvas(int w, int h);

    virtual ~GlPixelCanvas();

    void CreateTexture();

    void UpdateTexture();

    GLuint get_texture_id() { return texture_id; }
};
