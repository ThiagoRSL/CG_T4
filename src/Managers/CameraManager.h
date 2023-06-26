#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Managers/CameraManager.h"
#include "Utils/Pnt2.h"

class CameraManager
{
    public:
        static CameraManager &shared_instance() {static CameraManager cameraManager; return cameraManager;}
        CameraManager();
        void SetCameraAnchor(Pnt2* offset);
        void SetCameraOffset(Pnt2 offset);
        void UpdateCameraOffset();
        Pnt2* GetCameraOffsetRef() {return &CameraOffset;}
        Pnt2* GetCameraFocusPoint() {return Anchor;}

        Pnt2* Anchor;
        Pnt2 WindowOffset;
    protected:

    private:
        Pnt2 CameraOffset;
};

#endif // CAMERAMANAGER_H
