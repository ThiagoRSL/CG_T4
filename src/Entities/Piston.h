#ifndef PISTON_H
#define PISTON_H

#include <Entity.h>
#include "Crankshaft.h"


class Piston : public Entity
{
    private:
        Crankshaft* CrankShaft;
        Vec2* FixedAt;
        float angle;
        float radius;
        Vec2 headPoint;
        Vec2 basePoint;
        float connectingRodSize;
        void CalculateHeadPoint();

    public:
        Piston(Crankshaft* cs, float connectingRodSize, float* RGB);
        //virtual ~Piston();


        void SetAngle(float angle) {this->angle = angle;}
        void Render();

};

#endif // PISTON_H
