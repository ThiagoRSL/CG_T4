#ifndef CRANKSHAFT_H
#define CRANKSHAFT_H

#include "FPSManager.h"
#include "Entity.h"
#include "Pnt2.h"
#include "Poly.h"
#include "Curves.h"
#include <vector>

class Piston;

class Crankshaft : public Entity
{
    private:
        bool active;
        bool accelerating;
        float cycleSpeed;
        float radius;
        Vec2* SlotPoint;
        std::vector<Piston*> Pistons;

    public:
        Crankshaft(float x, float y, float r, float* RGB);
        //virtual ~Crankshaft();

        void CreateBody(float r, float* RGB);
        Vec2* GetSlotPoint() {return SlotPoint;}
        void SetActive(bool active) {this->active = active;}
        void SetAccelerating(bool accelerating) {this->accelerating = accelerating;}
        void SetFrequencyCycle(float cycleSpeed) {this->cycleSpeed = cycleSpeed;}
        void AppendPiston(Piston* pis);
        void Render();
        void Render2D();
        void Render3D();
};


#endif // CRANKSHAFT_H
