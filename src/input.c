#include "input.h"

#include <raylib.h>

#include "algorithms.h"

#define DELAY_INCREMENT 0.1

static bool sorting = false;

static void reset(struct elements elements, struct sorting_statistics* stats)
{
        reset_algorithms();
        reset_elements(elements);
        sorting = false;
        stats->steps = 0;
}

static void sorting_controls(
        struct elements elements,
        struct sorting_statistics* stats,
        struct timer* timer)
{
        // shuffling
        if (IsKeyPressed(KEY_S)) {
                shuffle_elements(elements);
                reset_algorithms();
                stats->steps = 0;
                sorting = false;
        }

        // reseting
        if (IsKeyPressed(KEY_R)) {
                reset(elements, stats);
        }

        // toggle sorting
        if (IsKeyPressed(KEY_SPACE)) {
                sorting = !sorting;
        }

        // step through sorting
        if (IsKeyPressed(KEY_RIGHT)) {
                sorting = false;
                step(elements);
                ++stats->steps;
        }

        if (is_sorted(elements)) {
                sorting = false;
        }

        if (sorting) {
                sort(timer, elements, stats);
        }
}

static void change_delay(struct sorting_statistics* stats, struct timer* timer)
{
        if (IsKeyPressed(KEY_UP)) {
                stats->delay    += DELAY_INCREMENT;
                timer->duration += DELAY_INCREMENT;
        }
        if (IsKeyPressed(KEY_DOWN) &&
                stats->delay > 2 * DELAY_INCREMENT) {

                stats->delay    -= DELAY_INCREMENT;
                timer->duration -= DELAY_INCREMENT;
        }
}

static void change_alogrithm(
        struct elements elements,
        struct sorting_statistics* stats)
{
        if (IsKeyPressed(KEY_ONE)) {
                select_algorithm(SELECTION);
                reset(elements, stats);
                
        }
        if (IsKeyPressed(KEY_TWO)) {
                select_algorithm(INSERTION);
                reset(elements, stats);
        }
        if (IsKeyPressed(KEY_THREE)) {
                select_algorithm(MERGE);
                reset(elements, stats);
        }
}

void handle_user_input(
        struct elements elements,
        struct sorting_statistics* stats,
        struct timer* timer)
{
        sorting_controls(elements, stats, timer);
        change_delay(stats, timer);
        change_alogrithm(elements, stats);
}

bool is_sorting()
{
        return sorting;
}
