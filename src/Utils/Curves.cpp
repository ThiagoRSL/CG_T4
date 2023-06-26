#include "Curves.h"

Curve2d::Curve2d()
{
    show_control_graph = false;
    curve_resolution = 1;
    show_with_lines = false;
    this->Anchor = new Pnt2(0,0);
    firstToRenderIndex = 0;
}

BSpline::BSpline()
    :Curve2d()
{

}

Bezier::Bezier()
    :Curve2d()
{

}


void Curve2d::AddControlPoint(Pnt2* point)
{
    ControlPoints.push_back(point);
}

void Curve2d::Render()
{
    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x;
        virtualX += Offset.x;
        virtualX -= CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }

    int i;
    if(show_control_graph)
    {
        CV::color(1, 0, 0);
        for(i = 0; i < ControlPoints.size()-1; i++)
        {
            Pnt2* c0 = ControlPoints.at(i);
            Pnt2* c1 = ControlPoints.at(i+1);
            CV::line(c0->x + virtualX, c0->y + virtualY, c1->x + virtualX, c1->y + virtualY);
        }
    }
    UpdateClosestPoint();
    if(show_with_lines)
    {
        RenderWithLines();
    }
    else
    {
        RenderWithPoints();
    }
}

void Curve2d::RenderWithLines()
{
    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x;
        virtualX += Offset.x;
        virtualX -= CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }

    int i, j, save_i;
    float t, div = ControlPoints.size()*curve_resolution;
    glColor3f(Color[0], Color[1], Color[2]);

    //Encontra primeiro ponto
    glBegin(GL_LINES);
    for(i = firstToRenderIndex; i < CurvePoints.size()-1; i++)
    {
        Pnt2* point = GetCurvePoint(i);
        if(GeometryAux::DistanceBetween(point, CameraManager::shared_instance().Anchor) > RenderManager::RENDER_DISTANCE)
           break;
        Pnt2* pointPlus = GetCurvePoint(i+1);
        glVertex2d(point->x + virtualX, point->y + virtualY);
        glVertex2d(pointPlus->x + virtualX, pointPlus->y + virtualY);
    }
    for(i = firstToRenderIndex; i > 0; i--)
    {
        Pnt2* point = GetCurvePoint(i);
        if(GeometryAux::DistanceBetween(point, CameraManager::shared_instance().Anchor) > RenderManager::RENDER_DISTANCE)
           break;
        Pnt2* pointPlus = GetCurvePoint(i-1);
        glVertex2d(point->x + virtualX, point->y + virtualY);
        glVertex2d(pointPlus->x + virtualX, pointPlus->y + virtualY);
    }
    glEnd();
}

void Curve2d::UpdateClosestPoint()
{
    float distanceNext, distanceActual, distancePrevious;
    int nearestPointIndex, nearestPointNextIndex, nearestPointPreviousIndex;
    Pnt2 *nearestPoint, *nearestPointNext, *nearestPointPrevious;

    Pnt2* CameraFocus = CameraManager::shared_instance().Anchor;

    nearestPointIndex = firstToRenderIndex;
    nearestPointNextIndex = firstToRenderIndex+1;
    nearestPointPreviousIndex = firstToRenderIndex-1;
    while(true)
    {
        nearestPoint = GetCurvePoint(nearestPointIndex);
        nearestPointNext = GetCurvePoint(nearestPointNextIndex);
        nearestPointPrevious = GetCurvePoint(nearestPointPreviousIndex);

        distanceActual = GeometryAux::DistanceBetween(CameraFocus, nearestPoint);

        if(nearestPointNext != nullptr) distanceNext = GeometryAux::DistanceBetween(CameraFocus, nearestPointNext);
        else distanceNext = 2000000.0;

        if(nearestPointPrevious != nullptr) distancePrevious = GeometryAux::DistanceBetween(CameraFocus, nearestPointPrevious);
        else distancePrevious = 2000000.0;

        while(distanceActual == distanceNext)
        {
            nearestPointNextIndex+=1;
            nearestPointNext = GetCurvePoint(nearestPointNextIndex);
            if(nearestPointNext != nullptr) distanceNext = GeometryAux::DistanceBetween(CameraFocus, nearestPointNext);
            else distanceNext = 2000000.0;
        }
        while(distanceActual == distancePrevious)
        {
            nearestPointPreviousIndex-=1;
            nearestPointPrevious = GetCurvePoint(nearestPointPreviousIndex);
            if(nearestPointPrevious != nullptr) distancePrevious = GeometryAux::DistanceBetween(CameraFocus, nearestPointPrevious);
            else distancePrevious = 2000000.0;
        }
        if(distanceActual < distanceNext && distanceActual < distancePrevious)
        {
            break;
        }
        else if(distanceActual > distanceNext)
        {
            nearestPointIndex = nearestPointNextIndex;
        }
        else if(distanceActual > distancePrevious)
        {
            nearestPointIndex = nearestPointPreviousIndex;
        }
    }
    firstToRenderIndex = nearestPointIndex;
}

