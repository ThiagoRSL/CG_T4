#include "UIManager.h"

UIManager::UIManager()
{
    float RGB[3] = {0.4, 0.4, 0.4};
    InventoryBackground = new Entity(50, 50);
    InventoryBackground->SetBackgroundColor(RGB);
    Poly* background = new Poly(0, 0);
    background->AddVertex(500,0);
    background->AddVertex(500,500);
    background->AddVertex(0,500);
    InventoryBackground->AppendPoly(background);
    score = 0;
    score_text = "0";
    stage_level = 0;
    score_text = "0";
}

void UIManager::OpenInventory()
{
    if(!show_inventory)
    {
        // Main Background
        InventoryBackground->SetStatic(true);
        InventoryBackground->SetStaticOffset(50,50);
        UIManager::shared_instance().AddRenderableToList(InventoryBackground);

        // CharacterProjection
        CharacterProjection = PlayerManager::shared_instance().GetPlayerCharacter()->GetCopy();
        CharacterProjection->Resize(2);
        CharacterProjection->SetStatic(true);
        CharacterProjection->SetStaticOffset(300,300);
        UIManager::shared_instance().AddRenderableToList(CharacterProjection);


        printf("\nOpening inventory...");
        show_inventory = true;
    }
    else
    {
        UIManager::shared_instance().RemoveRenderableFromList(CharacterProjection);
        UIManager::shared_instance().RemoveRenderableFromList(InventoryBackground);
        delete CharacterProjection;
        printf("\nClosing inventory...");
        show_inventory = false;
    }
}

void UIManager::OpenCharacterStats()
{
    if(!show_character_stats)
    {
        printf("\nOpening character information...");
        show_character_stats = true;
    }
    else
    {
        printf("\nClosing character information...");
        show_character_stats = false;
    }
}

bool UIManager::CheckInteraction(float x, float y)
{
    if(show_inventory)
    {
        Poly* part = CharacterProjection->CollideAt(x, y);
        Select(part);
        return true;
    }
    return false;
}

void UIManager::Select(Poly* selectedPoly)
{
    if(SelectedPoly != nullptr)
        SelectedPoly->SetShowBorder(false);

    this->SelectedPoly = selectedPoly;

    if(SelectedPoly != nullptr)
    {
        CharacterProjection->SetFirstPosition(SelectedPoly);
        SelectedPoly->SetShowBorder(true);
    }
}

void UIManager::AddCharacterStatsToRenderer(Character* character)
{
    CharacterStatsFrameUI* charStatsFrame = new CharacterStatsFrameUI(character);
    CharacterStatsFrames.push_back(charStatsFrame);
}
void UIManager::ClearManager()
{
    for(auto elem: CharacterStatsFrames) delete elem;
    CharacterStatsFrames.clear();
}
void UIManager::RemoveCharacterStatsToRenderer(Character* character)
{
    return;
}

void UIManager::AddScore(int score_val)
{
    score += score_val;
    UpdateScore();
}
void UIManager::UpdateScore()
{
    score_text = std::to_string(score);
}
void UIManager::RenderScore()
{
    float position = glutGet(GLUT_SCREEN_WIDTH) - (75);
    float position_val = glutGet(GLUT_SCREEN_WIDTH) - (70 + (score_text.size()*5));

    CV::color(1,1,1);
    CV::text(position - 20, 50, "SCORE");
    CV::text(position_val, 70, score_text.c_str());
}

void UIManager::SetLevel(int stage_level)
{
    this->stage_level = stage_level;
    UpdateStage();
}
void UIManager::UpdateStage()
{
    stage_text = "LEVEL " + std::to_string(stage_level);
}
void UIManager::RenderStageLabel()
{
    float position = glutGet(GLUT_SCREEN_WIDTH)/2;

    CV::color(1,1,1);
    CV::text(position - 30, 50, stage_text.c_str());
}
void UIManager::RenderResetNotification()
{
    float posX = glutGet(GLUT_SCREEN_WIDTH)/2;
    float posY = glutGet(GLUT_SCREEN_HEIGHT)/2;

    CV::color(1,1,1);
    CV::text(posX - 160, posY, "Game is Over, press R to Restart.");
}



void UIManager::RenderAll()
{
    RenderManager::RenderAll();
    RenderScore();
    RenderStageLabel();
    if(PlayerManager::shared_instance().IsGameOver())
        RenderResetNotification();

    int i;
    for(i = 0; i < CharacterStatsFrames.size();i++)
    {
        CharacterStatsFrames.at(i)->Render();
    }
}
