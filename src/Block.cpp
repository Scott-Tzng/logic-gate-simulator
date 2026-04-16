#include "Block.hpp"

#include <raymath.h>

constexpr Vector2 block_size {80, 60};
constexpr int node_radius {8};

Block::Block(Vector2 pos, Block_type type)
    : m_pos {pos}
    , m_type {type}
{
    
}

void Block::move(Vector2 delta)
{
    m_pos = Vector2Add(m_pos, delta);
}

bool Block::output_signal()
{
    // switch and lights don't have text so they aren't in this switch statement
    switch (m_type) {
    case Block_type::SWITCH:
        return m_switch_on;
    case Block_type::LIGHT:
        // light doesn't output anything and this should never get called for a light
        return false;
    case Block_type::AND:
        return m_top_signal && m_bot_signal;
    case Block_type::OR:
        return m_top_signal || m_bot_signal;
    case Block_type::XOR:
        return (m_top_signal && !m_bot_signal) || (!m_top_signal && m_bot_signal);
    case Block_type::NOT:
        return !m_top_signal;
    case Block_type::NAND:
        return !(m_top_signal && m_bot_signal);
    case Block_type::NOR:
        return !(m_top_signal || m_bot_signal);
    default: // case Block_type::XNOR:
        return !((m_top_signal && !m_bot_signal) || (!m_top_signal && m_bot_signal));
    }
}

void Block::recieve_top_signal(bool signal)
{
    m_top_signal = signal;
}

void Block::recieve_bot_signal(bool signal)
{
    m_bot_signal = signal;
}

void Block::toggle_switch()
{
    if (m_type != Block_type::SWITCH) {
        return;
    }

    m_switch_on = !m_switch_on;
}

bool Block::is_switch_on() const
{
    return m_switch_on && m_type == Block_type::SWITCH;
}

bool Block::is_light_on() const
{
    return m_top_signal && m_type == Block_type::LIGHT;
}

Block_type Block::get_type() const
{
    return m_type;
}

Rectangle Block::get_rect() const
{
    return { m_pos.x, m_pos.y, block_size.x, block_size.y };
}

Rectangle Block::get_switch_rect() const
{
    return { m_pos.x + 16, m_pos.y + 12, block_size.x - 32, block_size.y - 24 };
}

Vector2 Block::get_top_input_loc() const
{
    return { m_pos.x - node_radius, m_pos.y + (block_size.y / 3) };
}

Vector2 Block::get_center_input_loc() const
{
    return { m_pos.x - node_radius, m_pos.y + (block_size.y / 2) };
}

Vector2 Block::get_bot_input_loc() const
{
    return { m_pos.x - node_radius, m_pos.y + (2 * block_size.y / 3) };

}

Vector2 Block::get_ouput_loc() const
{
    return { m_pos.x + block_size.x + node_radius, m_pos.y + (block_size.y / 2) };
}

float Block::get_node_radius()
{
    return node_radius;
}

const char* Block::get_type_text() const
{
    // switch and lights don't have text so they aren't in this switch statement
    switch (m_type) {
    case Block_type::AND:
        return "AND";
    case Block_type::OR:
        return "OR";
    case Block_type::XOR:
        return "XOR";
    case Block_type::NOT:
        return "NOT";
    case Block_type::NAND:
        return "NAND";
    case Block_type::NOR:
        return "NOR";
    default: // Block_type::XNOR
        return "XNOR";
    }
}
