#include "timer.h"

Timer::Timer()
{
    start_time = 0;
}

void Timer::start()
{
    start_time = SDL_GetTicks();
}

Uint32 Timer::get_time()
{
    return SDL_GetTicks() - start_time;
}
