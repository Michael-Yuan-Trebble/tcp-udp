#pragma once
#pragma comment(lib,"Ws2_32.lib")

#define IPADDRESS "127.0.0.1"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

void tcpClient();
static void closeAll(SOCKET inSocket);
void connectSocket(SOCKET inSocket);
void sendMessage(SOCKET inSocket);