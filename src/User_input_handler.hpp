#pragma once

#include "Block.hpp"

#include "Block_container.hpp"
#include "Connection_tracker.hpp"

class User_input_handler {
public:
    User_input_handler(Block_container& blocks, Connection_tracker& connections);

    void handle_input();
    
private:
    void create_block();
    void make_connection();
    void move_block();
    void delete_block();
    void break_connection();

    void toggle_switches();

    Block_container& m_blocks;
    Connection_tracker& m_connections;

    Block* m_block_move_selection {nullptr};
    Block* m_connection_input {nullptr};
};
