#include "CharacterStatsFrameUI.h"

CharacterStatsFrameUI::CharacterStatsFrameUI(Character* character)
{
    hit_points_max_ref = character->GetHitPointsMaxRef();
    hit_points_val_ref = character->GetHitPointsRef();
    energy_max_ref = character->GetEnergyMaxRef();
    energy_val_ref = character->GetEnergyRef();

    float hit_points_bar_color[3] = {0.2,0.7,0.2};
    float energy_bar_color[3] = {0.2,0.2,0.7};

    this->HitPointsBar = new Entity(0,0, hit_points_bar_color);
    this->EnergyBar = new Entity(0,0, energy_bar_color);

    HitPointsBar->SetBackgroundColor(hit_points_bar_color);
    EnergyBar->SetBackgroundColor(energy_bar_color);

    hpbar_v1 = new Vec2(BAR_WIDTH, 0);
    hpbar_v2 = new Vec2(BAR_WIDTH, BAR_HEIGHT);
    epbar_v1 = new Vec2(BAR_WIDTH, 0);
    epbar_v2 = new Vec2(BAR_WIDTH, BAR_HEIGHT);

    HitPointsBar->AppendPoly(CreateBar(hit_points_bar_color, hpbar_v1, hpbar_v2));
    EnergyBar->AppendPoly(CreateBar(energy_bar_color, epbar_v1, epbar_v2));

    this->HitPointsBar->SetStatic(true);
    this->EnergyBar->SetStatic(true);

    this->HitPointsBar->SetStaticOffset(50, BAR_HEIGHT);
    this->EnergyBar->SetStaticOffset(50, 2*BAR_HEIGHT + BAR_SPACE);
}

Poly* CharacterStatsFrameUI::CreateBarFrame(float* Color)
{
    Poly* barFrame = new Poly(0,0);
    barFrame->AddVertex(0,0);
    barFrame->AddVertex(300,0);
    barFrame->AddVertex(300, BAR_HEIGHT);
    barFrame->AddVertex(0, BAR_HEIGHT);
    barFrame->SetBackgroundColor(Color);
    return barFrame;
}

Poly* CharacterStatsFrameUI::CreateBar(float* Color, Vec2* v1, Vec2* v2)
{
    Poly* barFrame = new Poly(0,0);
    barFrame->AddVertex(0,0);
    barFrame->AddVertex(v1);
    barFrame->AddVertex(v2);
    barFrame->AddVertex(0,BAR_HEIGHT);
    barFrame->SetBackgroundColor(Color);
    return barFrame;
}

void CharacterStatsFrameUI::Render()
{
    float hpvx = (*hit_points_val_ref/ (*hit_points_max_ref)) * BAR_WIDTH;
    float epvx = (*energy_val_ref/ (*energy_max_ref)) * BAR_WIDTH;
    hpbar_v1->x = hpvx;
    hpbar_v2->x = hpvx;
    epbar_v1->x = epvx;
    epbar_v2->x = epvx;
    HitPointsBar->Render();
    EnergyBar->Render();
}
