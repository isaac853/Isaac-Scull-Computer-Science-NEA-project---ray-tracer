#pragma once
#include "math/mathtypes.hpp"
#include "PixelCanvas.hpp"
#include "ray_tracer/RayTracer.hpp"

namespace isaac::ray_tracer {

using namespace isaac::math;

class Camera {
   private:
    floating focalLength;
    floating w;
    floating h;
   public:
    Camera(floating focalLength, floating w, floating h);

    void render(
        PixelCanvas& pixelCanvas,
        RayTracer& rayTracer
    );
};

}  // namespace isaac::ray_tracer
