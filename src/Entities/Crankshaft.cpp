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

    //Gera P1
    float p1_l = 30;
    float p1_h1 = 40;
    float p1_h2 = 30;

    //Cria centro do Virabrequim
    Poly* p1 = new Poly(this->Anchor->x, this->Anchor->y, RGB);
    p1->AddVertex(-p1_l/2, -p1_h1);
    p1->AddVertex(-p1_l/2, p1_h1);

    p1->AddVertex(p1_l/2, p1_h2);
    p1->AddVertex(p1_l/2, -p1_h2);
    this->AppendPoly(p1);
    //Termina Vibraquim

    //Gera P2
    float p2_l1 = 20;
    float p2_l2 = p1_h1*2;
    //Cria centro do Virabrequim
    Poly* p2 = new Poly(this->Anchor->x, this->Anchor->y, RGB);
    p2->AddVertex(-p1_l/2, -p1_h1);
    p2->AddVertex(-p1_l/2 + (-p2_l1), -p1_h1);

    p2->AddVertex(-p1_l/2 + (-p2_l1), p1_h1);
    p2->AddVertex(-p1_l/2, p1_h1);
    this->AppendPoly(p2);
    //Termina Vibraquim

    //Gera P3
    float p3_dx = -30; // delta no eixo x
    //Cria centro do Virabrequim
    Poly* p3 = new Poly(this->Anchor->x, this->Anchor->y, RGB);

    Pnt2* ps = new Pnt2(-p1_l/2 + (-p2_l1), -p1_h1);
    Pnt2* pt = new Pnt2(-p1_l/2 + (-p2_l1) + p3_dx, 0);
    Pnt2* pf = new Pnt2(-p1_l/2 + (-p2_l1), p1_h1);

    Bezier b = Bezier();
    b.SetCurveResolution(20);
    b.AddControlPoint(ps);
    b.AddControlPoint(pt);
    b.AddControlPoint(pf);
    b.GenerateCurvePoints();
    std::vector<Pnt2*> curvePoints = b.GetCurvePoints();
    int i;
    Pnt2* curvePoint;
    for (i = 0; i < curvePoints.size(); i++)
    {
        curvePoint = curvePoints.at(i);
        p3->AddVertex(curvePoint->x, curvePoint->y);
    }
    this->AppendPoly(p3);


    //Termina Vibraquim

    //Cria SlotPoint
    Vec2* p = new Vec2(-p1_l/2 + (-p2_l1), 0);
    this->AppendPoint(p);
    p->SetAnchor(this->Anchor);
    this->SlotPoint = p;
    //Termina SlotPoint
}

void Crankshaft::AppendPiston(Piston* pis)
{
    Pistons.push_back(pis);
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
