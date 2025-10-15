#include "tcpClient.h"
#include "tcpClientFunctions.h"

void tcpClient() 
{
	WSADATA wsaData;
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		std::cout << "The Winsock dll not found!" << std::endl;
		return;
	}
	std::cout << "Winsock dll found" << std::endl;
	std::cout << "The Status: " << wsaData.szSystemStatus << std::endl;

	SOCKET clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) 
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	std::cout << "socket() is OK" << std::endl;

	connectSocket(clientSocket);
	tcpClientFunctions(clientSocket);

	closeAll(clientSocket);

	return;
}

static void closeAll(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
}

void connectSocket(SOCKET clientSocket)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, IPADDRESS, &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(54000);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) 
	{
		std::cout << "Client: connect() - Failed to connect" << std::endl;
		WSACleanup();
		return;
	}
	
	std::cout << "Connected" << std::endl;
}