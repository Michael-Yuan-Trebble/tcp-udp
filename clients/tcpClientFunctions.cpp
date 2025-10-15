#include "tcpClientFunctions.h"

void tcpClientFunctions(SOCKET clientSocket)
{
	int num = rollDice();
	std::cout << "Random num: " << num << std::endl;

	std::string msg = std::to_string(num);

	int byteCount = send(clientSocket, msg.c_str(), msg.size(), 0);
	std::cout << "Sent: " << num << " with size: " << msg.size() << std::endl;

	int result;
	recv(clientSocket, reinterpret_cast<char*>(&result), sizeof(result), 0);
	result = ntohl(result);
	std::cout << "Server returned: " << result << std::endl;
}

int rollDice() 
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