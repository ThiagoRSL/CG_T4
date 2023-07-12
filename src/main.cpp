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
#include "Managers/FPSManager.h"
#include "Managers/UIManager.h"
#include "Utils/Vec2.h"
#include "Entities/Poly.h"
#include "Entities/Entity.h"
#include "Entities/Character.h"
#include "Utils/Curves.h"
#include "Crankshaft.h"
#include "Piston.h"

const int CONTROL_POINTS = 50;
const int CONTROL_POINTS_INCREMENT = 0;

std::set<int> PressedKeys;
Crankshaft* cs;
float angle_between_pistons = 60;
Piston *piston1, *piston2;

void render()
{
    CV::clear(1,1,1);

    //glBegin(GL_LINES);
    FPSManager::shared_instance().UpdateFrames();
    CameraManager::shared_instance().UpdateCameraOffset();
    RenderManager::shared_instance().RenderAll();
    //UIManager::shared_instance().RenderAll();
    //if(CollisionManager::shared_instance().ArrivedAtStation())  SetupStage();
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
      case 32:
        cs->SetAccelerating(true);
      break;
      case 97:
        //Seta pra esquerda
      break;
      case 100:
        //Seta pra direita
      break;
      case 114:
      break;
      case 115:
      break;
      default:
        //caso padrão
        break;
    }
}

void UpdateAngle()
{
    if(angle_between_pistons > 110)
        angle_between_pistons = 110;
    else if(angle_between_pistons < 60)
        angle_between_pistons = 60;
    piston1->SetAngle(-angle_between_pistons/2);
    piston2->SetAngle(angle_between_pistons/2);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    //printf("\nLiberou: %d" , key);
    if(PressedKeys.find(key) != PressedKeys.end())
        PressedKeys.erase(PressedKeys.find(key));
    switch(key)
    {
      case 32:
          cs->SetAccelerating(false);
      break;
      case 49://1
        RenderManager::shared_instance().show_crankshaft = !RenderManager::shared_instance().show_crankshaft;
      break;
      case 50://2
        RenderManager::shared_instance().show_connectionRod = !RenderManager::shared_instance().show_connectionRod;
      break;
      case 51://3
        RenderManager::shared_instance().show_piston = !RenderManager::shared_instance().show_piston;
      break;
      case 52://4
        RenderManager::shared_instance().show_piston_tube = !RenderManager::shared_instance().show_piston_tube;
        RenderManager::shared_instance().show_effects = !RenderManager::shared_instance().show_effects;
      break;
      case 200:
        angle_between_pistons += 1;
        UpdateAngle();
      break;
      case 202:
        angle_between_pistons -= 1;
        UpdateAngle();
      break;
      case 119:
          RenderManager::shared_instance().ToggleShowAnchors();
      break;
      default:
        //caso padrão
        break;
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    MouseManager::shared_instance().PosX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    MouseManager::shared_instance().PosY = y;

    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

    if(wheel == 0)
    {
        if(direction == 1)
        {
            angle_between_pistons += 1;
        }
        else if(direction == -1)
        {
            angle_between_pistons -= 1;
        }

        UpdateAngle();
    }
    if(UIManager::shared_instance().CheckInteraction(x, y))
    {
        return;
    }
    if(button == 0 && state == 0)
    {
        //click botão esquerdo
    }

}

int main(void)
{
    float RGB[3] = {0.0,0.75,0.75};
    float RGB2[3] = {0.75,0.0,0.75};
    float RGB3[3] = {0.75, 0.75, 0.0};
    float RGB4[3] = {0.75, 0.35, 0.35};
    float RGB5[3] = {0.85, 0.85, 0.85};
    float csColor[3] = {0.3,0.3,0.3};

    RenderManager::shared_instance().show_crankshaft = true;
    RenderManager::shared_instance().show_connectionRod = true;
    RenderManager::shared_instance().show_piston = true;
    RenderManager::shared_instance().show_piston_tube = true;
    RenderManager::shared_instance().show_effects = true;

    //cs = new Crankshaft(0, 0, 50, RGB);
    //Piston* piston = new Piston(cs, 200, RGB);

    cs = new Crankshaft(400, 0, 50, RGB);
    cs->SetBackgroundColor(csColor);
    piston1 = new Piston(cs, 150, RGB);
    piston1->SetAngle(-angle_between_pistons/2);
    piston2 = new Piston(cs, 150, RGB);
    piston2->SetAngle(angle_between_pistons/2);

    cs->SetActive(true);

    RenderManager::shared_instance().AddRenderableToList(cs);


    CV::init("Motor de Moto (Harley Davidson)");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    Pnt2* globanchor = cs->GetAnchor();
    CameraManager::shared_instance().SetCameraAnchor(globanchor);
    CameraManager::shared_instance().SetCameraOffset(Pnt2((float) -screenWidth/2, (float) -screenHeight/2));

    glutInitWindowSize (screenWidth, screenHeight);
    glutInitWindowPosition (0, 0);
    glutFullScreen();

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
