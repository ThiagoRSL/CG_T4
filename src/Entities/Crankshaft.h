#ifndef CRANKSHAFT_H
#define CRANKSHAFT_H


#include "Entity.h"
#include "Pnt2.h"
#include "Poly.h"
#include "Curves.h"
#include <vector>

class Piston;

class Crankshaft : public Entity
{
    private:
        float radius;
        Vec2* SlotPoint;
        std::vector<Piston*> Pistons;

    public:
        Crankshaft(float x, float y, float r, float* RGB);
        //virtual ~Crankshaft();

        void CreateBody(float r, float* RGB);
        Vec2* GetSlotPoint() {return SlotPoint;}
        void AppendPiston(Piston* pis);
        void Render();
};


#endif // CRANKSHAFT_H
