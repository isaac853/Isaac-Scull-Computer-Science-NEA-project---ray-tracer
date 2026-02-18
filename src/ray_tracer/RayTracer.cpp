#include "ray_tracer/RayTracer.hpp"
// TODO remove this when I remove the debug messages
#include <iostream>

namespace isaac::ray_tracer {

    /// @brief Special case where the ray starts from 0
    /// @param dir unit vector direction of the ray
    /// @param colour the return value colour
    void RayTracer::render(Vector3& dir, Vector3& colour){
        Vector3 start; 
        render(start, dir, colour);
    }
    
    /// @brief recursively traces rays rays against all renderables 
    /// @param start 
    /// @param dir 
    /// @param colour 
    void RayTracer::render(Vector3& start, Vector3& dir, Vector3& colour){
        Vector3 scale(6.0, 6.0, 1.0);
        Vector3 red(1.0, 0.0, 0.0);
        Vector3 r;
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
       // colour = scale.mul(dir.squared(), r);
    
        if(nearest != NULL){
            // Vector3 intPoint;
            // dir.mul(mink, intPoint);
            // intPoint.add(start); // This is where our ray has intersected with our renderable object

            // Now we need enough information to extract data from our material...

            // Only our renderable knows its shape and thus how to get an (x,y) texture coordinate

            // We need to decide if a second call to renderable is going to be used !?!

            nearest->render(*this, start, dir, mink, colour);
        
            // Pass ray tracer, start, dir, mink to renderable and get back a colour
            // Needs to be virtual so PlainRenderable and MappedRenderable can work differently
            

        }
    }
}


//materials to have a smoothness property that perturbs the reflected rays similarly to if they were chosen from a normal distribution
//for now have a constant no. of rays scattering at any surface
//materials! draw a diagram, figure out how to do anything at all