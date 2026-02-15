#pragma once
#include "math/Vector3.hpp"
#include "math/Transform.hpp"
#include "math/Matrix4x3.hpp"

namespace isaac::ray_tracer{
    using namespace isaac::math;

    class Renderable{
        private:
            // TODO we almost certainly don't want to keep all of these on the class
            // TODO but lets remove them when we are sure we don't need them any more
            Transform t_f; // Forward quaternion transform
            Transform t_i; // Inverse quaternion transfrom
            Matrix4x3 m_f; // Forward matrix transform
            Matrix4x3 m_i; // Inverse matrix transform
        public:
            Renderable(Transform &t);
            
            //virtual allows child classes to redifine what this does

            //trying to apply inverse transforms to rays instead of transforming objects
            //objects are hard to transform as they have lotss of components
            virtual floating intersectsObject(Vector3 &start, Vector3 &dir);

            //TODO should probably be in mapped renderable class

            // virtual void mapIntersection(
            //     Vector3& p,      // The intersection point 
            //     floating &x,     // The x texture mapping point
            //     floating &y,     // The y texture mapping point
            //     Vector3& normal  // The normal of the surface at the intersection point TODO Think
            // );

            floating intersects(Vector3 &start, Vector3 &dir);
    
            virtual void render(Vector3& dir, Vector3 &intersection, Vector3& colour);
    };
}