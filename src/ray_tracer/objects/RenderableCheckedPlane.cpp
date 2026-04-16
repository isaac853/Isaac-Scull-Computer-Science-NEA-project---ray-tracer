#include "ray_tracer/objects/RenderableCheckedPlane.hpp"


namespace isaac::ray_tracer {
using namespace isaac::math;

    RenderableCheckedPlane::RenderableCheckedPlane(Transform& t, PlainMaterial& mat1, PlainMaterial& mat2 ):Renderable(t), material1(mat1), material2(mat2){}

    floating RenderableCheckedPlane::intersectsObject(Vector3& start, Vector3& dir){
        return plane.intersects(start, dir);   
    }

    void RenderableCheckedPlane::render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& colour, int remainingDepth){
        //find plane intersection point in plane coords start 
        //intersection is dist * dir + start
        Vector3 intersection;
        dir.mul(dist, intersection);
        intersection.add(start);
        Vector3 transint; // intersection point in the plane coordinates
        Vector3 normal(0.0, 1.0, 0.0);

        intersection.mul(m_f, transint);

        floating scale = 0.25; // Reciprical of the side length of the checks
        floating x = scale * transint.v[0];
        floating y = scale * transint.v[2];

        //fix for middle range issue
        int64_t xi = x < 0.0 ? (int64_t)(x - 0.5): (int64_t)(x + 0.5);
        int64_t yi = y < 0.0 ? (int64_t)(y - 0.5): (int64_t)(y + 0.5);

        // int64_t xi = (int64_t)x;
        // int64_t yi = (int64_t)y;

        Vector3 reflectedColour;
        Vector3 reflectedDir;

        simpleReflect(dir, normal, reflectedDir);
        ray_tracer.render(intersection, reflectedDir, reflectedColour, remainingDepth);

        (((xi ^ yi) & 1) ? material1 : material2).colourCombine(reflectedColour, normal, dir, colour);             
    }


}