#ifndef PNT2_H
#define PNT2_H

class Vec2;

class Pnt2
{
    public:
        Pnt2();
        ~Pnt2();
        Pnt2(float x, float y);

        float x;
        float y;

        void ApplyVec2(Vec2 vec);
        Vec2 AsVec();
        //Pnt2 operator+ (const Vec2& vec);
        //Pnt2 operator+= (const Vec2& vec);
    protected:

    private:
};

#endif // PNT2_H
