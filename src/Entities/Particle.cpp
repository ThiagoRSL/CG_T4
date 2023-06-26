#include "Particle.h"

Particle::Particle(float framesToLive, float *RGB)
{
    this->framesToLive = framesToLive;
    this->RGB[0] = RGB[0];
    this->RGB[1] = RGB[1];
    this->RGB[2] = RGB[2];
}

void Particle::AddPoint(float x, float y)
{
    std::tuple<float, float> point = std::make_tuple(x, y);
    Points[point] = framesToLive;
}

void Particle::Render()
{
    float frames = FPSManager::shared_instance().GetFrames();

    if(frames != lastFrame)
    {
        std::vector<std::tuple<float, float>> eraseIndexes;
        for (auto it : Points)
        {
            Points[it.first] = it.second - 1;
            if(it.second <= 0) eraseIndexes.push_back(it.first);
        }

        int i;
        for (i = 0; i < eraseIndexes.size(); i++)
        {
            Points.erase(eraseIndexes[i]);
        }
        lastFrame = frames;
    }
    glBegin(GL_POINTS);
    for (auto iter : Points)
    {
        float multiplier = iter.second/framesToLive;
        glColor3f(RGB[0] * multiplier, RGB[1] * multiplier, RGB[2] * multiplier);
        glVertex2d(std::get<0>(iter.first) - CameraOffsetRef->x, std::get<1>(iter.first) - CameraOffsetRef->y);
    }
    glEnd();
}
