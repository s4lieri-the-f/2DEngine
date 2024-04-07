#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;

enum Type
{
    SERVER,
    VIEWER
}

class WebSocketServer
{
public:
    WebSocketServer(asio::io_context& ioContext, const tcp::endpoint& endpoint)
        : acceptor_(ioContext, endpoint), socket_(ioContext) {
        startAccept();
    }

private:
    void startAccept() {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<WebSocketSession>(std::move(socket_))->start();
            }
            startAccept();
        });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
public:
    WebSocketSession(tcp::socket socket) : ws_(std::move(socket)) {}
    Type type;
    void start() {
        ws_.async_accept([self = shared_from_this()](boost::system::error_code ec) {
            if (!ec) {
                self->read();
                if (type == SERVER)
                {
                    self->type = SERVER;
                }
                else
                {
                    self->type = VIEWER;
            }
        });
    }

private:
    void read() {
        ws_.async_read(buffer_, [self = shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (!ec) {
                // Process the received message
                std::string message(beast::buffers_to_string(self->buffer_.data()));
                std::cout << "Received message: " << message << std::endl;

                self->write(message);
            }
        });
    }

    void write(const std::string& message) {
        ws_.async_write(asio::buffer(message), [self = shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred) {
            if (!ec) {
                self->read();
            }
        });
    }

    beast::websocket::stream<tcp::socket> ws_;
    beast::flat_buffer buffer_;
};

