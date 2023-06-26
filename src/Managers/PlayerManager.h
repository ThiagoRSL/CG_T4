#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Character/Character.h"

class PlayerManager
{
    public:
        PlayerManager();
        static PlayerManager &shared_instance() {static PlayerManager playerManager; return playerManager;}

        void CheckInteraction();
        bool IsGameOver();

    private:
        Character* PlayerCharacter;

    public:
        void SetPlayerCharacter(Character* character);
        Character* GetPlayerCharacter() {return PlayerCharacter;}
};

#endif // PLAYERMANAGER_H
