#pragma once
#include "math/Plane.hpp"
#include "ray_tracer/PlainMaterial.hpp"
#include "ray_tracer/Renderable.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

class RenderableCheckedPlane : public Renderable {
   private:
    Plane plane;
    PlainMaterial material1;
    PlainMaterial material2;
    //    floating sqauareScale;
   public:
    RenderableCheckedPlane(Transform& t, PlainMaterial& material1, PlainMaterial& material2);
    virtual floating intersectsObject(Vector3& start, Vector3& dir);

    virtual void render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& colour, int remainingDepth);
};
}  // namespace isaac::ray_tracer