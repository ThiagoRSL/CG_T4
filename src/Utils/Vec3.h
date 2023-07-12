#ifndef VEC3_H
#define VEC3_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Vec3
{
    public:
        Vec3* Anchor;
        float x, y, z;

        Vec3();
        Vec3(float v[3]);
        Vec3(float x, float y, float z);
        //virtual ~Vec3();

        void ApplyAtPoint();
        void Normalize();

        float GetNorm();
        float DotProduct(Vec3* v);
        float Determinant(Vec3* v);
        float GetAngleBetween(Vec3* v);

        Vec3 operator* (const float& scalar)
        {
            Vec3 aux(x * scalar, y * scalar, z * scalar);
            return (aux);
        }
        Vec3 operator+ (const Vec3& vec)
        {
            Vec3 aux(x + vec.x, y + vec.y, z + vec.z);
            return (aux);
        }

        void Mult(float scalar);
        void Sum(float scalar);
        void Sum(Vec3& v2);
        void Sum(Vec3* v2);
        void Sub(Vec3* v2);

        void RotateDegrees(float degrees);
        void RotateRadians(float radians);

        void Render();
        Vec3* GetCopy();
};

#endif // VEC3_H
