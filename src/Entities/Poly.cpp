#include "Poly.h"

Poly::Poly()
{
    this->Anchor = new Pnt2(0, 0);
    this->OrientationVector = new Vec2();
    this->OrientationVector->SetAnchor(this->Anchor);
    rotation = 0;
    Offset = Pnt2(0,0);
    this->show_border = false;
}

Poly::Poly(float x, float y)
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    rotation = 0;
    Offset = Pnt2(0,0);
    this->show_border = false;
}

Poly::Poly(float x, float y, float RGB[3])
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    background_color[0] = RGB[0];
    background_color[1] = RGB[1];
    background_color[2] = RGB[2];
    background_color[3] = 1;
    rotation = 0;
    Offset = Pnt2(0,0);
    this->show_border = false;
}

void Poly::Move(float speed)
{
    Vec2 moveVec = (*OrientationVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}
void Poly::Move(Vec2* directionVector, float speed)
{
    Vec2 moveVec = (*directionVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}


void Poly::SetOrientation(float x, float y)
{
    this->OrientationVector->x = x;
    this->OrientationVector->y = y;
}

void Poly::AddVertex(Vec2* vertex)
{
    vertex->SetAnchor(this->Anchor);
    this->Vertexes.push_back(vertex);
}

void Poly::AddVertex(float x, float y)
{
    Vec2* vertex = new Vec2(x, y);
    vertex->SetAnchor(this->Anchor);
    this->Vertexes.push_back(vertex);
}

void Poly::Resize(float scalar)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->Mult(scalar);
    }
    Vec2 offsetVec = Offset.AsVec();
    offsetVec.Mult(scalar);
    Offset = offsetVec.AsPnt();
}

void Poly::RotateRad(float radians)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->RotateRadians(radians);
    }

    Vec2 offsetVec = Offset.AsVec();
    offsetVec.RotateRadians(radians);
    Offset = offsetVec.AsPnt();

    OrientationVector->RotateRadians(radians);
}

void Poly::Rotate(float degrees)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->RotateDegrees(degrees);
    }
    OrientationVector->RotateDegrees(degrees);

    Vec2 offsetVec = Offset.AsVec();
    offsetVec.RotateDegrees(degrees);
    Offset = offsetVec.AsPnt();

    rotation += degrees;

    if(rotation > 360)
        rotation -= 360;
    else if(rotation < 0)
        rotation += 360;
}

void Poly::Transform(float matrix[2][2])
{
    int i;
    float x, y, newX, newY;
    for(i = 0; i < Vertexes.size(); i++)
    {
        x = Vertexes.at(i)->x;
        y = Vertexes.at(i)->y;
        newX = x * matrix[0][0] + y * matrix[0][1];
        newY = x * matrix[1][0] + y * matrix[1][1];
        Vertexes.at(i)->x = newX;
        Vertexes.at(i)->y = newY;
    }
}

void Poly::Render()
{
    Pnt2* CameraOffset = CameraManager::shared_instance().GetCameraFocusPoint();
    //if(GeometryAux::DistanceBetween(this->Anchor, CameraOffset) > wRenderManager::RENDER_DISTANCE)
    //    return;

    this->RenderBody();
    if(show_border) this->RenderBorder();
}

void Poly::RenderBody()
{
    CV::color(background_color[0], background_color[1], background_color[2]);
    int i, a;
    float virtualX, virtualY;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

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

        float vx[3] = {virtualX, virtualX + Vertexes.at(i)->x, virtualX + Vertexes.at(a)->x};
        float vy[3] = {virtualY, virtualY + Vertexes.at(i)->y, virtualY + Vertexes.at(a)->y};
        CV::polygonFill(vx, vy, 3);
    }
}

void Poly::RenderBorder()
{
    CV::color(border_color[0],border_color[1],border_color[2]);
    int i, j;
    float virtualX, virtualY;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i == Vertexes.size()-1) j = 0;
        else j = i + 1;
        Vec2* pi = Vertexes.at(i);
        Vec2* pj = Vertexes.at(j);

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

        CV::line(virtualX + pi->x, virtualY + pi->y, virtualX + pj->x, virtualY + pj->y);
    }
}

void Poly::RenderVertexes()
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->Render();
    }
}

bool Poly::HasCollision(float x, float y)
{
    int i, a;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

        int counter = 0;
        float virtualX = x, virtualY = y;
        if(!isStatic)
        {
            virtualX = this->Anchor->x + Offset.x - CameraOffsetRef->x;
            virtualY = this->Anchor->y + Offset.y - CameraOffsetRef->y;
        }
        else
        {
            virtualX = StaticOffset.x + Offset.x;
            virtualY = StaticOffset.y + Offset.y;
        }

        if(GeometryAux::Intercept(8000, 8000, x, y, virtualX, virtualY, virtualX + this->Vertexes.at(i)->x, virtualY + this->Vertexes.at(i)->y))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, virtualX, virtualY, virtualX + this->Vertexes.at(a)->x, virtualY + this->Vertexes.at(a)->y))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, virtualX + this->Vertexes.at(i)->x, virtualY + this->Vertexes.at(i)->y, virtualX + this->Vertexes.at(a)->x, virtualY + this->Vertexes.at(a)->y))
        {
            counter += 1;
        }
        if(counter%2 == 1) return true;
    }

    return false;
}

void Poly::SetBackgroundColor(float color[3])
{
    background_color[0] = color[0];
    background_color[1] = color[1];
    background_color[2] = color[2];
    background_color[3] = 1;
}

void Poly::SetBorderColor(float color[3])
{
    border_color[0] = color[0];
    border_color[1] = color[1];
    border_color[2] = color[2];
    border_color[3] = 1;
}

Poly* Poly::GetCopy()
{
    float RGBCopy[3] = {background_color[0], background_color[1], background_color[2]};
    Poly* polyCopy = new Poly(this->Anchor->x, this->Anchor->y);
    polyCopy->SetBackgroundColor(RGBCopy);
    polyCopy->SetOffset(Offset.x, Offset.y);
    int i = 0;
    for(i = 0; i < Vertexes.size(); i++)
    {
        polyCopy->AddVertex(Vertexes.at(i)->GetCopy());
    }
    return polyCopy;
}
