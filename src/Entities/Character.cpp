#include "Character.h"
#include "PlayerManager.h"
#include "UIManager.h"
#include "Entities/Weapon/HoomingProjectile.h"

static int death_frames = 20;

Character::Character(float x, float y, float RGB[3])
    :Entity(x, y)
{
    Entity::SetBackgroundColor(RGB);
    this->OrientationVector->y = -1;
    this->OrientationVector->x = 0;
    this->AimPoint = new Pnt2(0, -1);
    this->AimVector = new Vec2(0, -1);

    this->movement_speed = 500;
    this->rotation_speed = 200;

    //Autonomous Module
    this->autonomous = false;
    this->view_range = 200;
    this->Target = nullptr;
    this->target_last_known_location = new Pnt2(x, y);
    aim_accuracy = 2;

    this->score_val = 0;

    this->hit_points_max = 1;
    this->hit_points = 1;
    this->energy_max = 1;
    this->energy = 1;

    this->dying = false;
    this->dead = false;
    //Controls
    this->rotating = 0;
    this->moving = 0;
    this->Trail = new Particle(20, RGB);

    this->dashing = false;
    //Ir pro laranja quando morre
    this->death_rgb_save[0] = 1 - this->background_color[0];
    this->death_rgb_save[1] = (1 - this->background_color[1])/4;
    this->death_rgb_save[2] = - this->background_color[2];
}
void Character::SetMovementSpeed(float movementSpeed)
{
    this->movement_speed = movementSpeed;
}
void Character::SetMaxHitPoints(float hitPoints)
{
    this->hit_points_max = hitPoints;
    this->hit_points = hit_points_max;
}
void Character::SetMaxEnergy(float energy)
{
    this->energy_max = energy;
    this->energy = energy;
}
void Character::AutonomyAdjustAim()
{
    if(Target == nullptr)
        return;

    float targetX = target_last_known_location->x - this->Anchor->x;
    float targetY = target_last_known_location->y - this->Anchor->y;

    AimTo(targetX, targetY);
}

void Character::AimTo(float x, float y)
{
    this->AimPoint->x = x;
    this->AimPoint->y = y;

    this->AimVector->x = x;
    this->AimVector->y = y;
    this->AimVector->Normalize();

    UpdateWeaponAim();
}

void Character::SetRotating(float degree)
{
    this->rotating = degree;
}
void Character::SetMoving(float movement)
{
    this->moving = movement;
}

void Character::Shoot()
{
    int i;
    for(i = 0; i < WeaponSlots.size(); i++)
    {
        if(WeaponSlots.at(i)->HasWeapon())
            WeaponSlots.at(i)->EquippedWeapon->Shoot();
    }
}
void Character::SpawnHommies()
{
    HoomingProjectile* shotPoly = new HoomingProjectile(this->Anchor->x + 30, this->Anchor->y + 30, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x - 30, this->Anchor->y - 30, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x + 30, this->Anchor->y - 30, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x - 30, this->Anchor->y + 30, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x - 50, this->Anchor->y, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x + 50, this->Anchor->y, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x, this->Anchor->y - 50, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);

    shotPoly = new HoomingProjectile(this->Anchor->x, this->Anchor->y + 50, 25, 0, 10000, this->background_color, this);
    shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
    RenderManager::shared_instance().AddRenderableToList(shotPoly);
}

