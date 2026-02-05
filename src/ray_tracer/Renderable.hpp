#pragma once
#include "math/Vector3.hpp"
#include "math/Transform.hpp"
namespace isaac::ray_tracer{
    using namespace isaac::math;

    class Renderable{
        private:
            Transform transform;
        public:
            //virtual allows child classes to redifine what this does
            virtual bool intersects(Vector3 &start, Vector3 &dir, Vector3 &result);
    
    };
}