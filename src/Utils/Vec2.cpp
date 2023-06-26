#include "Vec2.h"
#include "GeometryAux.h"

// Construtores
Vec2::Vec2()
{
    this->x = 0;
    this->y = 0;
    this->Anchor = nullptr;
}

Vec2::Vec2(float v[2])
{
    this->x = v[0];
    this->y = v[1];
    this->Anchor = nullptr;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
    this->Anchor = nullptr;
}

Vec2::Vec2(float x, float y, Pnt2* anchor)
{
    this->x = x;
    this->y = y;
    this->Anchor = new Pnt2(anchor->x, anchor->y);
}


// Getters
float Vec2::GetAngleBetween(Vec2* v)
{
    float det = Determinant(v);
    float arc_tan = atan2(det, DotProduct(v));
    if(isnan(arc_tan))
        return 0;
    else
        return atan2(det, DotProduct(v));
}
float Vec2::DotProduct(Vec2* v)
{
    return (this->x * v->x) + (this->y * v->y);
}
float Vec2::Determinant(Vec2* v)
{
    return x*v->y - y*v->x;
}
float Vec2::GetNorm()
{
    return sqrtf((x*x) + (y*y));
}

//Operações no próprio vetor
void Vec2::Mult(float scalar)
{
    this->x = this->x * scalar;
    this->y = this->y * scalar;
}

void Vec2::Sum(float scalar)
{
    this->x = this->x + scalar;
    this->y = this->y + scalar;
}

void Vec2::Sum(Vec2* v2)
{
    this->x = this->x + v2->x;
    this->y = this->y + v2->y;
}

void Vec2::Sum(Vec2& v2)
{
    this->x = this->x + (v2.x);
    this->y = this->y + (v2.y);
}

void Vec2::Sub(Vec2* v2)
{
    this->x = this->x - v2->x;
    this->y = this->y - v2->y;
}

void Vec2::Normalize()
{
    float norm = this->GetNorm();
    this->x = this->x / norm;
    this->y = this->y / norm;
}

void Vec2::RotateDegrees(float degrees)
{
    this->RotateRadians(degrees * (PI / 180));
}

void Vec2::RotateRadians(float radians)
{
    float aux_x = this->x;
    float aux_y = this->y;
    this->x = (aux_x * cosf(radians)) - (aux_y * sinf(radians));
    this->y = (aux_x * sinf(radians)) + (aux_y * cosf(radians));
}

Pnt2 Vec2::AsPnt()
{
    return Pnt2(this->x, this->y);
}

float Vec2::RelativeX()
{
    return Anchor->y + y;
}

float Vec2::RelativeY()
{
    return Anchor->y + y;
}

Vec2* Vec2::GetCopy()
{
    Vec2* n = new Vec2(x, y);
    n->SetAnchor(Anchor->x, Anchor->y);
    return n;
}

void Vec2::Render()
{
    CV::color(2);
    CV::line(this->Anchor->x, this->Anchor->y, this->RelativeX(), this->RelativeY());
}

