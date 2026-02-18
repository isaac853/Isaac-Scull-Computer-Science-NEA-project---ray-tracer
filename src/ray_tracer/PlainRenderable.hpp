#pragma once
#include "ray_tracer/Renderable.hpp"
#include "ray_tracer/PlainMaterial.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;
    class PlainRenderable:public Renderable{
        protected:
        PlainMaterial material;
        public:
        PlainRenderable(Transform &t, PlainMaterial m);
    };
}
