#ifndef SRC_ELEMENTS_H
#define SRC_ELEMENTS_H

#include <stdbool.h>

struct elements {
        int* data;
        int size;
};

bool is_sorted(struct elements e);
void print_elements(struct elements e);
void reset_elements(struct elements e);
void shuffle_elements(struct elements e);

#endif
