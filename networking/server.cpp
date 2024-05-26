#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace net = boost::asio;
using tcp = net::ip::tcp;
using error_code = boost::system::error_code;

class TCPServer
{
public:
    TCPServer(net::io_context &ioc, tcp::endpoint endpoint)
        : acceptor_(ioc, endpoint), socket_(ioc)
    {
        std::cout << "[DEBUG] Server is listening on " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
        do_accept();
    }

    void send(const std::string &message)
    {
        net::write(socket_, net::buffer(message + "\n"));
    }

    std::string read()
    {
        net::streambuf buffer;
        net::read_until(socket_, buffer, '\n');
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);
        return message;
    }
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    void do_accept()
    {
        std::cout << "[DEBUG] Waiting for a connection..." << std::endl;
        acceptor_.accept(socket_);
        std::cout << "[DEBUG] Accepted connection from " << socket_.remote_endpoint() << std::endl;
    }
};

#ifdef TEST
int main()
{
    try
    {
        net::io_context ioc;
        tcp::endpoint endpoint{tcp::v4(), 8080};
        TCPServer server(ioc, endpoint);

        // Example of server operations
        while (true)
        {
            std::string message = server.read();
            std::cout << "[DEBUG] Message received: " << message << std::endl;
            server.send("Echo: " + message);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
#endif
