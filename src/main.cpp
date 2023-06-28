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

const int CONTROL_POINTS = 50;
const int CONTROL_POINTS_INCREMENT = 0;

std::set<int> PressedKeys;
Entity* vb;

void render()
{
    //CV::clear(0,0,0);

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
        //R
      break;
      case 115:
        //Seta pra baixo
      break;
      case 119:
        //Seta pra cima
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
        vb->Rotate(-15);
      break;
      case 100:
        //Seta pra direita
        vb->Rotate(15);
      break;
      case 114:
        //R
      break;
      case 115:
        //Seta pra baixo
      break;
      case 119:
        //Seta pra cima
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

    Poly* p1 = new Poly(0, 0, RGB);
    p1->SetOffset(40, 0);

    float radius = 50.0;
    float angInit = -(PI/2);
    float angMax = (PI/2);
    float angStep = PI/180;
    float ang;

    //Cria Virabrequim
    p1->AddVertex(-90, -20);
    p1->AddVertex(-40, -30);
    for(ang = angInit; ang <= angMax+angStep; ang = ang + angStep)
    {
        p1->AddVertex(-(2*radius/5) + radius * cos(ang), radius * sin(ang));
    }
    p1->AddVertex(-40, 30);
    p1->AddVertex(-90, 20);
    //Termina Vibraquim

    //Cria Biela
    Poly* p2 = new Poly(0, 0, RGB);
    p2->SetOffset(-40, 0);
    Vec2* bielaPonta = new Vec2(40, 200);
    p2->AddVertex(bielaPonta);
    p2->AddVertex(-10, 0);
    p2->AddVertex(10, 0);
    p2->AddVertex(10, 200);
    p2->AddVertex(-10, 200);
    //Termina Biela



    vb = new Entity(800, 600, RGB);
    vb->AppendPoly(p1);
    vb->AppendPoly(p2);

    RenderManager::shared_instance().AddRenderableToList(vb);


    CV::init("Motor de Moto (Harley Davidson)");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    Pnt2* globanchor = vb->GetAnchor();
    CameraManager::shared_instance().SetCameraAnchor(globanchor);
    CameraManager::shared_instance().SetCameraOffset(Pnt2((float) -screenWidth/2, (float) -screenHeight/2));

    glutInitWindowSize (screenWidth, screenHeight);
    glutInitWindowPosition (0, 0);
    glutFullScreen();

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
