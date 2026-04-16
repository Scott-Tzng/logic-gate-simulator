#ifndef SRC_INPUT_H
#define SRC_INPUT_H

#include <stdbool.h>

#include "elements.h"
#include "statistics.h"
#include "timer.h"

void handle_user_input(
        struct elements e,
        struct sorting_statistics* s,
        struct timer* t);

bool is_sorting();

#endif
