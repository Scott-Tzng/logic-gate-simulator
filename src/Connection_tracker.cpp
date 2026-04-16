#include "Connection_tracker.hpp"

#include <algorithm>

void Connection_tracker::add_connection(Block* input, Block* output, Input_node node)
{
    // LIGHT blocks should not have more than one input
    if (output->get_type() == Block_type::LIGHT) {
        // check all the connections and make sure that there isn't already 
        // a connection that contains output

        for (Connection& connection : m_connections) {
            if (connection.output == output) {
                return;
            }
        }
    }

    m_connections.push_back(Connection{input, output, node});
}

void Connection_tracker::for_each(void (*func)(Connection&))
{
    std::for_each(m_connections.rbegin(), m_connections.rend(), func);
}

std::list<Connection>::iterator Connection_tracker::find_if(bool (*cond)(Connection&), bool& found)
{
    auto iter {std::find_if(m_connections.begin(), m_connections.end(), cond)};
    found = iter != m_connections.end();
    return iter;
}

void Connection_tracker::delete_connection(std::list<Connection>::iterator iter)
{
    m_connections.erase(iter);
}

void Connection_tracker::delete_connecitons_with(const Block* block)
{
    m_connections.remove_if(
        [block](const Connection& c)
        {
            // needed so that connections don't just remain in their previous state
            c.output->recieve_top_signal(false);
            c.output->recieve_bot_signal(false);

            return block == c.input || block == c.output;
        }
    );
}

void Connection_tracker::transmit_signals()
{
    for (auto& connection : m_connections) {
        if (connection.node == Input_node::TOP || connection.node == Input_node::CENTER) {
            connection.output->recieve_top_signal(connection.input->output_signal());
        }
        else {
            connection.output->recieve_bot_signal(connection.input->output_signal());
        }
    }
}
