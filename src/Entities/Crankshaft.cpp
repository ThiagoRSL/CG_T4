#include "Crankshaft.h"
#include "Piston.h"


Crankshaft::Crankshaft(float x, float y, float r, float* RGB)
    :Entity(x, y, RGB)
{
    this->CreateBody(r, RGB);
}

void Crankshaft::CreateBody(float r, float* RGB)
{
    float radius = 50.0;
    float angInit = -(PI/2);
    float angMax = (PI/2);
    float angStep = PI/180;
    float ang;

    //Cria Virabrequim
    Poly* p1 = new Poly(this->Anchor->x, this->Anchor->y, RGB);
    p1->SetOffset(40, 0);
    p1->AddVertex(-90, -20);
    p1->AddVertex(-40, -30);
    for(ang = angInit; ang <= angMax+angStep; ang = ang + angStep)
    {
        p1->AddVertex(-(2*radius/5) + radius * cos(ang), radius * sin(ang));
    }
    p1->AddVertex(-40, 30);
    p1->AddVertex(-90, 20);
    this->AppendPoly(p1);

    Poly* p = new Poly(-40, 0);
    this->AppendPoly(p);
    this->SlotPoint = p->GetAnchor();
    //Termina Vibraquim
}

void Crankshaft::AppendPiston(Piston* pis)
{
    Pistons.push_back(pis);
}

void Crankshaft::Rotate(float degrees)
{
    Entity::Rotate(degrees);
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Rotate(degrees);
    }
    OrientationVector->RotateDegrees(degrees);
}

void Crankshaft::Render()
{
    Entity::Render();

    int i;
    for(i = 0; i < Pistons.size(); i++)
    {
        Pistons.at(i)->Render();
    }
}
