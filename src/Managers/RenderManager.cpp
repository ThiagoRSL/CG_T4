#include "RenderManager.h"

RenderManager::RenderManager()
{
    this->showAnchors = false;

    this->show_crankshaft = true;
    this->show_connectionRod = true;
    this->show_piston = true;
    this->show_piston_tube = true;
    this->show_effects = true;

    this->RotAngleX = 0;
    this->RotAngleY = 0;
    this->RotAngleZ = 0;
    this->perspective_d = 15;

    this->perspective_mode = false;
}

void RenderManager::RenderAll()
{
    int i;
    for (i = 0; i < renderList.size(); i++)
    {
        renderList.at(i)->Render();
    }
}

void RenderManager::SetFirstPosition(Renderable* element)
{
    int i;
    for (i = 0; i < renderList.size(); i++)
    {
        if(renderList.at(i) == element)
        {
            renderList.erase(renderList.begin()+i);
            renderList.push_back(element);
        }
    }
}

void RenderManager::AddRenderableToList(Renderable* element)
{
    renderList.push_back(element);
}
void RenderManager::RemoveRenderableFromList(Renderable* element)
{
    int i;
    for (i = 0; i < renderList.size(); i++)
    {
        if(renderList.at(i) == element)
        {
            renderList.erase(renderList.begin()+i);
        }
    }
}

void RenderManager::ClearManager()
{
    renderList.clear();
}
