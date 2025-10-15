#include "tcpClient.h"

int tcpClient() {

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

	SOCKET clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "socket() is OK" << std::endl;
	}

	connectSocket(clientSocket);

	sendMessage(clientSocket);

	closeAll(clientSocket);

	return 0;
}

static void closeAll(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
}

int connectSocket(SOCKET clientSocket)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(54000);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "Client: connect() - Failed to connect" << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "Connected" << std::endl;
	}
}

void sendMessage(SOCKET clientSocket) {
	char buffer[200];
	printf("Enter your message ");
	std::cin.getline(buffer, 200);
	int byteCount = send(clientSocket, buffer, 200, 0);
	if (byteCount == SOCKET_ERROR) {
		printf("Server send error %ld.\n", WSAGetLastError());
		return;
	}
	else {
		printf("Server: sent %ld bytes \n", byteCount);
	}
}