void Curve2d::RenderWithPoints()
{
    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x + Offset.x - CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }

    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;
    glColor3f(Color[0], Color[1], Color[2]);


    glBegin(GL_POINTS);
    for(i = firstToRenderIndex; i < CurvePoints.size(); i++)
    {
        Pnt2* point = CurvePoints.at(i);
        if(GeometryAux::DistanceBetween(point, CameraManager::shared_instance().Anchor) > RenderManager::RENDER_DISTANCE)
           break;
        glVertex2d(point->x + virtualX, point->y + virtualY);
    }
    glEnd();
}

Pnt2* Curve2d::GetCurvePoint(int i)
{
    if(i < 0 || i >= CurvePoints.size()) return nullptr;
    return CurvePoints.at(i);
}

Pnt2* Curve2d::NearPoint(Pnt2 point, float distanceMin)
{
    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x + Offset.x - CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }
    int i;
    for(i = 0; i < CurvePoints.size(); i++)
    {
        CV::color(3);
        Pnt2 p = Pnt2(CurvePoints.at(i)->x + virtualX, CurvePoints.at(i)->y + virtualY);
        if(GeometryAux::DistanceBetween(&p, &point) < distanceMin)
        {
            return new Pnt2(CurvePoints.at(i)->x + virtualX, CurvePoints.at(i)->y + virtualY);
        }
    }
    return nullptr;
}

void BSpline::GenerateCurvePoints()
{
    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;

    for(i = 0; i < ControlPoints.size()-3; i++)
    {
        for(t = 0.0; t < 1; t += 1/div)
        {
            Pnt2* p0 = ControlPoints.at(i);
            Pnt2* p1 = ControlPoints.at(i+1);
            Pnt2* p2 = ControlPoints.at(i+2);
            Pnt2* p3 = ControlPoints.at(i+3);

            float px = ((1 - t)*(1 - t)*(1 - t)/6)*p0->x + (((3*t*t*t) - 6*t*t + 4)/6)*p1->x + (((-3*t*t*t) + (3*t*t) + (3*t) + 1)/6)*p2->x + ((t*t*t)/6)*p3->x;
            float py = ((1 - t)*(1 - t)*(1 - t)/6)*p0->y + (((3*t*t*t) - 6*t*t + 4)/6)*p1->y + (((-3*t*t*t) + (3*t*t) + (3*t) + 1)/6)*p2->y + ((t*t*t)/6)*p3->y;
            Pnt2* newPoint = new Pnt2(px, py);
            CurvePoints.push_back(newPoint);
        }
    }
}

void Bezier::GenerateCurvePoints()
{
    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;

    Pnt2* p0 = ControlPoints.at(0);
    Pnt2* p1 = ControlPoints.at(1);
    Pnt2* p2 = ControlPoints.at(2);

    for(t = 0.0; t < 1; t += 1/div)
    {
        float px = p0->x*(1 - t)*(1 - t) + p1->x*(2*t*(1-t)) + p2->x*(t*t);
        float py = p0->y*(1 - t)*(1 - t) + p1->y*(2*t*(1-t)) + p2->y*(t*t);
        Pnt2* newPoint = new Pnt2(px, py);
        CurvePoints.push_back(newPoint);
    }
}


Curve2d::~Curve2d()
{
    printf("\nBom e Velho ");
    for ( auto point : ControlPoints ) delete point;
    printf("\nVasco ");
    for ( auto point : CurvePoints ) delete point;
    printf("\nDa Gaa ");
    ControlPoints.clear();
    CurvePoints.clear();
}
