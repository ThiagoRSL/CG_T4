/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>
#include <iterator>
#include <cstdlib>
#include <iostream>

#include "gl_canvas2d.h"
#include "Managers/FileManager.h"
#include "Managers/MouseManager.h"
#include "Managers/RenderManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/FPSManager.h"
#include "Managers/PlayerManager.h"
#include "Managers/UIManager.h"
#include "Builder/CharacterBuilder.h"
#include "Utils/Vec2.h"
#include "Entities/Poly.h"
#include "Entities/Entity.h"
#include "Entities/Character/Character.h"
#include "Entities/Character/PlayerCharacter.h"
#include "Utils/Curves.h"

const int CONTROL_POINTS = 50;
const int CONTROL_POINTS_INCREMENT = 0;

void GenerateWalls();
void GeneratePlayer();
void CreateEnemy(float x, float y);
void SetupStage();
void ResetGame();

Character* player_character;
Character* enemy_character;
int stage_level;

Bezier* BottomWall;
BSpline* LeftWall;
BSpline* RightWall;

std::vector<Pnt2> EnemySpawnPoints;

std::set<int> PressedKeys;

void render()
{
    CV::clear(0,0,0);

    //glBegin(GL_LINES);
    FPSManager::shared_instance().UpdateFrames();
    CameraManager::shared_instance().UpdateCameraOffset();
    CollisionManager::shared_instance().CheckCollisions();
    PlayerManager::shared_instance().CheckInteraction();
    RenderManager::shared_instance().RenderAll();
    UIManager::shared_instance().RenderAll();
    if(CollisionManager::shared_instance().ArrivedAtStation())  SetupStage();
}



