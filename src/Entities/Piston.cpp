#include "Piston.h"


Piston::Piston(Crankshaft* cs, float connectingRodSize, float* RGB)
    : Entity(cs->GetSlotPoint()->x, cs->GetSlotPoint()->y, RGB)
{
    this->CrankShaft = cs;
    cs->AppendPiston(this);
    this->SetAnchor(cs->GetAnchor());
    this->FixedAt = cs->GetSlotPoint();
    this->radius = GeometryAux::DistanceBetween(FixedAt->x, FixedAt->y, 0, 0);
    printf("\nRADIO %f", this->radius);

    this->connectingRodSize = connectingRodSize;
    this->angle = 0;
    //this->CreateConnectingRod();
}

/*void Piston::CreateConnectingRod()
{
    Poly* connecctingRod = new Poly(this->Anchor->x, this->Anchor->y, RGB)
    connecctingRod->AddVertex(this->FixedAt);

}*/

void Piston::CalculateHeadPoint()
{
    float ang = GeometryAux::AngleBetweenFull(this->CrankShaft->GetAnchor()->x, this->CrankShaft->GetAnchor()->y, this->CrankShaft->GetAnchor()->x+this->FixedAt->x, this->CrankShaft->GetAnchor()->y+this->FixedAt->y)*2*PI/360;
    //printf("\n P1(%f,%f) P2(%f,%f) Angle %f", this->CrankShaft->GetAnchor()->x, this->CrankShaft->GetAnchor()->y, this->CrankShaft->GetAnchor()->x+this->FixedAt->x, this->CrankShaft->GetAnchor()->y+this->FixedAt->y, ang);

    float fx = FixedAt->x;
    float fy = FixedAt->y;
    //printf("\n Fx %f Fy %f", fx, fy);

    float sx = cos(ang) * this->radius;
    float dh = sqrtf((this->connectingRodSize*this->connectingRodSize) - (sx*sx));

    this->basePoint = Vec2(cos(ang)*radius, -sin(ang)*radius);
    this->headPoint = Vec2(0, -(dh + sin(ang) * radius));
    //printf("\n TAMANO DO CONNECT ROD: %f", GeometryAux::DistanceBetween(headPoint.x, headPoint.y, FixedAt->x, FixedAt->y));
}

void Piston::Render()
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
    if(RenderManager::shared_instance().GetShowAnchors())
    {
        CV::color(2);
        CV::circle(virtualX + this->FixedAt->x, virtualY + this->FixedAt->y, 100, 30);
        CV::circle(virtualX + this->FixedAt->x, virtualY + this->FixedAt->y, 100, 30);
    }

    FixedAt->RotateDegrees(-angle);
    this->CalculateHeadPoint();

    Vec2 vecDiffCrankPiston = Vec2(this->CrankShaft->GetAnchor()->x - this->Anchor->x,this->CrankShaft->GetAnchor()->y - this->Anchor->y);
    Vec2* PistonPos = new Vec2(headPoint.x, headPoint.y);
    Vec2* FixedCopy = FixedAt->GetCopy();

    Poly p = Poly(0, 0, this->background_color);
    p.SetAnchor(this->Anchor);
    p.AddVertex(PistonPos->x + 10, PistonPos->y); //- (10*cos(angle*PI/180)));
    p.AddVertex(PistonPos->x - 10, PistonPos->y); //+ (10*cos(angle*PI/180)));
    p.AddVertex(FixedAt->x - 10, FixedAt->y);
    p.AddVertex(FixedAt->x + 10, FixedAt->y);
    printf("\n TAMANO DO CONNECT ROD (ROTADO): %f", GeometryAux::DistanceBetween(PistonPos->x, PistonPos->y, FixedAt->x, FixedAt->y));
    //p.AddVertex(basePoint.x - 10, basePoint.y);
    //p.AddVertex(basePoint.x + 10, basePoint.y);
    p.Rotate(angle);
    p.Render();
    PistonPos->RotateDegrees(angle);
    FixedAt->RotateDegrees(angle);
}
