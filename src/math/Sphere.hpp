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

    inline bool intersects(Vector3 &start, Vector3 &dir, Vector3 &result){
        // to find if the vector intersects the sphere, see where it intersects a plane perpendicular to start, 
        // containing the center of the sphere (0,0,0),
        // and compare intersection point to length of radius
        // TODO include workings for the maths 
        
        
        const floating knum = start.lengthSquared();
        const floating kden = start.dot(dir);

        Vector3 pkden1;
        start.mul(kden, pkden1);

        Vector3 pkden2;
        dir.mul(knum, pkden2);

        Vector3 pkden;
        pkden1.add(pkden2, pkden);

        const floating modpkdenSquared = pkden.lengthSquared();
        const floating modrkdenSquared = radiusSquared * kden*kden;
        
        //compare to see if intersects
        const bool r = modpkdenSquared <= modrkdenSquared;

        //TODO, find p if it does intersect
        return r;

    }

};

}  // namespace isaac::math