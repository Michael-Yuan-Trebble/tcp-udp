#pragma once
#pragma comment(lib,"Ws2_32.lib")

#define NOMINMAX
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

void tcpClientFunctions(SOCKET inSocket);
int rollDice();