#include "timer.h"
#include <SDL2/SDL.h>
#include<iostream>
#include "window.h"

Timer::Timer()
{
    numFrames=0;
    totalTime=0;
}

double Timer::printFPS()
{
    const double startTime = SDL_GetTicks();
    SDL_Delay( 1.0f/60.0f );
    const double endTime = SDL_GetTicks();
    totalTime = endTime - startTime;
    return totalTime;
}
