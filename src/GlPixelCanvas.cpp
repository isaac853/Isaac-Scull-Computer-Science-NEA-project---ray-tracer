#include "GlPixelCanvas.hpp"

GlPixelCanvas::GlPixelCanvas(int w, int h) : PixelCanvas(w, h), texture_id(0) {
    CreateTexture();
}

GlPixelCanvas::~GlPixelCanvas() {
    if (texture_id != 0) {
        glDeleteTextures(1, &texture_id);
    }
}

// Create an openGL texture that can be used to display the pixel texture
void GlPixelCanvas::CreateTexture() {
    if (texture_id == 0) {
        glGenTextures(1, &texture_id);
    }
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
}

// Copy the pixel data into the openGL texture
void GlPixelCanvas::UpdateTexture() {
    if (texture_dirty) {
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
        texture_dirty = false;
    }
}
