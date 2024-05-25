#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;


enum Type{
    SERVER,
    VIEWER
}
class WebSocketClient
{
public:
    Type type;
    WebSocketClient(asio::io_context &ioContext)
        : ioContext_(ioContext),
          resolver_(ioContext),
          socket_(ioContext)
    {
    }

    void connect(const std::string &host, const std::string &port, Type type): type(type)
    {
        resolver_.async_resolve(host, port,
                                [this](const boost::system::error_code &ec, const asio::ip::tcp::resolver::results_type &results)
                                {
                                    if (!ec)
                                    {
                                        asio::async_connect(socket_.next_layer(), results.begin(), results.end(),
                                                            [this](const boost::system::error_code &ec, const asio::ip::tcp::endpoint & /*endpoint*/)
                                                            {
                                                                if (!ec)
                                                                {
                                                                    socket_.async_handshake(host, "/",
                                                                                            [this](const boost::system::error_code &ec)
                                                                                            {
                                                                                                if (!ec)
                                                                                                {
                                                                                                    std::cout << "[DEBUG] Connected to server." << std::endl;
                                                                                                    send(type == SERVER ? "SERVER" : "VIEWER")
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    std::cout << "[ERROR] Handshake failed: " << ec.message() << std::endl;
                                                                                                }
                                                                                            });
                                                                }
                                                                else
                                                                {
                                                                    std::cout << "[ERROR] Connection failed: " << ec.message() << std::endl;
                                                                }
                                                            });
                                    }
                                    else
                                    {
                                        std::cout << "[ERROR] Resolve failed: " << ec.message() << std::endl;
                                    }
                                });

        ioContext_.run();
    }

    void send(const std::string &message)
    {
        socket_.async_write(asio::buffer(message),
                            [this](const boost::system::error_code &ec, std::size_t /*bytes_transferred*/)
                            {
                                if (ec)
                                {
                                    std::cout << "Write error." << std::endl;
                                }
                            });
    }

    std::string receive()
    {
        socket_.async_read(buffer_,
                           [this](const boost::system::error_code &ec, std::size_t /*bytes_transferred*/)
                           {
                               if (!ec)
                               {
                                    std::string message = beast::buffers_to_string(buffer_.data());
                                    buffer_.consume(buffer_.size());
                                    return message;

                               }
                               else
                               {
                                   std::cout << "Read error." << std::endl;
                                   return "ERROR";
                               }
                           });
    }

private:
    asio::io_context &ioContext_;
    asio::ip::tcp::resolver resolver_;
    websocket::stream<asio::ip::tcp::socket> socket_;
    beast::flat_buffer buffer_;
};