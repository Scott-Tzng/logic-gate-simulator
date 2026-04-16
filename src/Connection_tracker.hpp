#pragma once

#include <list>

#include "Block.hpp"

struct Connection {
    Block* input;
    Block* output;
    Input_node node;
};

// keeps track of all the connections between blocks
class Connection_tracker {
public:
    void add_connection(Block* input, Block* output, Input_node node);
    void for_each(void (*func)(Connection&));
    std::list<Connection>::iterator find_if(bool (*cond)(Connection&), bool& found);
    void delete_connection(std::list<Connection>::iterator iter);
    // removes all connections that involve block
    void delete_connecitons_with(const Block* block);
    void transmit_signals();

private:
    std::list<Connection> m_connections;
};
