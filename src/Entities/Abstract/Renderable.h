#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "Utils/Pnt2.h"
#include "Managers/CameraManager.h"

class Renderable
{
    public:
        Renderable();
        virtual void Render()=0;

    protected:
        Pnt2* Anchor;
        Pnt2* CameraOffsetRef;
        bool isStatic;

    public:

        void SetAnchor(float x, float y) {this->Anchor = new Pnt2(x, y);}
        void SetAnchor(Pnt2* Anchor) {this->Anchor = Anchor;}
        Pnt2* GetAnchor() {return this->Anchor;}

        Pnt2 Offset;
        Pnt2 StaticOffset;
        virtual void SetOffset(float x, float y)
        {
            Offset.x = x;
            Offset.y = y;
        }
        void SetStaticOffset(float x, float y)
        {
            StaticOffset.x = x;
            StaticOffset.y = y;
        }
        Pnt2 GetPosition()
        {
            float virtualX, virtualY;
            if(!this->isStatic)
            {
                virtualX = Anchor->x + Offset.x - CameraOffsetRef->x;
                virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
            }
            else
            {
                virtualX = StaticOffset.x + Offset.x;
                virtualY = StaticOffset.y + Offset.y;
            }
            return Pnt2(virtualX, virtualY);
        }

        void Static(bool isStatic){this->isStatic = isStatic;}
        bool Static(){return this->isStatic;}

};

#endif // RENDERABLE_H
