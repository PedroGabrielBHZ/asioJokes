#include <array>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string serializeTicker()
{
    std::time_t now = time(0);
    return std::ctime(&now);
}

int main()
{
    try
    {
        boost::asio::io_context io_context;

        udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

        for (;;)
        {
            std::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;
            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

            std::string message = serializeTicker();

            boost::system::error_code ignored_error;
            socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}