#include "ray_tracer/PlainMaterial.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

PlainMaterial::PlainMaterial(floating s, floating r, Vector3& c):smoothness(s), reflectivity(r), colour(c){}
}