#include "Renderable.h"

#include "Utils/Vec2.h"

Renderable::Renderable()
{
    CameraOffsetRef = CameraManager::shared_instance().GetCameraOffsetRef();
    Static(false);
    this->Anchor = nullptr;
    this->Offset = Pnt2(0,0);
}
