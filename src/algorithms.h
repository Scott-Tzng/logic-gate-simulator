#ifndef SRC_ALGORITHMS_H
#define SRC_ALGORITHMS_H

#include <stdbool.h>

#include "elements.h"
#include "statistics.h"
#include "timer.h"

enum algorithm {
        SELECTION,
        INSERTION,
        MERGE,
};

void sort(struct timer* t, struct elements e, struct sorting_statistics* s);
void step(struct elements e);

void init_algorithms(); // should be called before any sorting
void reset_algorithms();
void select_algorithm(enum algorithm selection);
enum algorithm get_selected_algorithm();

#endif
