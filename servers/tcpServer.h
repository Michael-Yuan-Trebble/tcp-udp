#pragma once
#pragma comment(lib,"Ws2_32.lib")

#define NOMINMAX
#define IPADDRESS "127.0.0.1"
#include <iostream>
#include <random>
#include <ctime>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

void tcpServer();
static void closeAll(SOCKET inSocket);
SOCKET acceptSocket(SOCKET inSocket);

void recieveInput(SOCKET inSocket, SOCKET inSocket2);
int rollCounterDice();