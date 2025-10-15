#include "tcpServer.h"

int tcpServer() {

	WSADATA wsaData;
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		std::cout << "The Winsock dll not found!" << std::endl;
		return 0;
	}
	else {
		std::cout << "Winsock dll found" << std::endl;
		std::cout << "The Status: " << wsaData.szSystemStatus << std::endl;
	}

	SOCKET serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "socket() is OK" << std::endl;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, "127.0.0.1", &service.sin_addr.s_addr);
	service.sin_port = htons(54000);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		closeAll(serverSocket);
		return 0;
	}
	else {
		std::cout << "bind() is Ok" << std::endl;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "listen(): Error listening on socket: " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "listen() is ok, waiting for connections..." << std::endl;
	}

	acceptSocket(serverSocket);

	closeAll(serverSocket);

	return 0;
}

int acceptSocket(SOCKET serverSocket) 
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
		return -1;
	}
	std::cout << "Client connected" << std::endl;
}

static void closeAll(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
}