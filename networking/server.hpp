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
    WebSocketServer(asio::io_context &ioContext, const tcp::endpoint &endpoint)
        : acceptor_(ioContext, endpoint), socket_(ioContext)
    {
        startAccept();
    }

    void broadcastToClients(const std::string &message)
    {
        for (auto &session : sessions_)
        {
            if (session->type == Type::VIEWER)
            {
                session->write(message);
            }
        }
    }

private:
    void startAccept()
    {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
                               {
            if (!ec) {
                auto session = std::make_shared<WebSocketSession>(std::move(socket_), *this);
                sessions_.insert(session);
                session->start();
            }
            startAccept(); });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::set<std::shared_ptr<WebSocketSession>> sessions_;
};

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession>
{
public:
    WebSocketSession(tcp::socket socket, WebSocketServer &server)
        : ws_(std::move(socket)), server_(server) {}

    void start()
    {
        ws_.async_accept([self = shared_from_this()](boost::system::error_code ec)
                         {
            if (!ec) {
                self->read();
            } });
    }

    void write(const std::string &message)
    {
        ws_.async_write(asio::buffer(message), [self = shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred)
                        {
            if (!ec) {
                self->read();
            } });
    }

private:
    void read()
    {
        ws_.async_read(buffer_, [self = shared_from_this()](boost::system::error_code ec, std::size_t bytesTransferred)
                       {
            if (!ec) {
                std::string message(beast::buffers_to_string(self->buffer_.data()));
                std::cout << "New grid: " << message << std::endl;

                if (self->type == Type::SERVER) {
                    self->server_.broadcastToClients(message);
                }

                self->write(message);
            } });
    }

    beast::websocket::stream<tcp::socket> ws_;
    beast::flat_buffer buffer_;
    WebSocketServer &server_;
};