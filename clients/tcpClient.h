#pragma once
#pragma comment(lib,"Ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

int tcpClient();
static void closeAll(SOCKET inSocket);
int connectSocket(SOCKET inSocket);

void sendMessage(SOCKET inSocket);