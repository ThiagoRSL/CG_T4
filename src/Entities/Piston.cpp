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


    this->maxHeight = -this->connectingRodSize + radius;
    this->minHeight = -this->connectingRodSize - radius;
    this->pistonSize = 40;
    this->stage = 1;
}

void Piston::NextStage()
{
    if(this->stage >= 4)
        this->stage = 1;
    else
        this->stage++;

}
void Piston::CalculateHeadPoint()
{
    float ang = GeometryAux::AngleBetweenFull(this->CrankShaft->GetAnchor()->x, this->CrankShaft->GetAnchor()->y, this->CrankShaft->GetAnchor()->x+this->FixedAt->x, this->CrankShaft->GetAnchor()->y+this->FixedAt->y)*2*PI/360;


    if(maxHeight - 15 < headPoint.y) // Atingiu o fundo
    {
        printf("Min Height %f ", minHeight);
        printf(" Max Height %f ", maxHeight);
        printf(" Height %f \n", headPoint.y);
        printf("Não mudei?\n");
        if(stage%2 == 1)
            NextStage();
    }
    else if(minHeight + 15 > headPoint.y)
    {
        printf("Min Height %f ", minHeight);
        printf(" Max Height %f ", maxHeight);
        printf(" Height %f \n", headPoint.y);
        printf("Não mudei?2\n");
        if(stage%2 == 0)
            NextStage();
    }

    float fx = FixedAt->x;
    float fy = FixedAt->y;
    //printf("\n Fx %f Fy %f", fx, fy);

    float sx = cos(ang) * this->radius;
    float dh = sqrtf((this->connectingRodSize*this->connectingRodSize) - (sx*sx));

    this->basePoint = Vec2(cos(ang)*radius, -sin(ang)*radius);
    Vec2 newHeadPoint = Vec2(0, -(dh + sin(ang) * radius));
    this->headPoint = newHeadPoint;
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

    //Connection Rod
    Poly p = Poly(0, 0, this->background_color);
    p.SetAnchor(this->Anchor);
    p.AddVertex(PistonPos->x + 10, PistonPos->y); //- (10*cos(angle*PI/180)));
    p.AddVertex(PistonPos->x - 10, PistonPos->y); //+ (10*cos(angle*PI/180)));
    p.AddVertex(FixedAt->x - 10, FixedAt->y);
    p.AddVertex(FixedAt->x + 10, FixedAt->y);
    //printf("\n TAMANO DO CONNECT ROD (ROTADO): %f", GeometryAux::DistanceBetween(PistonPos->x, PistonPos->y, FixedAt->x, FixedAt->y));

    //Pistão
    Poly p2 = Poly(0, 0, this->background_color);
    p2.SetAnchor(this->Anchor);
    p2.AddVertex(PistonPos->x + pistonSize/2, PistonPos->y + pistonSize/2); //- (10*cos(angle*PI/180)));
    p2.AddVertex(PistonPos->x - pistonSize/2, PistonPos->y + pistonSize/2); //+ (10*cos(angle*PI/180)));
    p2.AddVertex(PistonPos->x - pistonSize/2, PistonPos->y - pistonSize/2);
    p2.AddVertex(PistonPos->x + pistonSize/2, PistonPos->y - pistonSize/2);

    float tubeColor[3] = {0.75, 0.75, 0.75};
    float nothingColor[3] = {0.3, 0.9, 0.9};
    float fuelColor[3] = {0, 0.5, 1};
    float explosionColor[3] = {1, 0.5, 0};
    float exaustionColor[3] = {0.5, 0.5, 0.5};
    //Camisa
    Poly c = Poly(0, 0, this->background_color);
    c.SetAnchor(this->Anchor);

    //Lateral Esquerda
    c.AddVertex(PistonPos->x - pistonSize/2, minHeight + connectingRodSize - pistonSize/2 - 10);
    c.AddVertex(PistonPos->x - 10 - pistonSize/2, minHeight + connectingRodSize - pistonSize/2 - 10);
    c.AddVertex(PistonPos->x - 10 - pistonSize/2, minHeight - pistonSize/2 - 10); //+ (10*cos(angle*PI/180)));
    c.AddVertex(PistonPos->x - pistonSize/2, minHeight - pistonSize/2 - 10); //- (10*cos(angle*PI/180)));
    c.SetBackgroundColor(tubeColor);

    Poly c2 = Poly(0, 0, this->background_color);
    c2.SetAnchor(this->Anchor);
    c2.AddVertex(PistonPos->x - pistonSize/2 - 10, minHeight - pistonSize/2 - 10);
    c2.AddVertex(PistonPos->x + pistonSize/2 + 10, minHeight - pistonSize/2 - 10);
    c2.AddVertex(PistonPos->x + pistonSize/2 + 10, minHeight - pistonSize/2 - 20);
    c2.AddVertex(PistonPos->x - pistonSize/2 - 10, minHeight - pistonSize/2 - 20);
    c2.SetBackgroundColor(tubeColor);

    //Lateral Direita
    Poly c3 = Poly(0, 0, this->background_color);
    c3.SetAnchor(this->Anchor);
    c3.AddVertex(PistonPos->x + pistonSize/2, minHeight + connectingRodSize - pistonSize/2 - 10);
    c3.AddVertex(PistonPos->x + 10 + pistonSize/2, minHeight + connectingRodSize - pistonSize/2 - 10);
    c3.AddVertex(PistonPos->x + 10 + pistonSize/2, minHeight - pistonSize/2 - 10); //+ (10*cos(angle*PI/180)));
    c3.AddVertex(PistonPos->x + pistonSize/2, minHeight - pistonSize/2 - 10); //- (10*cos(angle*PI/180)));
    c3.SetBackgroundColor(tubeColor);


    //Effect
    Poly e = Poly(0, 0, this->background_color);
    e.SetAnchor(this->Anchor);
    e.AddVertex(PistonPos->x + pistonSize/2, minHeight - pistonSize/2 - 10); //- (10*cos(angle*PI/180)));
    e.AddVertex(PistonPos->x - pistonSize/2, minHeight - pistonSize/2 - 10); //+ (10*cos(angle*PI/180)));
    e.AddVertex(PistonPos->x - pistonSize/2, PistonPos->y - pistonSize/2);
    e.AddVertex(PistonPos->x + pistonSize/2, PistonPos->y - pistonSize/2);
    if(stage == 1)
        e.SetBackgroundColor(nothingColor);
    else if(stage == 2) // COmprime e estora
        e.SetBackgroundColor(fuelColor);
    else if(stage == 3)
        e.SetBackgroundColor(explosionColor);
    else if(stage == 4)
        e.SetBackgroundColor(exaustionColor);

    p.Rotate(angle);
    p2.Rotate(angle);
    c.Rotate(angle);
    c2.Rotate(angle);
    c3.Rotate(angle);
    e.Rotate(angle);

    if(RenderManager::shared_instance().show_piston_tube)
    {
        c.Render();
        c2.Render();
        c3.Render();
    }
    if(RenderManager::shared_instance().show_effects)
    {
        e.Render();
    }

    if(RenderManager::shared_instance().show_connectionRod)
    {
        p.Render();
    }
    if(RenderManager::shared_instance().show_piston)
    {
        p2.Render();
    }
    PistonPos->RotateDegrees(angle);
    FixedAt->RotateDegrees(angle);
}
