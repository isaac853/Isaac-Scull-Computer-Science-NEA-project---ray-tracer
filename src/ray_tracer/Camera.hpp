#pragma once
#include "math/mathtypes.hpp"
#include "PixelCanvas.hpp"
#include "ray_tracer/RayTracer.hpp"

namespace isaac::ray_tracer {

using namespace isaac::math;

class Camera {
   private:
    floating focalLength;

   public:
    Camera(floating focalLength);

    void render(
        PixelCanvas& pixelCanvas,
        RayTracer& rayTracer
    );
};

}  // namespace isaac::ray_tracer
