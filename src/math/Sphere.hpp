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

    inline floating intersects(Vector3 &start, Vector3 &dir){      
        const floating sdots = start.lengthSquared();
        const floating sdotd = start.dot(dir);

        //desc = b^2 - 4ac
        const floating descByFour = sdotd*sdotd - sdots + radiusSquared;
        if (descByFour < 0) return -1.0; //return negative value for no collision

        const floating rootDescByFour = std::sqrt(descByFour); //TODO check how fast this is

        const floating k1 = -sdotd + rootDescByFour;
        const floating k2 = -sdotd - rootDescByFour;

        if (k1 < 0.0 && k2 < 0.0) return -1.0;

        //pick the smallest positive value of k
        const floating kpm = (k1 >= 0.0 && k1 < k2) || k2 < 0.0 ? k1 : k2;

        return kpm;
    }

    inline Sphere& operator=(const Sphere& other){
        radius = other.radius;
        radiusSquared = other.radiusSquared;
        return *this;
    }

};

}  // namespace isaac::math