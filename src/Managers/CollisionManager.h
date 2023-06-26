#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include <map>
#include "Curves.h"

class Poly;
class Character;

class CollisionManager
{
    private:
        std::vector<std::map<Character*, int>*> CharactersWallNearestPoint;
        Character* player_character;
        std::vector<Character*> Characters;
        std::vector<Curve2d*> Walls;
        Poly* Station;

    public:
        static CollisionManager &shared_instance() {static CollisionManager collisionManager; return collisionManager;}
        CollisionManager();

        Character* GetPlayerCharacter();
        void SetPlayerCharacter(Character* player_character);
        void AddNPC(Character* character);
        void RemoveNPC(Character* character);
        void addWall(Curve2d* wall);
        void ClearManager();
        Character* VerifyCollisionNPCs(float x, float y);
        Character* VerifyCollisionPlayer(float x, float y);
        Character* GetClosestEnemy(Pnt2* fromPoint);

        void CheckCollisions();
        bool VerifyCollisionWalls(Character* character);
        bool ArrivedAtStation();
        void SetStation(Poly* station){this->Station = station;}

    protected:

};

#endif // COLLISIONMANAGER_H
