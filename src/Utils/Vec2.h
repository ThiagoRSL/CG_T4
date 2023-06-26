#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Entities/Abstract/Renderable.h"
#include "gl_canvas2d.h"
#include "Utils/Pnt2.h"

class GeometryAux;

class Vec2 : public Renderable
{
    public:
        float x, y;
        float RelativeX();
        float RelativeY();

        Vec2();
        Vec2(float v[2]);
        Vec2(float x, float y);
        Vec2(float x, float y, Pnt2* anchor);

        // Getters
        float GetNorm();
        float DotProduct(Vec2* v);
        float Determinant(Vec2* v);

        float GetAngleBetween(Vec2* v);

        Vec2 operator* (const float& scalar)
        {
            Vec2 aux(x * scalar, y * scalar);
            return (aux);
        }
        Vec2 operator+ (const Vec2& vec)
        {
            Vec2 aux(x + vec.x, y + vec.y);
            return (aux);
        }
        // Operações no próprio vetor
        void Mult(float scalar);
        void Sum(float scalar);
        void Sum(Vec2& v2);
        void Sum(Vec2* v2);
        void Sub(Vec2* v2);

        void ApplyAtPoint();
        // Normaliza o proprio vetor
        void Normalize();
        // Rotaciona o vetor em alguns graus
        void RotateDegrees(float degrees);
        void RotateRadians(float radians);

        Pnt2 AsPnt();

        void Render();

    public:
        Vec2* GetCopy();

};

#endif // VEC2_H
