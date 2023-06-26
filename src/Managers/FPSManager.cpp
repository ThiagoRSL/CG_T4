#include "FPSManager.h"
float FPSManager::UpdateFrames()
{
  double tempo;

  t2 = clock();
  tempo  = (double)(t2 - t1);
  cont_frames++;

  if( tempo > UPDATE_RATE )
  {
     t1 = t2;
     fps = cont_frames / (tempo/CLOCKS_PER_SEC);
     cont_frames = 0;
     fps_old = fps;

     frames = fps;
  }
  else
  {
    frames = fps_old;
  }
}

float FPSManager::GetFrames()
{
    return frames;
}
