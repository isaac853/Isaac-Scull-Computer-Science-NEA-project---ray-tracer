#include "ray_tracer/objects/RenderableLightPlane.hpp"


namespace isaac::ray_tracer {
using namespace isaac::math;

    RenderableLightPlane::RenderableLightPlane(Transform& t, floating b, floating r, Vector3& col):Renderable(t), brightness(b), rolloff(r), colour(col){}

    floating RenderableLightPlane::intersectsObject(Vector3& start, Vector3& dir){
        //distace = center dot direction take start point dot direction
        return - start.dot(dir);
    }

    void RenderableLightPlane::render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& kolour, int remainingDepth){
        //find plane intersection point in plane coords start 
        //intersection is dist * dir + start
        Vector3 intersection;
        dir.mul(dist, intersection);
        intersection.add(start);
        
        Vector3 center(t_f.tx, t_f.ty, t_f.tz);
        Vector3 centerToIntersection;
        center.sub(intersection, centerToIntersection);
        floating dsquared = centerToIntersection.lengthSquared();
        floating factor = dsquared * rolloff * rolloff;
        Vector3 lightColour;
        colour.mul(factor < 1.0 ? brightness : brightness/factor, lightColour);

        Vector3 tcol;
        ray_tracer.render(intersection, dir, tcol, remainingDepth);

        tcol.add(lightColour, kolour);
    } 
}
