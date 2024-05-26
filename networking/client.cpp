#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include "../graphical_engine/render.hpp"
#include <iostream>
#include <thread>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp;

class WebSocketClient
{
public:
    WebSocketClient(asio::io_context &ioContext)
        : ioContext_(ioContext),
          resolver_(ioContext),
          socket_(ioContext)
    {
    }

    void connect(const std::string &host, const std::string &port)
    {
        std::cout << "[DEBUG] Resolving host: " << host << " and port: " << port << std::endl;
        auto const results = resolver_.resolve(host, port);

        std::cout << "[DEBUG] Attempting to connect..." << std::endl;
        auto ep = asio::connect(socket_.next_layer(), results);

        std::cout << "[DEBUG] Connected to: " << ep.address().to_string() << ":" << ep.port() << std::endl;

        // Perform the websocket handshake
        std::cout << "[DEBUG] Performing WebSocket handshake..." << std::endl;
        try
        {
            socket_.handshake(host, "/");
            std::cout << "[DEBUG] WebSocket handshake successful." << std::endl;
        }
        catch (const beast::system_error &e)
        {
            std::cerr << "[ERROR] WebSocket handshake failed: " << e.what() << std::endl;
        }
    }

    std::string read()
    {
        beast::flat_buffer buffer;
        std::cout << "[DEBUG] Waiting to read message..." << std::endl;
        socket_.read(buffer);
        std::string message = beast::buffers_to_string(buffer.data());
        std::cout << "[DEBUG] Message received: " << message << std::endl;
        return message;
    }

private:
    asio::io_context &ioContext_;
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> socket_;
};

int main()
{
    try
    {
        asio::io_context ioContext;
        WebSocketClient client(ioContext);
        client.connect("127.0.0.1", "8080");

        std::string grid = client.read();
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
            std::string grid = client.read();
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
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
