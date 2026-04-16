#pragma once

#include <raylib.h>

enum class Block_type {
    SWITCH,
    LIGHT,
    AND,
    OR,
    XOR,
    NOT,
    NAND,
    NOR,
    XNOR,
};

enum class Input_node {
    TOP,
    CENTER,
    BOT,
};

class Block {
public:
    Block(Vector2 pos, Block_type type);

    void move(Vector2 delta);
    bool output_signal();
    void recieve_top_signal(bool signal);
    void recieve_bot_signal(bool signal);
    void toggle_switch();
    bool is_switch_on() const;
    bool is_light_on() const;

    Block_type get_type() const;
    Rectangle get_rect() const;
    Rectangle get_switch_rect() const;
    Vector2 get_top_input_loc() const;
    Vector2 get_center_input_loc() const;
    Vector2 get_bot_input_loc() const;
    Vector2 get_ouput_loc() const;
    static float get_node_radius();
    const char* get_type_text() const;

private:
    Vector2 m_pos;
    Block_type m_type;
    bool m_switch_on {false};
    bool m_top_signal {false};
    bool m_bot_signal {false};
};
