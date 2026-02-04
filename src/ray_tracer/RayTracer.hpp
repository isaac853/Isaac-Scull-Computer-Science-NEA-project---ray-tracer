#pragma once

#include "math/Vector3.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;
    class RayTracer{
    public:
    //takes a direction vector and returns a colour (stored in a vector class for convenience)
    //by ref used for both to avoid space reallocation
        void render(Vector3& dir, Vector3& colour);
    };
}
