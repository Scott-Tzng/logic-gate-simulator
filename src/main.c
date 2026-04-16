#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "algorithms.h"
#include "input.h"
#include "elements.h"
#include "statistics.h"
#include "timer.h"
#include "ui.h"

#define DEFAULT_NUM_ELEMENTS  10
#define DEFAULT_DELAY_SECONDS 1

int main(int argc, char** argv)
{
        srand(time(NULL));

        init_algorithms();

        struct elements elements;

        if (argc == 1) {
                elements.size = DEFAULT_NUM_ELEMENTS;
        }
        else {
                int num_elements = atoi(argv[1]);
                if (num_elements == 0 || num_elements == 1) {
                        printf("Invalid numberf of elements\n");
                        printf("Number of elements should be > 1\n");
                        return -1;
                }
                elements.size = num_elements;
        }

        elements.data = malloc(sizeof(int) * elements.size);
        reset_elements(elements);

        struct sorting_statistics statistics = {
                .steps = 0,
                .delay = DEFAULT_DELAY_SECONDS
        };

        bool sorting = false;
        
        struct timer sorting_timer = {
                .start_time = 0.f,
                .duration   = DEFAULT_DELAY_SECONDS
        };

        select_algorithm(MERGE);

        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sorting Visualizer");
        SetTargetFPS(60);
    
        while (!WindowShouldClose()) {
                handle_user_input(elements, &statistics, &sorting_timer);

                draw_ui(elements, statistics);
        }

        CloseWindow();

        return 0;
}
