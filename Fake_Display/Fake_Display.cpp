// Fake_Display.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <WS2tcpip.h>
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
#pragma comment(lib, "Ws2_32.lib")
using namespace std;



int main(int argc, char* argv[])
{

	//step 1:
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		cout << "winsock 2.2 is not supported";
		return 0;
	}

	//step 2:
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET) {
		cout << "error " << WSAGetLastError() << ": cannot creat server socket";
		return 0;
	}

	// step 3
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	/*if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
		cout << "error " << WSAGetLastError() << ": cannot associate a local address whit srver socket ";
		return 0;
	}
	*/

	// step 4:
	if (listen(listenSock, 10)) {
		cout << "error " << WSAGetLastError() << ": cannot place server socket in state LISTEN.";
		return 0;
	}

	cout << "server started! " << endl;

	while (1) {
		// step 5:
		sockaddr_in clientAddr;
		char buff[BUFF_SIZE], clientIP[INET_ADDRSTRLEN];
		int ret, clientAddrLen = sizeof(clientAddr), clientPort;
		SOCKET connSock;
		// accept request
		connSock = accept(listenSock, (sockaddr*)&clientAddr, &clientAddrLen);
		if (connSock == SOCKET_ERROR) {
			cout << "error " << WSAGetLastError() << ": cannot permit incoming connection";
			return 0;
		}
		else {
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
			clientPort = ntohs(clientAddr.sin_port);
			cout << "accept incoming connection from " << clientIP << " " << clientPort << endl;
		}
		while (1)
		{
			// receive message from client
			ret = recv(connSock, buff, BUFF_SIZE, 0);
			if (ret == SOCKET_ERROR) {
				cout << "error " << WSAGetLastError() << ": cannot receive data";
				break;
			}
			else if (ret == 0) {
				cout << "client disconnects " << endl;
				break;
			}
			else {
				buff[ret] = 0;
				printf("Receive from client[%s:%d] %s\n", clientIP, clientPort, buff);
			}
		}// end communicating 

		closesocket(connSock);//close connSock
	}//close server

	//step 5
	closesocket(listenSock);

	//step 6
	WSACleanup();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
