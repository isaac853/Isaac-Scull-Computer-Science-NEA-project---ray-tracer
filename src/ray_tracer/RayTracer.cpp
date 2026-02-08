#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    void RayTracer::render(Vector3& dir, Vector3& colour){
        Vector3 scale(6.0, 6.0, 1.0);
        Vector3 red(1.0, 0.0, 0.0);
        Vector3 r;
        Vector3 start;
        // std::cout << dir << "\n";
        //loops through renderable list
        Renderable* nearest = NULL;
        floating mink = -1.0;
        for(Renderable* renderable:renderables){
            const floating k = renderable->intersects(start, dir);
            if (k >= 0.0 && (nearest == NULL || k < mink)){
                mink = k;
                nearest = renderable;
            }
        }
        colour = scale.mul(dir.squared(), r);
    
        if(nearest != NULL){
            colour = red;
        }
    }
}
