#include "App.hpp"

#include <raylib.h>

#include "rendering.hpp"

constexpr int screen_width {1280};
constexpr int screen_height {960};

App::App()
    : m_user_input {m_blocks, m_connections}
{
    InitWindow(screen_width, screen_height, "Logic Gate Sim");
    SetExitKey(KEY_NULL);
}

App::~App()
{
    CloseWindow();
}

void App::run()
{
    while (!WindowShouldClose()) {
        m_user_input.handle_input();

        m_connections.transmit_signals();

        BeginDrawing();
        
        ClearBackground(BLACK);

        rendering::draw_connections(m_connections);
        rendering::draw_blocks(m_blocks);

        DrawFPS(0, 0);

        EndDrawing();
    }
}
