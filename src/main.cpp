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
Crankshaft* cs2;

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
          //ESPAÇO
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
      case 119:
        cs->SetAccelerating(true);
        cs2->SetAccelerating(true);
      break;
      default:
        //caso padrão
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
      case 32:
          RenderManager::shared_instance().ToggleShowAnchors();
      break;
      case 97:
        //Seta pra esquerda
        cs->SetActive(true);
        cs2->SetActive(true);
      break;
      case 100:
        //Seta pra direita
        cs->SetActive(false);
        cs2->SetActive(false);
      break;
      case 114:
      break;
      case 115:
      break;
      case 119:
        cs->SetAccelerating(false);
        cs2->SetAccelerating(false);
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

    cs = new Crankshaft(0, 0, 50, RGB);
    //Piston* piston = new Piston(cs, 200, RGB);

    cs2 = new Crankshaft(400, 0, 50, RGB);
    Piston* piston2 = new Piston(cs2, 200, RGB);
    piston2->SetAngle(45/2);
    piston2 = new Piston(cs2, 200, RGB);
    piston2->SetAngle(-45/2);


    RenderManager::shared_instance().AddRenderableToList(cs);
    RenderManager::shared_instance().AddRenderableToList(cs2);


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
