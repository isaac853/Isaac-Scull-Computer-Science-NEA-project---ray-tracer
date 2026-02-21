#pragma once
#include "math/Plane.hpp"
#include "ray_tracer/PlainMaterial.hpp"
#include "ray_tracer/Renderable.hpp"

namespace isaac::ray_tracer {
using namespace isaac::math;

class RenderableLightPlane : public Renderable {
   private:
    floating brightness;
    floating rolloff;
    Vector3 colour;
   public:
    RenderableLightPlane(Transform& t, floating brightness, floating rolloff, Vector3& colour);
    virtual floating intersectsObject(Vector3& start, Vector3& dir);

    virtual void render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& colour, int remainingDepth);
};
}  // namespace isaac::ray_tracer