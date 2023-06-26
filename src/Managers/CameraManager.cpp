#include "CameraManager.h"

CameraManager::CameraManager()
{
    WindowOffset = Pnt2(0,0);
    Anchor = new Pnt2(0,0);
}

void CameraManager::SetCameraAnchor(Pnt2* anchor)
{
    Anchor = anchor; //Seguindo esta ancôra
}

void CameraManager::SetCameraOffset(Pnt2 offset)
{
    WindowOffset.x = offset.x;
    WindowOffset.y = offset.y;
}

void CameraManager::UpdateCameraOffset()
{
    CameraOffset.x = Anchor->x + WindowOffset.x;
    CameraOffset.y = Anchor->y + WindowOffset.y;
}
