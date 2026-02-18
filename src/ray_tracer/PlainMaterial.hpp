#pragma once
#include "math/Vector3.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;
    
class PlainMaterial {
    private:
        floating smoothness;
        floating reflectivity;
        Vector3 colour;
    //transparency
    public:
        PlainMaterial(
        floating smoothness,
        floating reflectivity,
        Vector3& colour);
        // virtual void at(
        //     Vector3& dir,
        //     floating& smoothness, // Some measure of how we scatter our rays
        //     floating& reflectivity, // how much we take into account reflected rays
        //     Vector3& colour // This is reflective colour i.e. the colour in white light
        // ) {}; 

        /// @brief makes ambient lighting more interesting by changing it according to the angle you hit the surface
        /// @param normal 
        /// @param dir 
        /// @return 
        inline floating ambientFactor(Vector3 &normal, Vector3 &dir){
            const floating t = normal.dot(dir); // this will be negative because the incoming ray will be in the opposite direction to the normal
            return 0.5 * (1-t) *0.5; // TODO this has been timesed by 0.5 to dampen, make this better e.g pass as parameter
        }

        inline void colourCombine(Vector3 &incident, Vector3 &normal, Vector3 &dir, Vector3 &result){
            const floating factor = ambientFactor(normal, dir);
            // incident light times colour + colour times ambient factor
            Vector3 part1;
            incident.mul(colour, part1);

            Vector3 part2;
            colour.mul(factor, part2);

            part1.add(part2, result);
        }
        inline PlainMaterial& operator=(const PlainMaterial& other){
            smoothness = other.smoothness;
            reflectivity = other.reflectivity;
            colour = other.colour;
            return *this;
        }
    };
}