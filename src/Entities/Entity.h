#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <vector>
#include "Utils/Pnt2.h"
#include "Utils/Vec2.h"
#include "Poly.h"

class Entity : public Renderable
{
    public:
        Entity(float x, float y);
        Entity(float x, float y, float* RGB);
        void AppendPoly(Poly* poly);
        void Render();

        void Move(float speed);
        void Resize(float scalar);
        virtual void Rotate(float degrees);
        Poly* CollideAt(float x, float y);
        void SetFirstPosition(Poly* part);

    protected:
        Vec2* OrientationVector;
        std::vector<Poly*> Parts;

        float background_color[3];

    public:
        Entity* GetCopy();
        std::vector<Poly*>* GetPartsCopy();
        void SetStatic(bool isStatic);
        void SetStaticOffset(float x, float y);
        void SetBackgroundColor(float* RGB)
        {
            this->background_color[0] = RGB[0];
            this->background_color[1] = RGB[1];
            this->background_color[2] = RGB[2];
        }
        void SetOrientationVector(Vec2* orientationVector){this->OrientationVector = orientationVector;}
        Vec2* GetOrientationVector(){ return OrientationVector;}

};

#endif // ENTITY_H
