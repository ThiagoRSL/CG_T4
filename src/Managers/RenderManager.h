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
    public:
        static const int RENDER_DISTANCE = 2500;
        static RenderManager &shared_instance() {static RenderManager renderManager; return renderManager;}
        RenderManager();
        void AddRenderableToList(Renderable* element);
        void RemoveRenderableFromList(Renderable* element);
        void SetFirstPosition(Renderable* element);
        virtual void ClearManager();
        //AddToRenderQueue(Renderizable element, int priority_level);
        virtual void RenderAll();

    protected:

    private:
        std::vector<Renderable*> renderList;


};

#endif // RENDERMANAGER_H

