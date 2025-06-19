#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.hpp"
int main(void)
{
	WSAInitializer wsa;
	try
	{
		Server server;
		std::cout << "Server Running on Port 17423" << std::endl;

		server.run();
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what();
	}
	return 0;
}