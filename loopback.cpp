#include "ocean_sample/test_logic.hpp"
#include "networking/client.hpp"
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <width> <height>" << std::endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));
    asio::io_context ioContext;
    WebSocketClient client(ioContext);
    client.connect("localhost", "8080", SERVER);
    Ocean ocean(10, 10);

    for (int i = 0; i < 10; ++i)
    {
        ocean.addEntity(rand() % 10, rand() % 10, std::make_shared<GoodCarp>());
    }

    for (int i = 0; i < 3; ++i)
    {
        ocean.addEntity(rand() % 10, rand() % 10, std::make_shared<BadCarp>());
    }
    for (int i = 0; i < 5; ++i)
    {
        ocean.addEntity(rand() % 10, rand() % 10, std::make_shared<Rock>());
    }

    while (true)
    {
        ocean.tick();
        auto map = ocean.generate_map();
        client.send(map);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}