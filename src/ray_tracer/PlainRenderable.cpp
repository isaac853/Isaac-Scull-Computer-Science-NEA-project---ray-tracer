#include "ray_tracer/PlainRenderable.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

PlainRenderable::PlainRenderable(Transform &t, PlainMaterial m):Renderable(t), material(m){}


}