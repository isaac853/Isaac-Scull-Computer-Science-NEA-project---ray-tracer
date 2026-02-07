#include "ray_tracer/objects/RenderableSphere.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

RenderableSphere::RenderableSphere(Transform& t, Sphere& s) : Renderable(t), sphere(s) {}

bool RenderableSphere::intersectsObject(Vector3& start, Vector3& dir, Vector3& result) {
    return true;
}

}  // namespace isaac::ray_tracer
