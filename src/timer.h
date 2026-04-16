#ifndef SRC_TIMER_H
#define SRC_TIMER_H

#include <stdbool.h>

#include "statistics.h"

struct timer {
        double start_time;
        seconds duration;
};

void start_timer(struct timer* timer, seconds duration);
void resetart_timer(struct timer* timer);

bool is_timer_done(struct timer timer);

#endif
