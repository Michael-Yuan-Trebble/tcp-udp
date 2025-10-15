#include "tcpServer.h"

void tcpServer() 
{
	WSADATA wsaData;
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) { std::cout << "The Winsock dll not found!" << std::endl; return; }

	std::cout << "Winsock dll found" << std::endl;
	std::cout << "The Status: " << wsaData.szSystemStatus << std::endl;

	SOCKET serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) 
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	
	std::cout << "socket() is OK" << std::endl;

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, IPADDRESS, &service.sin_addr.s_addr);
	service.sin_port = htons(54000);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
	{
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		closeAll(serverSocket);
		return;
	}

	std::cout << "bind() is Ok" << std::endl;

	if (listen(serverSocket, 1) == SOCKET_ERROR) { std::cout << "listen(): Error listening on socket: " << WSAGetLastError() << std::endl; }
	else { std::cout << "listen() is ok, waiting for connections..." << std::endl; }

	SOCKET clientSocket = acceptSocket(serverSocket);

	if (clientSocket == INVALID_SOCKET) { closeAll(serverSocket); return; }

	recieveInput(serverSocket, clientSocket);

	closeAll(serverSocket);
	return;
}

SOCKET acceptSocket(SOCKET serverSocket) 
{
	SOCKET acceptSocket;
	sockaddr_in clientAddr;
	int clientSize = sizeof(clientAddr);
	acceptSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
	if (acceptSocket == INVALID_SOCKET) 
	{
		std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return INVALID_SOCKET;
	}

	std::cout << "Client connected" << std::endl;

	return acceptSocket;
}

void recieveInput(SOCKET serverSocket, SOCKET clientSocket)
{
	char buffer[1024] = { 0 };
	int bytesRecieved = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesRecieved > 0) 
	{
		buffer[bytesRecieved] = '\0';
		int num = std::stoi(buffer);
		std::cout << "Recieved number: " << num << std::endl;

		int counterNum = rollCounterDice();
		int result = 0;

		if (num > counterNum) 
		{
			result = num - counterNum;
			std::cout << "Client's roll was higher by: " << counterNum << std::endl;
			result = htonl(result);
			send(clientSocket, reinterpret_cast<char*>(&result), sizeof(result), 0);
			return;
		}
		else 
		{
			result = counterNum - num;
			std::cout << "Server's roll was higher by: " << counterNum << std::endl;
			result = htonl(result);
			send(clientSocket, reinterpret_cast<char*>(&result), sizeof(result), 0);
			return;
		}
		std::cout << "Equal Rolls " << std::endl;
		send(clientSocket, reinterpret_cast<char*>(&result), sizeof(result), 0);
	}
}

int rollCounterDice()
{
	int num;
	while (true)
	{
		std::cout << "Enter an Integer: ";
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid Input, please input an Integer\n";
		}
		else break;
	}

	unsigned seed = static_cast<unsigned>(std::time(nullptr));
	std::mt19937 ran(seed);
	std::uniform_int_distribution<int> dist(1, num);
	int ranNum = dist(ran);

	return ranNum;
}

static void closeAll(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
}