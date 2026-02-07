#include "ray_tracer/Renderable.hpp"
namespace isaac::ray_tracer{
    using namespace isaac::math;

        //empty implementation so linker does not get angry
        bool Renderable::intersectsObject(Vector3 &start, Vector3 &dir, Vector3 &result){
            return false;
        }

        bool Renderable::intersects(Vector3 &start, Vector3 &dir, Vector3 &result){
           //translate start and direction into the coordinate space of our object
            Vector3 os;
            Vector3 od;
            Vector3 ores;
            start.trans(m_i, os); // poinless rotation here
            dir.rot(m_i, od);
            const bool r = intersectsObject(os, od, ores);
            if (r) ores.trans(m_f, result);
            return r;
        }

        Renderable::Renderable(Transform &t):t_f(t){
            t_f.inverse(t_i);
            m_f.set(t_f);
            m_i.set(t_i);
        }








}



