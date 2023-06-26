#ifndef PARTICLE_H
#define PARTICLE_H

#include "Abstract/Renderable.h"
#include "RenderManager.h"
#include "FPSManager.h"
#include "map"
#include "tuple"

class Particle : public Renderable
{
    public:
        Particle(float framesToLive, float *RGB);

        void AddPoint(float x, float y);
        void Render();

        float* GetRGBRef() {return RGB;}
    protected:

    private:
        std::map<std::tuple<float, float>, int> Points;
        float RGB[3];
        float framesToLive;
        float lastFrame;
};

#endif // PARTICLE_H
