#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <stdio.h>
#include <vector>

#include "Poly.h"
#include "Entity.h"
#include "Character.h"
#include "PlayerManager.h"
#include "RenderManager.h"
#include "CharacterStatsFrameUI.h"

class UIManager : public RenderManager
{
    public:
        UIManager();
        static UIManager &shared_instance() {static UIManager uiManager; return uiManager;}

        void OpenInventory();
        void OpenCharacterStats();
        bool CheckInteraction(float x, float y);
        void Select(Poly* selectedPoly);
        void ClearManager();

        void AddCharacterStatsToRenderer(Character* character);
        void RemoveCharacterStatsToRenderer(Character* character);

        //Score
        void AddScore(int score_val);
        void UpdateScore();
        void RenderScore();
        //Stage
        void SetLevel(int stage_level);
        void UpdateStage();
        void RenderStageLabel();
        //Reset
        void RenderResetNotification();

        void RenderAll();
    private:
        //Show Score
        int score;
        std::string score_text;
        //Show Stage
        int stage_level;
        std::string stage_text;


        std::vector<CharacterStatsFrameUI*> CharacterStatsFrames;


        bool show_inventory;
        bool show_character_stats;
        Poly* SelectedPoly;

        //Open Inventory
        Entity* InventoryBackground;
        Entity* CharacterProjection;



};

#endif // UIMANAGER_H
