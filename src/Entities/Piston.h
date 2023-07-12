#ifndef PISTON_H
#define PISTON_H

#include <Entity.h>
#include "Crankshaft.h"


class Piston : public Entity
{
    public:

    private:
        Crankshaft* CrankShaft;
        Vec2* FixedAt;
        float angle;
        float radius;
        float maxHeight;
        float minHeight;
        float pistonSize;
        int stage;
        Vec2 headPoint;
        Vec2 basePoint;
        float connectingRodSize;
        void CalculateHeadPoint();
        void NextStage();
    public:
        Piston(Crankshaft* cs, float connectingRodSize, float* RGB);
        //virtual ~Piston();


        void SetAngle(float angle) {this->angle = angle;}
        void Render();
        void Render2D();
        void Render3D();

};

#endif // PISTON_H
