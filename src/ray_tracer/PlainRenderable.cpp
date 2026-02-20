#include "ray_tracer/PlainRenderable.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

PlainRenderable::PlainRenderable(Transform &t, PlainMaterial m):Renderable(t), material(m){}

//TODO this might belong somewhere else
void PlainRenderable::simpleReflect(Vector3& dir, Vector3& normal, Vector3& result){
//dot normal with dir and times by 2 then add to dir
    floating dirDotNormal = dir.dot(normal);
    normal.mul((dirDotNormal*-2.0), result);
    result.add(dir);
}
}