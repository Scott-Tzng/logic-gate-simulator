#pragma once

#include "Block_container.hpp"
#include "Connection_tracker.hpp"
#include "User_input_handler.hpp"

class App {
public:
    App();
    ~App();

    void run();

private:
    Block_container m_blocks;
    Connection_tracker m_connections;
    User_input_handler m_user_input;
};
