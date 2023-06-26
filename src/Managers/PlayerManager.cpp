#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
    //ctor
}

void PlayerManager::SetPlayerCharacter(Character* character)
{
    this->PlayerCharacter = character;
}

void PlayerManager::CheckInteraction()
{
    if(PlayerCharacter == nullptr)
        return;

    float mouseX = (MouseManager::shared_instance().PosX - PlayerCharacter->GetAnchor()->x) + CameraManager::shared_instance().GetCameraOffsetRef()->x;
    float mouseY = (MouseManager::shared_instance().PosY - PlayerCharacter->GetAnchor()->y) + CameraManager::shared_instance().GetCameraOffsetRef()->y;
    PlayerCharacter->AimTo(mouseX, mouseY);
}

bool PlayerManager::IsGameOver()
{
    if(PlayerCharacter == nullptr)
        return true;
    if(PlayerCharacter->IsDead() || PlayerCharacter->IsDying())
        return true;
    return false;
}
