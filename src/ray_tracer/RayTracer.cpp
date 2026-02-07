#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    void RayTracer::render(Vector3& dir, Vector3& colour){
        Vector3 scale(6.0, 6.0, 1.0);
        Vector3 red(1.0, 0.0, 0.0);
        Vector3 r;
        Vector3 start;
        bool anyhit = true;
        // std::cout << dir << "\n";
        //loops through renderable list
        for(Renderable* renderable:renderables){
            Vector3 intersectionPoint;
            const bool hit = renderable->intersects(start, dir, intersectionPoint);
            anyhit |= hit;
        }
        colour = scale.mul(dir.squared(), r);
    
        if(anyhit){
            colour = red;
        }
    }
}
