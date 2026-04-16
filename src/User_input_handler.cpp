#include "User_input_handler.hpp"

#include <cmath>

#include "rendering.hpp"

static auto mouse_in_gate {
    [](Block& b) {
        return CheckCollisionPointRec(GetMousePosition(), b.get_rect());
    }
};

User_input_handler::User_input_handler(Block_container& blocks, Connection_tracker& connections)
    : m_blocks {blocks}
    , m_connections {connections}
{
}

void User_input_handler::handle_input()
{
    create_block();
    make_connection();
    move_block();
    delete_block();
    break_connection();

    toggle_switches();
}

void User_input_handler::create_block()
{
    // keybinds to create
    // 1: SWITCH
    // 2: LIGHT
    // 3: NOT
    // 4: AND
    // 5: OR
    // 6: NAND
    // 7: NOR
    // 8: XOR
    // 9: XNOR

    if (IsKeyPressed(KEY_ONE)) {
        m_blocks.add_block(GetMousePosition(), Block_type::SWITCH);
    }
    else if (IsKeyPressed(KEY_TWO)) {
        m_blocks.add_block(GetMousePosition(), Block_type::LIGHT);
    }
    else if (IsKeyPressed(KEY_THREE)) {
        m_blocks.add_block(GetMousePosition(), Block_type::NOT);
    }
    else if (IsKeyPressed(KEY_FOUR)) {
        m_blocks.add_block(GetMousePosition(), Block_type::AND);
    }
    else if (IsKeyPressed(KEY_FIVE)) { 
        m_blocks.add_block(GetMousePosition(), Block_type::OR);
    }
    else if (IsKeyPressed(KEY_SIX)) {
        m_blocks.add_block(GetMousePosition(), Block_type::NAND);
    }
    else if (IsKeyPressed(KEY_SEVEN)) {
        m_blocks.add_block(GetMousePosition(), Block_type::NOR);
    }
    else if (IsKeyPressed(KEY_EIGHT)) {
        m_blocks.add_block(GetMousePosition(), Block_type::XOR);
    }
    else if (IsKeyPressed(KEY_NINE)) {
        m_blocks.add_block(GetMousePosition(), Block_type::XNOR);
    }
}

void User_input_handler::make_connection()
{
    // yes I know this function is hideous

    auto mouse_clicked_in_output {
        [](Block& b)
        {
            bool mouse_in_output {
                CheckCollisionPointCircle(
                    GetMousePosition(),
                    b.get_ouput_loc(),
                    Block::get_node_radius()
                )
            };
            return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse_in_output;
        }
    };

    auto mouse_in_top_input {
        [](Block& b)
        {
            bool correct_type {b.get_type() != Block_type::NOT && b.get_type() != Block_type::LIGHT};
            bool collides {
                CheckCollisionPointCircle(
                    GetMousePosition(),
                    b.get_top_input_loc(),
                    Block::get_node_radius()
                )
            };

            return correct_type && collides;
        }
    };

    auto mouse_in_center_input {
        [](Block& b)
        {
            bool correct_type {b.get_type() == Block_type::NOT || b.get_type() == Block_type::LIGHT};
            bool collides {
                CheckCollisionPointCircle(
                    GetMousePosition(),
                    b.get_center_input_loc(),
                    Block::get_node_radius()
                )
            };

            return correct_type && collides;
        }
    };

    auto mouse_in_bot_input {
        [](Block& b)
        {
            bool correct_type {b.get_type() != Block_type::NOT && b.get_type() != Block_type::LIGHT};
            bool collides {
                CheckCollisionPointCircle(
                    GetMousePosition(),
                    b.get_bot_input_loc(),
                    Block::get_node_radius()
                )
            };

            return correct_type && collides;
        }      
    };

    // connections are made by clicking on the output and then the input
    
    // check the output nodes
    if (m_connection_input == nullptr) {
        bool found {};
        auto block {m_blocks.find_if(mouse_clicked_in_output, found)};
        
        if (!found) {
            return;
        }

        m_connection_input = &(*block);
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // check top input nodes first
        bool found {};
        auto block {m_blocks.find_if(mouse_in_top_input, found)};
        // found something with the top input nodes
        if (found) {
            // "&(*block)" is the input node
            m_connections.add_connection(m_connection_input, &(*block), Input_node::TOP);
            m_connection_input = nullptr;
            return;
        }

        // check the middle input nodes (if they exist)
        block = m_blocks.find_if(mouse_in_center_input, found);
        if (found) {
            m_connections.add_connection(m_connection_input, &(*block), Input_node::CENTER);
            m_connection_input = nullptr;
            return;
        }

        // check the bottom input nodes if the top input nodes don't work
        block = m_blocks.find_if(mouse_in_bot_input, found);
        if (found) {
            // same thing as above
            m_connections.add_connection(m_connection_input, &(*block), Input_node::BOT);
            m_connection_input = nullptr;
            return;
        }

        m_connection_input = nullptr;
    }
}

void User_input_handler::move_block()
{
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        m_block_move_selection = nullptr;
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        bool found {};
        auto iter {m_blocks.find_if(mouse_in_gate, found)};
        if (found) {
            m_block_move_selection = &(*iter);
            m_blocks.move_top_layer(iter);
        }
        else {
            m_block_move_selection = nullptr;
        }
    }

    if (m_block_move_selection != nullptr) {
        m_block_move_selection->move(GetMouseDelta());
    }
}

void User_input_handler::delete_block()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        return;
    }

    bool found {};
    auto iter {m_blocks.find_if(mouse_in_gate, found)};
    if (found) {
        m_connections.delete_connecitons_with(&(*iter));
        m_blocks.remove_block(iter);
    }
}

void User_input_handler::break_connection()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        return;
    }

    // check if where the user clicked is inside a connection
    // a connection contains two points so we can use the formula to find the
    // distance from a point to a line

    // I used the wikipedia article and Sebastian Lague video on this for help

    
    auto check {
        [](Connection& c) {
            // p1 and p2 are the points that define the line
            // p3 is the position of the mouse click

            Vector2 p1 {c.input->get_ouput_loc()};
            Vector2 p2 {};
            switch (c.node) {
            case Input_node::TOP:
                p2 = c.output->get_top_input_loc();
                break;
            case Input_node::CENTER:
                p2 = c.output->get_center_input_loc();
                break;
            case Input_node::BOT:
                p2 = c.output->get_bot_input_loc();
                break;
            }
            Vector2 p3 {GetMousePosition()};

            float numerator {
                std::abs(((p2.y - p1.y) * p3.x) - ((p2.x - p1.x) * p3.y) + (p2.x * p1.y) - (p2.y * p1.x))
            };

            float denominator {
                std::sqrtf(std::powf(p2.y - p1.y, 2) + std::powf(p2.x - p1.x, 2))
            };

            return numerator / denominator < rendering::line_thickness;
        }
    };

    bool found {};
    auto connection {m_connections.find_if(check, found)};
    if (found) {
        m_connections.delete_connection(connection);
    }
}

void User_input_handler::toggle_switches()
{
    auto func {
        [](Block& b) {
            return b.get_type() == Block_type::SWITCH &&
                CheckCollisionPointRec(GetMousePosition(), b.get_switch_rect());
        }
    };

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return;
    }

    bool found {};
    auto block {m_blocks.find_if(func, found)};
    if (!found) {
        return;
    }

    block->toggle_switch();
}
