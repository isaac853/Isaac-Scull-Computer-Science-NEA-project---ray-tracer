#pragma once
#include "math/Vector3.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;
    
//have a flat plane of material that can give smoothness reflectivity maybe transparancy ect. Given an intersection at (x,y) on the material
//want simple special cases e.g a red wrap just returns red and ignores (x,y) intersection point
class Material {
    private:
 //   floating smoothness;
 //   floating reflectivity;
    //transparency
    public:
        virtual void at(
            floating x,
            floating y,
            Vector3& dir,
            floating& smoothness, // Some measure of how we scatter our rays
            floating& reflectivity, // how much we take into account reflected rays
            Vector3& colour // This is reflective colour i.e. the colour in white light
        ) {}; 
    };
}