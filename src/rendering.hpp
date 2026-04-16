#pragma once

#include "Block_container.hpp"
#include "Connection_tracker.hpp"

namespace rendering {
    void draw_blocks(Block_container& blocks);

    void draw_connections(Connection_tracker& connections);

    constexpr float line_thickness {5.f};
};
