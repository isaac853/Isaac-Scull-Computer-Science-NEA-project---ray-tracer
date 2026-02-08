#include "ray_tracer/objects/RenderableSphere.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

RenderableSphere::RenderableSphere(Transform& t, Sphere& s) : Renderable(t), sphere(s) {}

floating RenderableSphere::intersectsObject(Vector3& start, Vector3& dir) {
    return sphere.intersects(start, dir);
}

}  // namespace isaac::ray_tracer
