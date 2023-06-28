#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "Managers/MouseManager.h"
#include "Entities/Abstract/Renderable.h"
#include "Utils/GeometryAux.h"

typedef void (*callback_function)(void);

class RenderManager
{
    private:
        bool showAnchors;
        std::vector<Renderable*> renderList;

    public:
        static const int RENDER_DISTANCE = 2500;
        static RenderManager &shared_instance() {static RenderManager renderManager; return renderManager;}
        RenderManager();
        void AddRenderableToList(Renderable* element);
        void RemoveRenderableFromList(Renderable* element);
        void SetFirstPosition(Renderable* element);
        void ToggleShowAnchors() {this->showAnchors = !this->showAnchors;}
        bool GetShowAnchors() {return this->showAnchors;}
        virtual void ClearManager();
        virtual void RenderAll();
        //AddToRenderQueue(Renderizable element, int priority_level);

    protected:


};

#endif // RENDERMANAGER_H

