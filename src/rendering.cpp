#include "rendering.hpp"

void rendering::draw_blocks(Block_container& blocks)
{
    // indentation rules be dammed
    blocks.for_each(
        [](Block& b)
        { 
            // main body the gate

            DrawRectangleRec(b.get_rect(), BLUE);

            // draw text centered on gate

            const Vector2 pos {b.get_rect().x, b.get_rect().y};
            const Vector2 block_size {b.get_rect().width, b.get_rect().height};
            const Vector2 gate_center {
                pos.x + (block_size.x / 2),
                pos.y + (block_size.y / 2)};

            // switches and lights don't have text; they have graphics
            if (b.get_type() == Block_type::SWITCH) {

            }
            else if (b.get_type() == Block_type::LIGHT) {
                if (b.is_light_on()) {
                    DrawRectangle(
                        pos.x + 16,
                        pos.y + 12,
                        block_size.x - 32,
                        block_size.y - 24,
                        YELLOW
                    ); 
                }
                else {
                    DrawRectangle(
                        pos.x + 16,
                        pos.y + 12,
                        block_size.x - 32,
                        block_size.y - 24,
                        BLACK
                    ); 
                }
            }

            if ((b.get_type() == Block_type::SWITCH && b.is_switch_on()) ||
                (b.get_type() == Block_type::LIGHT && b.is_light_on())) {
                DrawRectangle(
                    pos.x + 16,
                    pos.y + 12,
                    block_size.x - 32,
                    block_size.y - 24,
                    YELLOW
                ); 
            }
            else if (b.get_type() == Block_type::SWITCH || b.get_type() == Block_type::LIGHT) {
                DrawRectangle(
                    pos.x + 16,
                    pos.y + 12,
                    block_size.x - 32,
                    block_size.y - 24,
                    BLACK
                ); 
            }

            // draw centered text
            else {
                // copied from MeasureText in raylib

                constexpr int default_font_size {10};
                const char* text {b.get_type_text()};
                int font_size {20};
                if (font_size < default_font_size) {
                    font_size = default_font_size;
                }
                int spacing = font_size / default_font_size;
                Vector2 text_size {MeasureTextEx(GetFontDefault(), text, font_size, spacing)};
                Vector2 text_pos {
                    gate_center.x - (text_size.x / 2), 
                    gate_center.y - (text_size.y / 2)
                };
                DrawText(text, text_pos.x, text_pos.y, font_size, WHITE);
            }

            // light doesn't have output node
            if (b.get_type() != Block_type::LIGHT) {
                DrawCircle(
                    pos.x + block_size.x + b.get_node_radius(),
                    gate_center.y, b.get_node_radius(),
                    WHITE
                );
            }

            // NOT gates and lights only has one input node
            if (b.get_type() == Block_type::NOT || b.get_type() == Block_type::LIGHT) {
                DrawCircle(
                    pos.x - b.get_node_radius(),
                    gate_center.y,
                    b.get_node_radius(),
                    WHITE
                );
            }
            // all other gates have 2 input nodes
            // switch doesn't have input nodes
            else if (b.get_type() != Block_type::SWITCH) {
                DrawCircle(
                    pos.x - b.get_node_radius(),
                    pos.y + (block_size.y / 3),
                    b.get_node_radius(),
                    WHITE
                );
                DrawCircle(
                    pos.x - b.get_node_radius(),
                    pos.y + (2 * block_size.y / 3),
                    b.get_node_radius(),
                    WHITE
                );
            }
        }
    );
}

void rendering::draw_connections(Connection_tracker& connections)
{
    auto draw_connections {
        [](Connection& connection)
        {    
            Vector2 input_loc {};
            switch (connection.node) {
            case Input_node::TOP:
                input_loc = connection.output->get_top_input_loc();
                break;
            case Input_node::CENTER:
                input_loc = connection.output->get_center_input_loc();
                break;
            case Input_node::BOT:
                input_loc = connection.output->get_bot_input_loc();
                break;
            }

            Color connection_color {};
            if (connection.input->output_signal()) {
                connection_color = WHITE;
            }
            else {
                connection_color = GRAY;
            }

            DrawLineEx(
                input_loc,
                connection.input->get_ouput_loc(),
                line_thickness,
                connection_color
            );

        }
    };

    connections.for_each(draw_connections);
}