void Character::ActivateSpecial(int special_id)
{
    printf("\nCharacter used special: %i.", special_id);
    switch(special_id)
    {
        case 1:
            if(energy > 0)
            {
                this->dashing = !this->dashing;
            }
            break;
        case 2:
            if(energy >= 25)
            {
                DrawEnergy(25);
                SpawnHommies();
            }
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

void Character::Rotate(float degrees)
{
    int i;
    for (i = 0; i < WeaponSlots.size(); i++)
    {
        if(WeaponSlots.at(i)->HasWeapon())
            WeaponSlots.at(i)->EquippedWeapon->Rotate(degrees);
    }
    Entity::Rotate(degrees);
}

void Character::ReceiveDamage(float damage)
{
    if(dying || dead)
        return;

    this->hit_points = hit_points - damage;
    if(this->hit_points <= 0)
    {
        dying = true;
        death_frame = 0;
        hit_points = 0;
    }
}
void Character::AnimateDeath()
{
    float frames = FPSManager::shared_instance().GetFrames();
    if(last_death_frame != frames)
    {
        death_frame++;
        last_death_frame = frames;
        int i;
        for(i = 0; i < Entity::Parts.size(); i++)
        {
            Poly* part = Entity::Parts.at(i);
            float* rgb = part->GetBackgroundColorRef();
            rgb[0] += death_rgb_save[0]/death_frames;
            rgb[1] += death_rgb_save[1]/death_frames;
            rgb[2] += death_rgb_save[2]/death_frames;
        }
    }
}

void Character::BurstAnimation()
{
    return;
}

void Character::Die()
{
    dying = false;
    dead = true;

    UIManager::shared_instance().AddScore(this->score_val);
    //BurstAnimation();

    if(PlayerManager::shared_instance().GetPlayerCharacter() == this)
    {
        PlayerManager::shared_instance().SetPlayerCharacter(nullptr);
        CollisionManager::shared_instance().SetPlayerCharacter(nullptr);
    }
    RenderManager::shared_instance().RemoveRenderableFromList(this);
    CollisionManager::shared_instance().RemoveNPC(this);
}

void Character::Render()
{
    float frames = FPSManager::shared_instance().GetFrames();

    Trail->Render();
    //Checa a distÂncia do personagem pra ver se ele deve ser renderizado.
    if(GeometryAux::DistanceBetween(this->Anchor, CameraManager::shared_instance().Anchor) > RenderManager::RENDER_DISTANCE)
        return;

    if(dead)
        return;



    if(dying)
    {
        this->AnimateDeath();
        if(death_frame == death_frames)
        {
            this->BurstAnimation();
            this->Die();
        }
        Entity::Render();
        if(CollisionManager::shared_instance().GetPlayerCharacter() == this) CollisionManager::shared_instance().SetPlayerCharacter(nullptr);
        return;
    }


    RefreshWeaponsCooldown();

    if(!PlayerManager::shared_instance().IsGameOver())
    {
        if(autonomous)  AutonomousThinking();
        if(moving)
        {
            Trail->AddPoint(this->Anchor->x, this->Anchor->y);
            float displacement;
            if(dashing)
            {
                if(last_frame != frames)
                    DrawEnergy(1);
                if(energy == 0)
                {
                    dashing = false;
                }

                Trail->AddPoint(this->Anchor->x-20, this->Anchor->y);
                Trail->AddPoint(this->Anchor->x-10, this->Anchor->y);
                Trail->AddPoint(this->Anchor->x+10, this->Anchor->y);
                Trail->AddPoint(this->Anchor->x+20, this->Anchor->y);
                displacement = 3*moving*movement_speed/FPSManager::shared_instance().GetFrames();
            }
            else
            {
                displacement = moving*movement_speed/FPSManager::shared_instance().GetFrames();
            }
            Move(displacement);
        }
        if(rotating)    Rotate(rotating*rotation_speed/FPSManager::shared_instance().GetFrames());
        if(CollisionManager::shared_instance().VerifyCollisionWalls(this)) ReceiveDamage(1000);
    }

    Entity::Render();
    RenderWeapons();
    if(last_frame != frames)
        last_frame = frames;
}

void Character::DrawEnergy(float energyPoints)
{
    if(this->energy - energyPoints < 0)
        this->energy = 0;
    else
        this->energy -= energyPoints;
}

void Character::RenderWeapons()
{
    int i;
    for(i = 0; i < WeaponSlots.size(); i++)
    {
        WeaponSlots.at(i)->Render();
    }
}

void Character::CreatePartSlot(int type_part_id, Pnt2 offset)
{
    Pnt2* offset_new = new Pnt2(offset.x, offset.y);
    ShipParts[type_part_id] = std::make_pair(offset_new, nullptr);
}

void Character::AppendPart(ShipPart* shipPart)
{
    for (auto part : ShipParts)
    {
        if(part.first == shipPart->GetPartTypeId())
        {
            ShipPart* partTemp = part.second.second;
            if(partTemp == nullptr)
            {
                ShipParts[part.first].second = shipPart;
                Pnt2* offset = ShipParts[part.first].first;
                ShipParts[part.first].second->SetOffset(offset->x, offset->y);
                Entity::AppendPoly((Poly*) ShipParts[part.first].second);
            }
        }
    }
    shipPart->AppendToCharacter(this);
    //UpdatePartsModifiers();
    UpdateParts();
}

void Character::UpdateWeaponAim()
{
    int i;
    for(i = 0; i < WeaponSlots.size(); i++)
    {
        WeaponSlot* slot = WeaponSlots.at(i);
        if(slot->HasWeapon())
        {
            /* Todos miram no ponto do mouse.
            Vec2 orientation = slot->EquippedWeapon->GetOrientation();
            Vec2 newAim = Vec2(AimPoint->x - slot->EquippedWeapon->Offset.x, AimPoint->y - slot->EquippedWeapon->Offset.y);
            float angleDiff = orientation.GetAngleBetween(&newAim);
            */

            // O canhão central mira em direção do mouse (os demais canhões miram em paralelo)
            Vec2 orientation = slot->EquippedWeapon->GetOrientation();
            Pnt2 aimTo = slot->EquippedWeapon->GetOrientation().AsPnt();
            aimTo.ApplyVec2(*this->AimVector);
            Vec2 aimVec = aimTo.AsVec();
            float angleDiff = orientation.GetAngleBetween(&aimVec);

            Pnt2 saveOffSet = slot->EquippedWeapon->Offset;
            slot->EquippedWeapon->Offset = Pnt2(0,0);
            slot->EquippedWeapon->RotateRad(angleDiff);
            slot->EquippedWeapon->Offset = saveOffSet;
        }
    }
}

bool Character::EquipWeapon(Weapon* weapon)
{
    int i;
    for(i = 0; i < WeaponSlots.size(); i++)
    {
        WeaponSlot* slot = WeaponSlots.at(i);
        if(slot->EquippedWeapon == nullptr)
        {
            slot->SetWeapon(weapon);
            return true;
        }
    }
    return false;
}


void Character::RefreshWeaponsCooldown()
{
    int i;
    for(i = 0; i < WeaponSlots.size(); i++)
    {
        if(WeaponSlots.at(i)->HasWeapon())
            WeaponSlots.at(i)->EquippedWeapon->RefreshShotCooldown();
    }
}

void Character::UpdateParts()
{
    WeaponSlots.clear();
    int i, j;

    for (auto part :ShipParts)
    {
        ShipPart* partActual = part.second.second;
        if(partActual != nullptr)
        {
            std::vector<WeaponSlot*> wps = partActual->GetWeaponSlots();
            for(j = 0; j < wps.size(); j++)
            {
                WeaponSlots.push_back(wps.at(j));
            }
        }
    }
    UpdatePartsModifiers();
}

//void Character::ClearPartModifiers();
void Character::UpdatePartsModifiers()
{
    printf("\nUpdating modifiers...");
}

void Character::MoveDirection(Vec2* directionVector, float speed)
{
    Vec2 moveVec = (*directionVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}

bool Character::HasCollisionOnParts(float x, float y)
{
    if(Entity::CollideAt(x, y) != nullptr)
        return true;
    /*int i;
    for (i = 0; i < Parts.size(); i++)
    {
        if(Parts.at(i)->HasCollision(x, y))
            return true;
    }*/
    return false;
}

void Character::ResetControls()
{
    this->moving = 0;
    this->rotating = 0;
}

void Character::AutonomousThinking()
{
    if(Target == nullptr || Target->IsDying() || Target->IsDead())
    {
        Character* player = CollisionManager::shared_instance().GetPlayerCharacter();
        if(player == nullptr)
            return;
        //FindNewTarget
        if(!player->IsDead() && !player->IsDying())
            this->Target = player;
        else
        {
            Target = nullptr;
            this->ResetControls();
            this->SetAutonomous(false);
            return;
        }
    }
    moving = 0;

    if(GeometryAux::DistanceBetween(this->Anchor, Target->GetAnchor()) < view_range)
    {
        this->target_last_known_location->x = Target->GetAnchor()->x;
        this->target_last_known_location->y = Target->GetAnchor()->y;
        AutonomyAdjustAim();
        if(GeometryAux::DistanceBetween(this->Anchor, Target->GetAnchor()) > view_range/2)
        {
            if(GeometryAux::DistanceBetween(this->Anchor, this->target_last_known_location) > 50)
            {
                moving = 1;
            }
        }
    }

    float x1 = this->Anchor->x;
    float y1 = this->Anchor->y;
    float x2 = target_last_known_location->x - x1; // Considerando o ponto âncora como a origem
    float y2 = target_last_known_location->y - y1; // Considerando o ponto âncora como a origem
    float x3 = this->OrientationVector->x;
    float y3 = this->OrientationVector->y;

    float angleTarget = GeometryAux::AngleBetween(0, 0, x2, y2);
    float angleOrientation = GeometryAux::AngleBetween(0, 0, x3, y3);

    float angleDifference = angleTarget - angleOrientation;
    float angleDifferenceInverse = (360.0 - abs(angleDifference));

    if(abs(angleDifference) > 0 && abs(angleDifference) < this->aim_accuracy)
    {
        rotating = 0;
    }
    else
    {
        //Verifica se é melhor virar em sentido horário ou anti-horário.
        if(abs(angleDifferenceInverse) < abs(angleDifference))
        {
            if(angleDifference > 0)
                rotating = -0.75;
            else
                rotating = 0.75;
        }
        else
        {
            if(angleDifference > 0)
                rotating = 0.75;
            else
                rotating = -0.75;
        }

        if(GeometryAux::DistanceBetween(this->Anchor, Target->GetAnchor()) > view_range) return;
        //Atualizar o valor de rotação para o minimo necessário no último frame.
    }

    if(GeometryAux::DistanceBetween(this->Anchor, Target->GetAnchor()) > view_range)
    {
        rotating = 0;
        if(GeometryAux::DistanceBetween(this->Anchor, this->target_last_known_location) > 50)
        {
            moving = 1.2;
        }
        else
            moving = 0;
        return;
    }
    else
    {
        Shoot();
    }
}
