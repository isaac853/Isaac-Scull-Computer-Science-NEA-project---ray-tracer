#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    /// @brief Special case where the ray starts from 0
    /// @param dir unit vector direction of the ray
    /// @param colour the return value colour
    void RayTracer::render(Vector3& dir, Vector3& colour){
        Vector3 start; 
        render(start, dir, colour, 3); // TODO 10 is remaining depth, make into parameter
    }
    
    /// @brief recursively traces rays rays against all renderables 
    /// @param start 
    /// @param dir 
    /// @param colour 
    void RayTracer::render(Vector3& start, Vector3& dir, Vector3& colour, int remainingDepth){

        if(remainingDepth <= 0) return; //base case

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
    
        if(nearest != NULL){
            // Only our renderable knows its shape and thus how to get an (x,y) texture coordinate
            // Pass ray tracer, start, dir, mink to renderable and get back a colour
            // Needs to be virtual so PlainRenderable and MappedRenderable can work differently
            nearest->render(*this, start, dir, mink, colour, remainingDepth - 1);
        }
    }
}


//materials to have a smoothness property that perturbs the reflected rays similarly to if they were chosen from a normal distribution
//for now have a constant no. of rays scattering at any surface
//materials! draw a diagram, figure out how to do anything at all