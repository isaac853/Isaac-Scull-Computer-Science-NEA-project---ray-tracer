#pragma once
#include "math/Sphere.hpp"
#include "ray_tracer/PlainRenderable.hpp"
namespace isaac::ray_tracer {
using namespace isaac::math;

class RenderableSphere : public PlainRenderable {
   private:
    Sphere sphere;

   public:
    RenderableSphere(Transform& t, PlainMaterial& material, Sphere& s);
    virtual floating intersectsObject(Vector3& start, Vector3& dir);

    virtual void render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& colour, int remainingDepth);
};

}  // namespace isaac::ray_tracer
