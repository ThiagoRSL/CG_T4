#include "Piston.h"


Piston::Piston(Crankshaft* cs, float connectingRodSize, float* RGB)
    : Entity(cs->GetSlotPoint()->x, cs->GetSlotPoint()->y, RGB)
{
    this->CrankShaft = cs;
    cs->AppendPiston(this);
    this->SetAnchor(cs->GetAnchor());
    this->FixedAt = cs->GetSlotPoint();
    this->connectingRodSize = connectingRodSize;
    //this->CreateConnectingRod();
}

/*void Piston::CreateConnectingRod()
{
    Poly* connecctingRod = new Poly(this->Anchor->x, this->Anchor->y, RGB)
    connecctingRod->AddVertex(this->FixedAt);

}*/

void Piston::CalculateHeight()
{
    float s1 = this->FixedAt->x - this->CrankShaft->GetAnchor()->x;
    float s2 = sqrtf((this->connectingRodSize*this->connectingRodSize) - (s1*s1));

    this->pistonHeight = this->FixedAt->y + s2;
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
        CV::color(6);
        CV::circle(virtualX, virtualY, 10, 30);
    }
    this->CalculateHeight();

    Poly p = Poly(0, 0, this->background_color);
    p.SetAnchor(this->Anchor);
    p.AddVertex(this->CrankShaft->GetAnchor()->x + 10, this->CrankShaft->GetAnchor()->y - this->pistonHeight);
    p.AddVertex(this->CrankShaft->GetAnchor()->x - 10, this->CrankShaft->GetAnchor()->y - this->pistonHeight);
    p.AddVertex(this->FixedAt->x - 10, this->FixedAt->y);
    p.AddVertex(this->FixedAt->x + 10, this->FixedAt->y);
    p.Render();
}
