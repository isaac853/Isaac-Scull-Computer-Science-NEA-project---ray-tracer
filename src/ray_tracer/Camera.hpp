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
        const uint8_t samplesPerPixel,
        std::function<void(Vector3& dir, Vector3& colour)> callback
    );
};

}  // namespace isaac::ray_tracer
