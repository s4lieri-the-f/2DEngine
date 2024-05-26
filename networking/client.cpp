#include <boost/asio.hpp>
#include "../graphical_engine/render.hpp"
#include <iostream>
#include <thread>
#include <cmath>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TCPClient
{
public:
    TCPClient(asio::io_context &ioContext)
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
        auto ep = asio::connect(socket_, results);

        std::cout << "[DEBUG] Connected to: " << ep.address().to_string() << ":" << ep.port() << std::endl;
    }

    std::string read()
    {
        asio::streambuf buffer;
        std::cout << "[DEBUG] Waiting to read message..." << std::endl;
        try
        {
            // Check if the socket is open before reading
            if (!socket_.is_open())
            {
                throw std::runtime_error("Socket is not open");
            }

            // Perform the read operation
            asio::read_until(socket_, buffer, '\n');
            std::istream is(&buffer);
            std::string message;
            std::getline(is, message);
            std::cout << "[DEBUG] Message received: " << message << std::endl;
            return message;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[ERROR] Read error: " << e.what() << std::endl;
            throw;
        }
    }

private:
    asio::io_context &ioContext_;
    tcp::resolver resolver_;
    tcp::socket socket_;
};

int main(int argc, char **argv)
{
    try
    {
        glutInit(&argc, argv);
        asio::io_context ioContext;
        TCPClient client(ioContext);
        client.connect("0.0.0.0", "8080");

        std::string grid = client.read();
        int size = 10;
        int **int_grid = new int *[size];
        for (int i = 0; i < size; ++i)
        {
            int_grid[i] = new int[size];
            for (int j = 0; j < size; ++j)
            {
                int_grid[i][j] = 0;
            }
        }

        Window window(size, int_grid);
        window.run();

        while (true)
        {
            std::string grid = client.read();
            for (int i = 0; i < size; ++i)
            {
                int_grid[i] = new int[size];
                for (int j = 0; j < size; ++j)
                {
                    int_grid[i][j] = (int)grid[i * size + j] - (int)'0';
                }
            }
            window.grid = int_grid;
            window.currentGrid = int_grid;
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    std::cerr << window.grid[i][j] << " ";
                }
                std::cerr << std::endl;
            }
            window.updateGrid(int_grid);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
