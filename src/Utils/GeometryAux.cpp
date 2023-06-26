#include "GeometryAux.h"

//1 -> horario | -1 -> anti-horario | 0 -> colinear
int GeometryAux::GetOrientation(float x0, float y0, float x1, float y1, float x2, float y2)
{
    float r1 = (y1 - y0)*(x2 - x1); // p0 e p1
    float r2 = (y2 - y1)*(x1 - x0); // p1 e p2

    //colinear
    if(r1 == r2) return 0;

    //sentido horario
    if(r1 > r2)
    {
        return 1;
    }

    //sentido anti-horario
    return -1;
}
bool GeometryAux::Intercept(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
    if(GetOrientation(x0,y0,x1,y1,x2,y2) != GetOrientation(x0,y0,x1,y1,x3,y3))
    {
        if(GetOrientation(x2,y2,x3,y3,x0,y0) != GetOrientation(x2,y2,x3,y3,x1,y1))
        {
            return true;
        }
    }
    return false;
}
float GeometryAux::DistanceBetween(float x0, float y0, float x1, float y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float diff = ((dx*dx) + (dy*dy));
    if(diff < 0) diff = diff*-1;
    return sqrtf(diff);
}
float GeometryAux::DistanceBetween(Pnt2* p1, Pnt2* p2)
{
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    float diff = ((dx*dx) + (dy*dy));
    if(diff < 0) diff = diff*-1;
    return sqrtf(diff);
}
float GeometryAux::AngleBetween(float x1, float y1, float x2, float y2)
{
    return atan2(y2 - y1, x2 - x1) * (180 / M_PI);
}
float GeometryAux::AngleBetweenFull(float x1, float y1, float x2, float y2)
{
    return atan2(y2 - y1, x2 - x1) * (180 / M_PI) + 180;
}
float GeometryAux::GetDiff(float c0, float c1)
{
    return c0-c1;
}
float DegToRad(float deg)
{
    return (fmod(deg, 360) * M_PI) /180;
}

