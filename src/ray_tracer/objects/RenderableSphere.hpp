#pragma once
#include "math/Sphere.hpp"
#include "ray_tracer/Renderable.hpp"
namespace isaac::ray_tracer {
using namespace isaac::math;

class RenderableSphere : public Renderable {
   private:
    Sphere sphere;

   public:
    RenderableSphere(Transform& t, Sphere& s);
    virtual bool intersectsObject(Vector3& start, Vector3& dir, Vector3& result);
};

}  // namespace isaac::ray_tracer
