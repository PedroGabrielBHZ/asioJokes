#include <array>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host1> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;

        // Define the target endpoint (localhost, port 14)
        boost::asio::ip::udp::endpoint receiver1_endpoint(boost::asio::ip::address::from_string(argv[1]), std::stoi(argv[2]));

        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> send_buf = {{0}};
        socket.send_to(boost::asio::buffer(send_buf), receiver1_endpoint);

        std::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(
            boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), len);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
