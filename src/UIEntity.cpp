#include "UIEntity.h"

UIEntity::UIEntity(float x, float y)
    : Entity(x, y)
{
    this->Anchor = new Pnt2(x, y);
}
