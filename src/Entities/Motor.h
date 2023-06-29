#ifndef MOTOR_H
#define MOTOR_H

#include "Utils/Pnt2.h"

class Motor
{
    public:
        Motor();
        virtual ~Motor();

    protected:

    private:
};
/*
class Virabrequim : public Entity
{
    private:
        float radius;
        Pnt2 SlotPoint;

    public:
        Virabrequim(float x, float y, float r, float* RGB);
        virtual ~Virabrequim();

        void CreateBody();
        void GetSlotPoint() {return &SlotPoint;}
        void Render();

};

class Pistao : public Entity
{
    private:
        Pnt2* FixedAt;
        float distance;

    public:
        Pistao(Virabrequim* vb, float distance, float* RGB);
        float CalculateHeight();

        void Render();

};*/
#endif // MOTOR_H
