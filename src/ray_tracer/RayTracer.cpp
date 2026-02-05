#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    void RayTracer::render(Vector3& dir, Vector3& colour){
        Vector3 scale(6.0, 6.0, 1.0);
        Vector3 r;
        // std::cout << dir << "\n";
        colour = scale.mul(dir.squared(), r);
    }
}
