#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include <vector>
#include <map>
#include "Utils/Pnt2.h"
#include "Entities/Entity.h"
#include "ShipPart.h"
#include "Slot.h"
#include "Entities/Weapon/Weapon.h"
#include "Entities/Weapon/Projectile.h"
#include "Particle.h"

class PlayerManager;
class UIManager;
class HoomingProjectile;

class Character : public Entity
{
    public:
        Character(float x, float y, float RGB[3]);

        void AimTo(float x, float y);
        void SetRotating(float degree);
        void SetMoving(float movement);
        void ActivateSpecial(int special_id);
        void Shoot();
        void ReceiveDamage(float damage);

        void AnimateDeath();
        void BurstAnimation();
        void LeftTrail();
        void Die();

        bool HasCollisionOnParts(float x, float y);


        void RefreshWeaponsCooldown();
        void ResetControls();

        void Render();
        void RenderBody();
        void RenderWeapons();
        void RenderShipParts();
        void RenderTrail();

        void AppendPart(ShipPart* part);
        void RemovePart(ShipPart* part);
        void UpdateParts();
        void UpdatePartsModifiers();
        void RemovePartsModifiers();

        void CreatePartSlot(int type_part_id, Pnt2 offset);
        void Rotate(float degrees);
        bool EquipWeapon(Weapon* weapon);

        void UpdateWeaponAim();

        void MoveDirection(Vec2* directionVector, float speed);
        void TeleportTo(float x, float y) {Anchor->x = x; Anchor->y = y;}

    protected:
        std::map<int, std::pair<Pnt2*, ShipPart*>> ShipParts;
        std::vector<WeaponSlot*> WeaponSlots;
        Particle* Trail;
        //SpecialPower* Special;
        Pnt2* AimPoint;
        Vec2* AimVector;
        //Control Variables
        float rotating;
        float moving;
        int score_val;


        //Base stats
        float movement_speed;
        float rotation_speed;
        float speed;
        float energy_max;
        float energy;

        // Life
        float hit_points_max;
        float hit_points;
        bool dying;
        bool dead;
        bool deactivated;

        //Autonomy
        float aim_accuracy;
        Character* Target;
        Pnt2* target_last_known_location;
        bool autonomous;
        float view_range;

        //specials
        bool dashing;
        void SpawnHommies();

        // Death Animation
        int death_frame;
        float death_rgb_save[3];
        float last_death_frame;

        float last_frame;
        void AutonomousThinking();
    //Getters e Setters
    public:
        bool IsDying() {return this->dying;}
        bool IsDead() {return this->dead;}
        bool IsDashing() {return this->dashing;}
        Pnt2* GetAimPoint() {return this->AimPoint;}
        float* GetHitPointsMaxRef() {return &this->hit_points_max;}
        float* GetHitPointsRef() {return &this->hit_points;}
        float* GetEnergyMaxRef() {return &this->energy_max;}
        float* GetEnergyRef() {return &this->energy;}
        void SetMaxHitPoints(float hitPoints);
        void SetMaxEnergy(float energy);
        void SetViewRange(float view_range) {this->view_range = view_range;}
        void SetScoreValue(int scoreVal) {this->score_val = scoreVal;}
        void SetMovementSpeed(float movementSpeed);
        void DrawEnergy(float energyPoints);

        void SetAutonomous(bool autonomous){this->autonomous = autonomous;}
        bool SetTarget(Character* target) {this->Target = target;}
    //Autonomy
    public:
        void AutonomyAdjustAim();
};

#endif // CHARACTER_H
