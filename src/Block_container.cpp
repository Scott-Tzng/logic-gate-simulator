#include "Block_container.hpp"

#include <algorithm>

void Block_container::add_block(Vector2 pos, Block_type type)
{
    m_blocks.emplace_front(pos, type);
}

void Block_container::remove_block(std::list<Block>::iterator iter)
{
    m_blocks.erase(iter);
}

void Block_container::for_each(void (*func)(Block&))
{
    std::for_each(m_blocks.rbegin(), m_blocks.rend(), func);
}

void Block_container::move_top_layer(std::list<Block>::iterator iter)
{
    m_blocks.splice(m_blocks.begin(), m_blocks, iter);
}


std::list<Block>::iterator Block_container::find_if(bool (*cond)(Block&), bool& found)
{
    auto iter {std::find_if(m_blocks.begin(), m_blocks.end(), cond)};
    found = iter != m_blocks.end();
    return iter;
}
