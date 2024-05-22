#include "networking/client.hpp"
#include "graphical_engine/render.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }

    asio::io_context ioContext;
    WebSocketClient client(ioContext);
    client.connect(argv[1], argv[2], Type::CLIENT);
    std::string grid = client.receive();

    Window window(grid);

    while (true)
    {
        std::string grid = client.receive();
        window.updateGrid(grid);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}