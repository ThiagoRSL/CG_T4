#include "CharacterBuilder.h"


CharacterBuilder::CharacterBuilder()
{
    //ctor
}

Character* CharacterBuilder::BuildShip(float x, float y, float* RGB, int ship_type_code)
{
    switch(ship_type_code)
    {
        case 1:
            return CreateSmallShip(x, y, RGB);
        case 2:
            return CreateMediumShip(x, y, RGB);
        case 3:
            break;
        case 4:
            break;

    }
}

Character* CharacterBuilder::CreateSmallShip(float x, float y, float* RGB)
{
    Character* character = new Character(x, y, RGB);
    character->CreatePartSlot(ShipPart::SHIP_BODY_PART_TYPE_ID, Pnt2(0,0));
    ShipPart* body = CreateChassis(x, y, RGB);
    body->AddWeaponSlot(Pnt2(0,0));
    character->AppendPart(body);

    return character;
}

Character* CharacterBuilder::CreateMediumShip(float x, float y, float* RGB)
{
    Character* character = new Character(x, y, RGB);
    character->CreatePartSlot(ShipPart::SHIP_BODY_PART_TYPE_ID, Pnt2(0, 0));
    character->CreatePartSlot(ShipPart::LEFT_WING_PART_TYPE_ID, Pnt2(-30, 5));
    character->CreatePartSlot(ShipPart::RIGHT_WING_PART_TYPE_ID, Pnt2(30, 5));
    //character->CreateWeaponSlot(Pnt2(0,0));

    ShipPart* body = CreateChassis(x, y, RGB);
    character->AppendPart(body);
    body->AddWeaponSlot(Pnt2(0,0));

    ShipPart* rightWing = CreateRightWing(x, y, RGB);
    rightWing->AddWeaponSlot(Pnt2(0,0));
    character->AppendPart(rightWing);

    ShipPart* leftWing = CreateLeftWing(x, y, RGB);
    leftWing->AddWeaponSlot(Pnt2(0,0));
    character->AppendPart(leftWing);


    return character;
}

ShipPart* CharacterBuilder::CreateChassis(float x, float y,float* RGB)
{
    ShipPart* part = new ShipPart(x, y, RGB);
    part->SetPartTypeId(ShipPart::SHIP_BODY_PART_TYPE_ID);
    part->AddVertex(-20,-25);
    part->AddVertex(-10,-40);
    part->AddVertex(10,-40);
    part->AddVertex(20,-25);
    part->AddVertex(20,25);
    part->AddVertex(-20,25);
    return part;
}

ShipPart* CharacterBuilder::CreateLeftWing(float x, float y, float* RGB)
{
    ShipPart* leftWing = new ShipPart(x, y, RGB);
    leftWing->SetPartTypeId(ShipPart::LEFT_WING_PART_TYPE_ID);
    leftWing->AddVertex(10, -25);
    leftWing->AddVertex(-10, -10);
    leftWing->AddVertex(-10, 30);
    leftWing->AddVertex(10, 30);
    return leftWing;
}

ShipPart* CharacterBuilder::CreateRightWing(float x, float y,float* RGB)
{
    ShipPart* rightWing = new ShipPart(x, y, RGB);
    rightWing->SetPartTypeId(ShipPart::RIGHT_WING_PART_TYPE_ID);
    rightWing->AddVertex(10, -10);
    rightWing->AddVertex(-10, -25);
    rightWing->AddVertex(-10, 30);
    rightWing->AddVertex(10, 30);
    return rightWing;
}
