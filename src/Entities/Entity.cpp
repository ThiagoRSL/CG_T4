#include "Entity.h"


Entity::Entity(float x, float y)
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    this->Parts = std::vector<Poly*>();
}
Entity::Entity(float x, float y, float* RGB)
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    this->Parts = std::vector<Poly*>();
}

void Entity::Move(float speed)
{
    Vec2 moveVec = (*OrientationVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}

void Entity::Resize(float scalar)
{
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Resize(scalar);
    }
}

void Entity::Rotate(float degrees)
{
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Rotate(degrees);
    }
    for (i = 0; i < Points.size(); i++)
    {
        Points.at(i)->RotateDegrees(degrees);
    }
    OrientationVector->RotateDegrees(degrees);
}

void Entity::AppendPoly(Poly* poly)
{
    Parts.push_back(poly);
    poly->SetAnchor(this->Anchor);
    poly->SetBackgroundColor(this->background_color);
}

void Entity::AppendPoint(Vec2* point)
{
    point->SetAnchor(this->Anchor);
    this->Points.push_back(point);
}

std::vector<Poly*>* Entity::GetPartsCopy()
{
    std::vector<Poly*>* coppies = new std::vector<Poly*>();
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        coppies->push_back(Parts.at(i)->GetCopy());
    }
    return coppies;
}

Entity* Entity::GetCopy()
{
    Entity* entityCopy = new Entity(this->Anchor->x, this->Anchor->y);
    entityCopy->SetBackgroundColor(this->background_color);
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        entityCopy->AppendPoly(Parts.at(i)->GetCopy());
    }
    return entityCopy;
}

void Entity::SetStatic(bool isStatic)
{
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Static(isStatic);
    }
    this->Static(isStatic);
}

void Entity::SetStaticOffset(float x, float y)
{
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        Poly* part = Parts.at(i);
        part->SetStaticOffset(x, y);
    }
}

Poly* Entity::CollideAt(float x, float y)
{
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        Poly* part = Parts.at(i);
        if(part->HasCollision(x, y))
        {
            return part;
        }
    }
    return nullptr;
}

void Entity::SetFirstPosition(Poly* part)
{
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        if(Parts.at(i) == part)
        {
            Parts.erase(Parts.begin()+i);
            Parts.push_back(part);
        }
    }
}

Vec2* Entity::GetRelativePosition()
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

    return new Vec2(virtualX, virtualY);
}

void Entity::Render()
{
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Render();
    }

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

}
