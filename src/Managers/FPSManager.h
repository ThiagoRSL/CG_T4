#ifndef FPSMANAGER_H
#define FPSMANAGER_H

#include <stdio.h>
#include <time.h>
#define UPDATE_RATE 30   //milisegundos
class FPSManager
{
    public:
        static FPSManager &shared_instance() {static FPSManager fpsManager; return fpsManager;}
        float UpdateFrames();
        float GetFrames();

    private:
        clock_t t1, t2;
        long    cont_frames;
        float   fps, fps_old, frames;

};
#endif // FPSMANAGER_H
