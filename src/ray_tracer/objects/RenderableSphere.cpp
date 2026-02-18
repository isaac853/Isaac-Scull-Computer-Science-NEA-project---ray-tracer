#include "ray_tracer/objects/RenderableSphere.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

RenderableSphere::RenderableSphere(Transform& t, PlainMaterial& m, Sphere& s ) : PlainRenderable(t,m), sphere(s) {}

floating RenderableSphere::intersectsObject(Vector3& start, Vector3& dir) {
    return sphere.intersects(start, dir);
}

void RenderableSphere::render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& colour ){
    //intersection is dist * dir + start
    Vector3 intersection;
    dir.mul(dist, intersection);
    intersection.add(start);

    //translate object coord center point(0,0,0) into world coords 
    Vector3 center;
    center.trans(m_f, center);

    Vector3 normal;
    intersection.sub(center, normal);
    normal.normalise(); // TODO we can achieve this by multiplying by reciprocal of radius

    Vector3 black;
    material.colourCombine(black, normal, dir, colour);
    }
}  // namespace isaac::ray_tracer
