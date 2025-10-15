#include "Connect.h"
#include "./servers/tcpServer.h"
#include "./clients/tcpClient.h"

void runServer() 
{
	tcpServer();
}

void runClient() 
{
	tcpClient();
}

int main()
{
	std::thread serverThread(runServer);

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::thread clientThread(runClient);

	serverThread.join();
	clientThread.join();

	return 0;
}