#pragma once
#include <vector>
#include "math/Vector3.hpp"
#include "ray_tracer/Renderable.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;
    class RayTracer{
    private:
    //pointers are super scary, be careful
    std::vector<Renderable*> renderables;
    public:
    //takes a direction vector and returns a colour (stored in a vector class for convenience)
    //by ref used for both to avoid space reallocation
        void render(Vector3& dir, Vector3& colour);

        inline void add(Renderable* r){
            renderables.push_back(r);
        }
    };
}
