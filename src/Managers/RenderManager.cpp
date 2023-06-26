#include "RenderManager.h"

RenderManager::RenderManager()
{

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
