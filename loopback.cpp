#include "ocean_sample/test_logic.cpp"
#include "networking/server.cpp"
#include <boost/asio.hpp>
#include <chrono>
#include <thread>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));
    net::io_context ioc{1};
    tcp::endpoint endpoint{tcp::v4(), 8080};
    TCPServer server(ioc, endpoint);
    Ocean ocean(600, 600);

    for (int i = 0; i < 30000; ++i)
    {
        ocean.addEntity(rand() % 600, rand() % 600, std::make_shared<GoodCarp>());
    }

    for (int i = 0; i < 5000; ++i)
    {
        ocean.addEntity(rand() % 600, rand() % 600, std::make_shared<BadCarp>());
    }
    for (int i = 0; i < 10000; ++i)
    {
        ocean.addEntity(rand() % 600, rand() % 600, std::make_shared<Rock>());
    }

    while (true)
    {
        ocean.tick();
        auto grid = ocean.generate_map();
        std::string grid_str;
        for (int i = 0; i < 600; ++i)
        {
            for (int j = 0; j < 600; ++j)
            {
                // std::cerr << grid[i][j] << " ";
                grid_str += std::to_string(grid[i][j]);
            }
            // std::cerr << std::endl;
        }
        try
        {
            server.send(grid_str);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[ERROR] Desconnected " << std::endl;
            server.acceptor_.close();
            server.do_accept();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}