#pragma once

#include <functional>
#include <list>

#include "Block.hpp"

#include <raylib.h>

class Block_container {
public:
    void add_block(Vector2 pos, Block_type type);
    void remove_block(std::list<Block>::iterator iter);
    // sets the block referenced by iter to be the top layer
    // blocks are layered for drawing
    void move_top_layer(std::list<Block>::iterator iter);

    // data access

    // these two functions basically do the same thing as their std equivalents
    // but are here to encapsulate the data more and limits what the user can
    // do with m_blocks

    void for_each(void (*func)(Block&));
    std::list<Block>::iterator find_if(bool (*cond)(Block&), bool& found);

private:
    std::list<Block> m_blocks;
};