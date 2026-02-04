#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    void RayTracer::render(Vector3& dir, Vector3& colour){
        // std::cout << dir << "\n";
        colour = dir;
    }
}
