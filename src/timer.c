#include "timer.h"

#include <raylib.h>


void start_timer(struct timer* timer, seconds duration)
{
        timer->start_time = GetTime();
        timer->duration   = duration;
}

void resetart_timer(struct timer* timer)
{
        timer->start_time = GetTime();
}

bool is_timer_done(struct timer timer)
{
        return GetTime() - timer.start_time >= timer.duration;
}
