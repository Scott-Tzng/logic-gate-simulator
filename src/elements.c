#include "elements.h"

#include <stdio.h>
#include <stdlib.h>

bool is_sorted(struct elements e)
{
        // data[i] should be one less than data[i + 1]

        for (int i = 0; i < e.size - 1; ++i) {
                if (e.data[i] + 1 != e.data[i + 1]) {
                        return false;
                }
        }
        
        return true;
}

void print_elements(struct elements e)
{
        for (int i = 0; i < e.size; ++i) {
                printf("elements[%i]: %i\n", i, e.data[i]);
        }
}

void reset_elements(struct elements e)
{
        for (int i = 0; i < e.size; ++i) {
                e.data[i] = i;
        }
}


void shuffle_elements(struct elements e)
{
        if (e.size == 1) {
                return;
        }

        // implementation of the Fisher-Yates algorithm
        for (int i = e.size - 1; i > 0; --i) {
                int j = rand() % (i + 1);
                int temp = e.data[i];
                e.data[i] = e.data[j];
                e.data[j] = temp;
        }
}
