#pragma once
#include "math/mathtypes.hpp"
#include "math/Vector3.hpp"
namespace isaac::math {
    /// @brief xz plane
    class Plane{
        private:
        public:

        inline floating intersects(Vector3 &start, Vector3 &dir){
            //plane is parralel to xz plane, so sdotn and ddotn are trivial
            floating sdotn = start.v[1];
            floating ddotn = dir.v[1];
            
            // checks if a div by zero occurs, or if plane is behind camera or it hit back of plane
            if(((sdotn * ddotn )> 0) || ((ddotn > -1e-10) && (ddotn < 1e-10))) return -1.0;
            return -sdotn / ddotn; 
        }
};
}