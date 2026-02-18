#include "ray_tracer/Renderable.hpp"
namespace isaac::ray_tracer{
    using namespace isaac::math;

        //empty implementation so linker does not get angry
        floating Renderable::intersectsObject(Vector3 &start, Vector3 &dir){
            return false;
        }

        floating Renderable::intersects(Vector3 &start, Vector3 &dir){
           //translate start and direction into the coordinate space of our object
            Vector3 os;
            Vector3 od;
            start.trans(m_i, os);
            dir.rot(m_i, od);
            return intersectsObject(os, od);
        }

        Renderable::Renderable(Transform &t):t_f(t){
            t_f.inverse(t_i);
            m_f.set(t_f);
            m_i.set(t_i);
        }
        void Renderable::render(RayTracer& ray_tracer, Vector3& start, Vector3& dir, floating dist, Vector3& colour ){
            colour.set(0.0, 0.0, 0.0); // pointless implementation as this will not be called
        }







}



