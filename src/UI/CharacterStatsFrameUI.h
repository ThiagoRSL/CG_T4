#ifndef CHARACTERSTATSFRAMEUI_H
#define CHARACTERSTATSFRAMEUI_H

#include "Entity.h"
#include "Character.h"


class CharacterStatsFrameUI : public Renderable
{
    public:
        CharacterStatsFrameUI(Character* character);

        void Render();

    protected:

    private:
        const float BAR_WIDTH = 250.0;
        const float BAR_HEIGHT = 20.0;
        const float BAR_SPACE = 5.0;

        Entity* HitPointsBar;
        Entity* EnergyBar;
        Vec2* hpbar_v1;
        Vec2* hpbar_v2;
        Vec2* epbar_v1;
        Vec2* epbar_v2;

        float* hit_points_max_ref;
        float* hit_points_val_ref;
        float* energy_max_ref;
        float* energy_val_ref;
        Poly* CreateBarFrame(float* Color);
        Poly* CreateBar(float* Color, Vec2* v1, Vec2* v2);
};

#endif // CHARACTERSTATSFRAMEUI_H
