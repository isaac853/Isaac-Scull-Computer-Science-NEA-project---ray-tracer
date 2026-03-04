#pragma once
#include "math/mathtypes.hpp"
#include "math/Vector3.hpp"
namespace isaac::math {
    /// @brief xz plane
    class Plane{
        private:
        public:

        inline floating intersects(Vector3 &start, Vector3 &dir){
            floating sdotn = start.v[1];
            floating ddotn = dir.v[1];
            if(((sdotn * ddotn )> 0) || ((ddotn > -1e-10) && (ddotn < 1e-10))) return -1.0; // checks if a div by zero occurs, or if plane is behind camera or it hit back of plane
            return -sdotn / ddotn; // TODO kill it with fire
        }
};
}