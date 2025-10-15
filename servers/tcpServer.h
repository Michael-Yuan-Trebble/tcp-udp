#pragma once
#pragma comment(lib,"Ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

int tcpServer();
static void closeAll(SOCKET inSocket);
int acceptSocket(SOCKET inSocket);