#include <iostream>
#include "graphical_engine/render.hpp"
#include "networking/client.cpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <cmath>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }
    asio::io_context ioContext;
    WebSocketClient client(ioContext);
    client.connect(argv[1], argv[2]);
    std::string grid = client.receive();
    int size = std::sqrt(grid.length());
    int **int_grid = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        int_grid[i] = new int[size];
        for (int j = 0; j < size; ++j)
        {
            int_grid[i][j] = grid[i * size + j] - '0';
        }
    }
    Window window(size, int_grid);

    while (true)
    {
        std::string grid = client.receive();
        for (int i = 0; i < size; ++i)
        {
            int_grid[i] = new int[size];
            for (int j = 0; j < size; ++j)
            {
                int_grid[i][j] = grid[i * size + j] - '0';
            }
        }
        window.updateGrid(int_grid);
        window.display();
    }

    return 0;
}
