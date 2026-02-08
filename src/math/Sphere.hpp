#pragma once
#include "math/mathtypes.hpp"
#include "math/Vector3.hpp"
namespace isaac::math {
class Sphere {
   private:
    floating radius;
    floating radiusSquared;
   public:
   //sphere radius r about (0,0,0)
    Sphere(floating r) : radius(r), radiusSquared(r*r) {}
    
    inline floating descriminantcalc(Vector3 &start, Vector3 &dir){
        const floating knum = start.lengthSquared();
        const floating kden = start.dot(dir);

        //desc = b^2 - 4ac

        floating descByFour = kden*kden - knum + radiusSquared;
        return descByFour;
    }

    inline bool intersects(Vector3 &start, Vector3 &dir, Vector3 &result){      
        const floating descByFour = descriminantcalc(start, dir);
        return descByFour >= 0;
    }

    inline Sphere& operator=(const Sphere& other){
        radius = other.radius;
        radiusSquared = other.radiusSquared;
        return *this;
    }

};

}  // namespace isaac::math