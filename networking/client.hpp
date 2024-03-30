#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;

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
                                                                                                    // WebSocket handshake successful, do something
                                                                                                    // ... later
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    // Handle handshake error
                                                                                                    // ... later
                                                                                                }
                                                                                            });
                                                                }
                                                                else
                                                                {
                                                                    // Handle connection error
                                                                    // ... later
                                                                }
                                                            });
                                    }
                                    else
                                    {
                                        // Handle resolve error
                                        // ... later
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
                                    // Handle write error
                                    // ... later
                                }
                            });
    }

    void receive()
    {
        socket_.async_read(buffer_,
                           [this](const boost::system::error_code &ec, std::size_t /*bytes_transferred*/)
                           {
                               if (!ec)
                               {
                                   // Handle received message
                                   std::string message = beast::buffers_to_string(buffer_.data());
                                   buffer_.consume(buffer_.size());

                                   // Do something with the received message
                                   // ... later

                                   // Continue receiving
                                   // really good idea to make it recursive. ok.
                                   receive();
                               }
                               else
                               {
                                   // Handle read error
                                   // ... later
                               }
                           });
    }

private:
    asio::io_context &ioContext_;
    asio::ip::tcp::resolver resolver_;
    websocket::stream<asio::ip::tcp::socket> socket_;
    beast::flat_buffer buffer_;
};