#include "algorithms.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

static enum algorithm selected_algorithm;

static struct {
        int num_sorted;
} selection_state;

static void step_selection_sort(struct elements e)
{
        int smallest_value = e.data[selection_state.num_sorted];
        int smallest_index = selection_state.num_sorted;
        for (int i = selection_state.num_sorted; i < e.size; ++i) {
                if (e.data[i] < smallest_value) {
                        smallest_value = e.data[i];
                        smallest_index = i;
                }
        }

        int temp = e.data[selection_state.num_sorted];
        e.data[selection_state.num_sorted] = e.data[smallest_index];
        e.data[smallest_index] = temp;

        ++selection_state.num_sorted;
}

static struct {
        int farthest_sorted;
} insertion_state;

static void step_insertion_sort(struct elements e)
{
        int target_index = insertion_state.farthest_sorted + 1;
        int swap_index   = target_index - 1;

        while (e.data[target_index] < e.data[swap_index]) {
                int temp = e.data[swap_index];
                e.data[swap_index] = e.data[target_index];
                e.data[target_index] = temp;
                        
                --target_index;
                --swap_index;
        }

        ++insertion_state.farthest_sorted;
}

static struct {
        bool initial_split_done;
        int* element_groups;
        int  num_groups;
        // groups are merged together in each pass
        // one pass represents would mean going from this:
        // 00 11 22 33
        // to this:
        // 0000 1111
        bool done_with_pass;
        // which groups are next to be merged
        int  pass_index;
} merge_state;

// basically performs the splitting step
static void merge_init(struct elements e)
{
        merge_state.element_groups = malloc(sizeof(int) * e.size);
        merge_state.initial_split_done = true;

        for (int i = 0; i < e.size; ++i) {
                // make it so that every 2 elements have the same
                // grouping value
                // integer division rounds down
                int group = i / 2;
                merge_state.element_groups[i] = group;
        }
        
        // intial sort on pairs
        for (int i = 0; i < e.size - 1; i += 2) {
                if (e.data[i] > e.data[i + 1]) {
                        int temp = e.data[i];
                        e.data[i] = e.data[i + 1];
                        e.data[i + 1] = temp;
                }
        }

        merge_state.num_groups = (e.size + 1) / 2;
}

static void merge(struct elements e, int group_1, int group_2)
{
        int group_1_len = 0;
        int group_2_len = 0;
        for (int i = 0; i < e.size; ++i) {
                if (merge_state.element_groups[i] == group_1) {
                        ++group_1_len;
                }
                else if (merge_state.element_groups[i] == group_2) {
                        ++group_2_len;
                }
        }

        int total_len = group_1_len + group_2_len;
        int* sorted = malloc(sizeof(int) * (total_len));
        if (sorted == NULL) {
                printf("Malloc failed!\n");
                exit(EXIT_FAILURE);
        }

        // find the start of the groups
        int group_1_begin = 0;
        int group_1_index = -1;
        int group_2_index = -1;

        for (int i = 0; i < e.size; ++i) {
                int group = merge_state.element_groups[i];
                if (group == group_1 && group_1_index == -1) {
                        group_1_begin = i;
                        group_1_index = i;
                }
                
                if (group == group_2 && group_2_index == -1) {
                        group_2_index = i;
                }
        }

        int group_1_end  = group_1_index + group_1_len;
        int group_2_end  = group_2_index + group_2_len;
        int sorted_index = 0;
        while (group_1_index < group_1_end && group_2_index != group_2_end) {
                int group_1_item = e.data[group_1_index];
                int group_2_item = e.data[group_2_index];

                if (group_1_item < group_2_item) {
                        sorted[sorted_index] = group_1_item;
                        ++group_1_index;
                }
                else {
                        sorted[sorted_index] = group_2_item;
                        ++group_2_index;
                }
                
                ++sorted_index;
        }

        // fill in the rest of sorted
        if (group_1_index == group_1_end) {
                for (; group_2_index < group_2_end; ++group_2_index) {
                        sorted[sorted_index] = e.data[group_2_index];
                        ++sorted_index;
                }
        } else {
                for (; group_1_index < group_1_end; ++group_1_index) {
                        sorted[sorted_index] = e.data[group_1_index];
                        ++sorted_index;
                }
        }
        
        // copy sorted to elements and merge groupings
        for (int i = group_1_begin; i < group_2_end; ++i) {
                e.data[i] = sorted[i - group_1_begin];
                merge_state.element_groups[i] = group_1;
        }

        free(sorted);
}

static void merge_update_groups(struct elements e)
{
        merge_state.num_groups /= 2;
        for (int i = 0; i < e.size; ++i) {
                ++merge_state.element_groups[i];
                merge_state.element_groups[i] /= 2;
        }
}

// Modified implementation of merge sort that I don't know how to
// describe and also not very efficient.
// Merge sort is also just kinda weird to visualize.
// Merge sort is usually implemented recursively but I want to see the
// steps and it is hard to be able to see the steps when using recursion.
// (I think!)
static void step_merge_sort(struct elements e) {
        if (!merge_state.initial_split_done) {
                merge_init(e);
        }
        else if (merge_state.pass_index >= merge_state.num_groups - 1) {
                merge_state.pass_index = 0;
                merge_update_groups(e);
                merge(e, merge_state.pass_index, merge_state.pass_index + 1);
                merge_state.pass_index += 2;
        }
        else {
                merge(e, merge_state.pass_index, merge_state.pass_index + 1);
                merge_state.pass_index += 2;
        }
}

void sort(struct timer* t, struct elements e, struct sorting_statistics* s)
{
        if (is_timer_done(*t)) {
                step(e);
                resetart_timer(t);
                ++s->steps;
        }
}

void step(struct elements e)
{
        switch (selected_algorithm) {
        case SELECTION: step_selection_sort(e); break;
        case INSERTION: step_insertion_sort(e); break;
        case MERGE:     step_merge_sort(e);     break;
        }
}

void init_algorithms()
{
        selection_state.num_sorted = 0;

        insertion_state.farthest_sorted = 0;

        merge_state.initial_split_done = false;
        merge_state.element_groups     = NULL;
        merge_state.done_with_pass     = false;
        merge_state.pass_index         = 0;
}

void reset_algorithms()
{
        selection_state.num_sorted = 0;

        insertion_state.farthest_sorted = 0;

        merge_state.initial_split_done = false;
        free(merge_state.element_groups);
        merge_state.element_groups = NULL;
        merge_state.done_with_pass = false;
        merge_state.pass_index     = 0;
}

void select_algorithm(enum algorithm selection)
{
        selected_algorithm = selection;
}

enum algorithm get_selected_algorithm()
{
        return selected_algorithm;
}
