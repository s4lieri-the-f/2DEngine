#include "ocean_sample/logic.hpp"
#include "networking/client.hpp"
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <width> <height>" << std::endl;
        return 1;
    }
    asio::io_context ioContext;
    WebSocketClient client(ioContext);
    client.connect("localhost", "8080", SERVER);
    Ocean ocean = Ocean(argv[1], argv[2]);

    while (true)
    {
        ocean.update();
        std::string grid = get_grid();
        client.send(grid);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}