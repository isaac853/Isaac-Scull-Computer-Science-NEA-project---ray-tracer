#pragma once
#include "math/mathtypes.hpp"

namespace isaac::ray_tracer {

using namespace isaac::math;

class Camera {
   private:
    floating focalLength;

   public:
    Camera(floating focalLength);
};

}  // namespace isaac::ray_tracer
