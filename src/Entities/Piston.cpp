#include "Piston.h"


Piston::Piston(Crankshaft* cs, float connectingRodSize, float* RGB)
    : Entity(cs->GetSlotPoint()->x, cs->GetSlotPoint()->y, RGB)
{
    this->CrankShaft = cs;
    cs->AppendPiston(this);
    this->SetAnchor(cs->GetAnchor());
    this->FixedAt = cs->GetSlotPoint();
    this->connectingRodSize = connectingRodSize;
}

void Piston::CalculateHeight()
{
    float s1 = this->FixedAt->x - this->CrankShaft->GetAnchor()->x;
    float s2 = -200;//sqrtf((this->connectingRodSize*this->connectingRodSize) - (s1*s1));

    this->pistonHeight = this->FixedAt->y + s2;
}

void Piston::Render()
{
    float virtualX, virtualY;
    if(RenderManager::shared_instance().GetShowAnchors())
    {
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
        CV::color(6);
        CV::circle(virtualX, virtualY, 10, 30);
    }

    this->CalculateHeight();
    CV::color(3);
    CV::line(this->FixedAt->x + virtualX, this->FixedAt->y + virtualY, this->CrankShaft->GetAnchor()->x + virtualX, this->CrankShaft->GetAnchor()->y + virtualY + this->pistonHeight);
}
