#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code &)
{
	std::cout << "I have been called in the past, but here I am.\n";
}
int main()
{
	boost::asio::io_context io;
	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(3));
	t.async_wait(&print);
	io.run();
	return 0;
}
