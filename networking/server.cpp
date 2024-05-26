#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using boost::system::error_code;

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession>
{
public:
    explicit WebSocketSession(tcp::socket socket)
        : ws_(std::move(socket)) {}

    void run()
    {
        std::cout << "[DEBUG] Starting async_accept" << std::endl;
        ws_.async_accept(beast::bind_front_handler(&WebSocketSession::on_accept, shared_from_this()));
    }

    void send(const std::string &message)
    {
        ws_.async_write(net::buffer(message),
                        beast::bind_front_handler(&WebSocketSession::on_write, shared_from_this()));
    }

private:
    websocket::stream<tcp::socket> ws_;
    beast::flat_buffer buffer_;

    void on_accept(error_code ec)
    {
        if (ec)
        {
            std::cerr << "[ERROR] Accept error: " << ec.message() << "\n";
            return;
        }
        std::cout << "[DEBUG] Handshake successful" << std::endl;
        do_read();
    }

    void do_read()
    {
        ws_.async_read(buffer_,
                       beast::bind_front_handler(&WebSocketSession::on_read, shared_from_this()));
    }

    void on_read(error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
        {
            std::cerr << "[ERROR] Read error: " << ec.message() << "\n";
            return;
        }

        std::cout << "[DEBUG] Message received: " << beast::buffers_to_string(buffer_.data()) << std::endl;
        buffer_.consume(buffer_.size());
        do_read();
    }

    void on_write(error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
        {
            std::cerr << "[ERROR] Write error: " << ec.message() << "\n";
            return;
        }
        std::cout << "[DEBUG] Message sent successfully" << std::endl;
    }
};

class WebSocketServer
{
public:
    WebSocketServer(net::io_context &ioc, tcp::endpoint endpoint)
        : acceptor_(ioc, endpoint)
    {
        std::cout << "[DEBUG] Server is listening on " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;
        do_accept();
    }

    void broadcast(const std::string &message)
    {
        for (auto &session : sessions_)
        {
            session->send(message);
        }
    }

private:
    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<WebSocketSession>> sessions_;

    void do_accept()
    {
        acceptor_.async_accept(
            [this](error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    std::cout << "[DEBUG] Accepted connection from " << socket.remote_endpoint() << std::endl;
                    auto session = std::make_shared<WebSocketSession>(std::move(socket));
                    sessions_.push_back(session);
                    session->run();
                }
                else
                {
                    std::cerr << "[ERROR] Accept error: " << ec.message() << std::endl;
                }
                do_accept();
            });
    }
};
#ifdef TEST
int main()
{
    try
    {
        net::io_context ioc;
        tcp::endpoint endpoint{tcp::v4(), 8081};
        WebSocketServer server(ioc, endpoint);

        std::thread server_thread([&ioc]()
                                  { ioc.run(); });

        server_thread.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
#endif
