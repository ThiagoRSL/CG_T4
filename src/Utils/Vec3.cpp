#include "Vec3.h"

Vec3::Vec3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->Anchor = nullptr;
}

Vec3::Vec3(float v[3])
{
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
    this->Anchor = nullptr;
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->Anchor = nullptr;
}

float Vec3::GetNorm()
{
    return sqrtf((x*x) + (y*y) + (z*z));
}

void Vec3::Normalize()
{
    float norm = this->GetNorm();
    this->x = this->x / norm;
    this->y = this->y / norm;
    this->z = this->z / norm;
}
/*
void Vec3::RotateDegrees(float degrees)
{
    this->RotateRadians(degrees * (PI / 180));
}

void Vec3::RotateRadians(float radians)
{
    float aux_x = this->x;
    float aux_y = this->y;
    this->x = (aux_x * cosf(radians)) - (aux_y * sinf(radians));
    this->y = (aux_x * sinf(radians)) + (aux_y * cosf(radians));
}*/
    float Vec3::DotProduct(Vec3* v)
    {
        return (this->x * v->x) + (this->y * v->y) + (this->z * v->z);
    }
    float Vec3::Determinant(Vec3* v)
    {
        return x*v->y + v->x*z + y*v->z - v->y*z - x*v->z - v->x*y;
    }
    float Vec3::GetAngleBetween(Vec3* v)
    {
        float det = Determinant(v);
        float arc_tan = atan2(det, DotProduct(v));
        if(isnan(arc_tan))
            return 0;
        else
            return atan2(det, DotProduct(v));
    }
    /*void Mult(float scalar);
    void Sum(float scalar);
    void Sum(Vec3& v2);
    void Sum(Vec3* v2);
    void Sub(Vec3* v2);

    void RotateDegrees(float degrees);
    void RotateRadians(float radians);*/

    void Vec3::Render()
    {
        printf("Renderizei o Vec3");
    }
    Vec3* Vec3::GetCopy()
    {
        return new Vec3(x, y, z);
    }
