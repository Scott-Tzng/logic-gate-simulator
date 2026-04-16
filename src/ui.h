#ifndef SRC_UI_H
#define SRC_UI_H

#include<stdbool.h>

#include "elements.h"
#include "statistics.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 900

#define PADDING 5

void draw_ui(struct elements e, struct sorting_statistics stats);

#endif