void keyboard(int key)
{
    printf("\nTecla: %d" , key);

    if(PressedKeys.find(key) != PressedKeys.end())
    {
        return;
    }
    PressedKeys.insert(key);

    switch(key)
    {
      //seta para a esquerda
      case 8:
          SetupStage(); // < ------ PARA DEBUGAR DESCOMENTE ESTA LINHA
      break;
      case 120:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->ActivateSpecial(2);
      break;
      case 32:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->ActivateSpecial(1);
      break;
      case 97:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->SetRotating(-1);
      break;
      case 100:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->SetRotating(1);
      break;
      case 114:
        if(PlayerManager::shared_instance().IsGameOver())
            ResetGame();
      break;
      case 115:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->SetMoving(-1);
      break;
      case 119:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->SetMoving(1.5);
        //player_character->SetMoving(4); <- Usar isso aqui pra debuggar
      break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    //printf("\nLiberou: %d" , key);
    if(PressedKeys.find(key) != PressedKeys.end())
        PressedKeys.erase(PressedKeys.find(key));
    switch(key)
    {
      case 27:
         //exit(0);
      break;
        //InventoryManager::shared_instance().OpenMenu();
      case 107:
        //ClearAllFigures();
        break;
      case 108:
        //LoadSave();
        break;
      case 109:
        //FileManager::shared_instance().SaveData(SavedFilePath, FigureManager::shared_instance().GetFiguresAsString(), FigureManager::shared_instance().CountFigures());
        break;
      //seta para a esquerda
      case 98:
        printf("\nB pressionado, loja abertas.");
        break;
      case 99:
        UIManager::shared_instance().OpenCharacterStats();
        break;
      case 105:
        UIManager::shared_instance().OpenInventory();
        break;
      case 97:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;

        if(PressedKeys.find(100) != PressedKeys.end())
            player_character->SetRotating(1);
        else
            player_character->SetRotating(0);
      break;
      case 100:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;

        if(PressedKeys.find(97) != PressedKeys.end())
            player_character->SetRotating(-1);
        else
            player_character->SetRotating(0);
      break;
      case 115:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;

        if(PressedKeys.find(119) != PressedKeys.end())
            player_character->SetMoving(-0.5);
        else
            player_character->SetMoving(0);
      break;
      case 119:
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;

        if(PressedKeys.find(115) != PressedKeys.end())
            player_character->SetMoving(1);
        else
            player_character->SetMoving(0);
      break;
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    MouseManager::shared_instance().PosX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    MouseManager::shared_instance().PosY = y;

    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

    if(UIManager::shared_instance().CheckInteraction(x, y))
    {
        return;
    }
    if(button == 0 && state == 0)
    {
        if(player_character == nullptr || player_character->IsDead() || player_character->IsDying())
            return;
        player_character->Shoot();
    }

}

void GenerateWalls()
{
    float RGB3[3] = {0.75, 0.75, 0.0};
    //Wall Close
    BottomWall = new Bezier();
    BottomWall->SetColor(RGB3);
    BottomWall->SetShowWithLines(true);
    BottomWall->SetCurveResolution(100);

    //LeftWall
    LeftWall = new BSpline();
    LeftWall->SetColor(RGB3);
    LeftWall->SetShowWithLines(true);
    //left->SetShowControlGraph(true);
    //left->SetCurveResolution(1);

    //RightWall
    RightWall = new BSpline();
    RightWall->SetColor(RGB3);
    RightWall->SetShowWithLines(true);
    //right->SetShowControlGraph(true);
    //right->SetCurveResolution(1);x

    //Gera os pontos de controle das curvas laterais
    Pnt2* p = new Pnt2(100,100);
    Pnt2* pn;
    Pnt2* pnx;
    int controlPoints = CONTROL_POINTS + (stage_level*CONTROL_POINTS_INCREMENT);
    int i;
    for (i = 0; i < controlPoints; i++)
    {
        pn = new Pnt2((std::rand() % 150), p->y - (std::rand() % 125) - 175);
        LeftWall->AddControlPoint(pn);
        pnx = new Pnt2(1200 + (std::rand() % 250), pn->y - (std::rand() % 50));
        RightWall->AddControlPoint(pnx);
        p = pn;


        if(i+5 < controlPoints)
        {
            EnemySpawnPoints.push_back(Pnt2((pn->x + pnx->x)/2, (pn->y + pnx->y)/2));
        }

    }

    LeftWall->GenerateCurvePoints();
    RightWall->GenerateCurvePoints();
    Pnt2* firstRightPoint = RightWall->GetFirstCurvePoint();
    Pnt2* firstLeftPoint = LeftWall->GetFirstCurvePoint();

    BottomWall->AddControlPoint(new Pnt2(firstRightPoint->x, firstRightPoint->y));
    BottomWall->AddControlPoint(new Pnt2((firstRightPoint->x + firstLeftPoint->x)/2, firstLeftPoint->y + 500));
    BottomWall->AddControlPoint(new Pnt2(firstLeftPoint->x, firstLeftPoint->y));
    BottomWall->GenerateCurvePoints();

    Pnt2* lastRightPoint = RightWall->GetLastCurvePoint();
    Pnt2* lastLeftPoint = LeftWall->GetLastCurvePoint();
    Poly* Station = new Poly(lastLeftPoint->x, lastLeftPoint->y);
    Station->AddVertex(0,0);
    Station->AddVertex(lastRightPoint->x-lastLeftPoint->x, 0);
    Station->AddVertex(lastRightPoint->x-lastLeftPoint->x, -1000);
    Station->AddVertex(0, -1000);
    Station->SetBackgroundColor(RGB3);


    CollisionManager::shared_instance().ClearManager();
    RenderManager::shared_instance().ClearManager();
    CollisionManager::shared_instance().addWall(LeftWall);
    CollisionManager::shared_instance().addWall(RightWall);
    CollisionManager::shared_instance().addWall(BottomWall);
    CollisionManager::shared_instance().SetStation(Station);
    RenderManager::shared_instance().AddRenderableToList(LeftWall);
    RenderManager::shared_instance().AddRenderableToList(RightWall);
    RenderManager::shared_instance().AddRenderableToList(BottomWall);
    RenderManager::shared_instance().AddRenderableToList(Station);
}

void GeneratePlayer()
{
    float RGB[3] = {0.0,0.75,0.75};
    float RGB2[3] = {0.75,0.0,0.75};
    float RGB3[3] = {0.75, 0.75, 0.0};
    float RGB4[3] = {0.75, 0.35, 0.35};
    float RGB5[3] = {0.85, 0.85, 0.85};

    if(stage_level >= 10)
    {
        player_character = (PlayerCharacter*) CharacterBuilder::BuildShip(200, 700, RGB, 2);
        player_character->SetMaxHitPoints(200);
        player_character->SetMaxEnergy(150);
    }
    else
    {
        player_character = (PlayerCharacter*) CharacterBuilder::BuildShip(200, 700, RGB, 1);
        player_character->SetMaxHitPoints(100);
        player_character->SetMaxEnergy(100);
    }


    Weapon* w1 = new Weapon();
    w1->SetBackgroundColor(RGB3);
    Weapon* w2 = new Weapon();
    w2->SetBackgroundColor(RGB2);
    Weapon* w3 = new Weapon();
    w3->SetBackgroundColor(RGB2);
    w1->SetShotColor(RGB4);
    w2->SetShotColor(RGB5);
    w3->SetShotColor(RGB5);
    player_character->EquipWeapon(w1);
    player_character->EquipWeapon(w2);
    player_character->EquipWeapon(w3);
    PlayerManager::shared_instance().SetPlayerCharacter(player_character);
    RenderManager::shared_instance().AddRenderableToList(player_character);
    CollisionManager::shared_instance().SetPlayerCharacter(player_character);
    CollisionManager::shared_instance().AddNPC(player_character);
    UIManager::shared_instance().AddCharacterStatsToRenderer(player_character);
    player_character->TeleportTo((RightWall->GetFirstCurvePoint()->x + LeftWall->GetFirstCurvePoint()->x)/2, LeftWall->GetFirstCurvePoint()->y);

    CameraManager::shared_instance().SetCameraAnchor(player_character->GetAnchor());
}

void CreateEnemy(float x, float y, bool mustBeBig=false)
{
    float RGB[3] = {0.0,0.75,0.75};
    float RGB2[3] = {0.75,0.0,0.75};
    float RGB3[3] = {0.75, 0.75, 0.0};
    float RGB4[3] = {0.75, 0.35, 0.35};
    float RGB5[3] = {0.85, 0.85, 0.85};

    int randomNum = rand() % 100 + 1 + stage_level*5;

    Weapon* w1 = new Weapon();
    w1->SetBackgroundColor(RGB4);
    w1->SetShotColor(RGB5);
    Weapon* w2 = new Weapon();
    w2->SetBackgroundColor(RGB4);
    w2->SetShotColor(RGB5);
    Weapon* w3 = new Weapon();
    w3->SetBackgroundColor(RGB4);
    w3->SetShotColor(RGB5);

    if(randomNum >= 100 || mustBeBig)
    {
        enemy_character = CharacterBuilder::BuildShip(x, y+1, RGB2, 2);
        enemy_character->SetMaxHitPoints(20 + stage_level * 10);
        enemy_character->EquipWeapon(w1);
        enemy_character->EquipWeapon(w2);
        enemy_character->EquipWeapon(w3);
        enemy_character->SetScoreValue(2000 + stage_level * 500);
    }
    else
    {
        enemy_character = CharacterBuilder::BuildShip(x, y+1, RGB2, 1);
        enemy_character->SetMaxHitPoints(stage_level * 5);
        enemy_character->EquipWeapon(w1);
        enemy_character->SetScoreValue(500 + stage_level * 100);
        delete w2;
        delete w3;
    }
    enemy_character->Rotate(180);
    if(stage_level > 20)
    {
        enemy_character->SetMovementSpeed(1000);
        enemy_character->SetViewRange(1000);
    }
    else
    {
        enemy_character->SetMovementSpeed(500 + (25 * stage_level));
        enemy_character->SetViewRange(500 + (25 * stage_level));
    }
    enemy_character->SetAutonomous(true);
    RenderManager::shared_instance().AddRenderableToList(enemy_character);
    CollisionManager::shared_instance().AddNPC(enemy_character);
    enemy_character->TeleportTo(x, y);
}

void GenerateEnemies()
{
    int i;
    for(i = 5; i < EnemySpawnPoints.size(); i++)
    {
        Pnt2* spawnPoint = &EnemySpawnPoints.at(i);
        int random = (std::rand() % 20) + stage_level;
        if(random >= 0 && random < 15)
        {
            CreateEnemy(spawnPoint->x + 200, spawnPoint->y, false);
            CreateEnemy(spawnPoint->x, spawnPoint->y, false);
            CreateEnemy(spawnPoint->x - 200, spawnPoint->y, false);
            i += 4;
        }
        else if(random >= 15 && random < 25)
        {
            CreateEnemy(spawnPoint->x + 200, spawnPoint->y, false);
            CreateEnemy(spawnPoint->x, spawnPoint->y, true);
            CreateEnemy(spawnPoint->x - 200, spawnPoint->y, false);
            i += 6;
        }
        else if(random >= 25 && random < 50)
        {
            CreateEnemy(spawnPoint->x + 250, spawnPoint->y, true);
            CreateEnemy(spawnPoint->x, spawnPoint->y, true);
            CreateEnemy(spawnPoint->x - 250, spawnPoint->y, true);
            i += 6;
        }
        else if(random >= 50)
        {
            CreateEnemy(spawnPoint->x + 200, spawnPoint->y, false);
            CreateEnemy(spawnPoint->x + 200, spawnPoint->y + 100, false);
            CreateEnemy(spawnPoint->x, spawnPoint->y, true);
            CreateEnemy(spawnPoint->x - 200, spawnPoint->y + 100, false);
            CreateEnemy(spawnPoint->x - 200, spawnPoint->y, false);
            i += 6;
        }
    }
}

void ResetGame()
{
    stage_level = 0;
    UIManager::shared_instance().SetLevel(stage_level);
    SetupStage();
}

void SetupStage()
{
    UIManager::shared_instance().ClearManager();

    stage_level += 1;
    UIManager::shared_instance().SetLevel(stage_level);

    EnemySpawnPoints.clear();
    GenerateWalls();
    GeneratePlayer();
    GenerateEnemies();
}

int main(void)
{
    float RGB[3] = {0.0,0.75,0.75};
    float RGB2[3] = {0.75,0.0,0.75};
    float RGB3[3] = {0.75, 0.75, 0.0};
    float RGB4[3] = {0.75, 0.35, 0.35};
    float RGB5[3] = {0.85, 0.85, 0.85};


    stage_level = 0;
    SetupStage();

    CV::init("Space Extinction");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    CameraManager::shared_instance().SetCameraOffset(Pnt2((float) -screenWidth/2, (float) -screenHeight/2));

    glutInitWindowSize (screenWidth, screenHeight);
    glutInitWindowPosition (0, 0);
    glutFullScreen();

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
