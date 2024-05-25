#pragma once

#include <boost/asio>
#include <boost/beast>
#include <boost/beast/websocket>
#include <iostream>
#include "networking/server.hpp"

int main()
{
    try
    {
        asio::io_context ioContext;
        tcp::endpoint endpoint(tcp::v4(), 8080);
        WebSocketServer server(ioContext, endpoint);
        ioContext.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}