#ifndef PISTON_H
#define PISTON_H

#include <Entity.h>
#include "Crankshaft.h"


class Piston : public Entity
{
    private:
        Crankshaft* CrankShaft;
        Pnt2* FixedAt;
        float pistonHeight;
        float connectingRodSize;
        void CalculateHeight();

    public:
        Piston(Crankshaft* cs, float connectingRodSize, float* RGB);
        //virtual ~Piston();
        void Render();

};

#endif // PISTON_H
