#ifndef CURVES_H
#define CURVES_H

#include "gl_canvas2d.h"
#include <vector>
#include "Entities/Abstract/Renderable.h"
#include "Pnt2.h"
#include "GeometryAux.h"
#include "RenderManager.h"


class Curve2d : public Renderable
{

    public:
        Curve2d();
        ~Curve2d();

        void SetColor(float* color) {Color[0] = color[0];Color[1] = color[1];Color[2] = color[2];}
        void AddControlPoint(Pnt2* point);
        void SetShowControlGraph(bool show) {show_control_graph = show;}
        void SetShowWithLines(bool show) {show_with_lines = show;}
        void SetCurveResolution(float resolution) {curve_resolution = resolution;}
        virtual void GenerateCurvePoints() = 0;
        Pnt2* NearPoint(Pnt2 point, float distanceMin);
        Pnt2* GetFirstCurvePoint() { return CurvePoints.at(0);}
        Pnt2* GetLastCurvePoint() { return CurvePoints.at(CurvePoints.size()-1);}
        Pnt2* GetCurvePoint(int i);
        void UpdateClosestPoint();

        void Render();

    protected:
        bool show_control_graph;
        bool show_with_lines;
        float curve_resolution;
        float Color[3];
        std::vector<Pnt2*> ControlPoints;
        std::vector<Pnt2*> CurvePoints;
        int firstToRenderIndex, lastToRenderIndex;
        void RenderWithLines();
        void RenderWithPoints();
};

class BSpline : public Curve2d
{
    public:
        BSpline();

        void GenerateCurvePoints();
};

class Bezier : public Curve2d
{
    public:
        Bezier();

        void GenerateCurvePoints();

};
#endif // CURVES_H
