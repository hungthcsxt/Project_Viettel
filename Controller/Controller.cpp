// Controller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "conio.h"
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main(int argc, char* argv[]) {



	//step 1
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		cout << "winsock 2.2 is not supported" << endl;
		return 0;
	}

	//step 2
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		cout << "error " << WSAGetLastError() << ": cannot creat server socket";
		return 0;
	}

	// step 3
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	if (connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
		cout << "error " << WSAGetLastError() << ": cannot connect server";
		return 0;
	}
	cout << "connected server!" << endl;

	// step 5
	int ret, messageLen;
	cout << "Use the arrow keys to move the character " << endl;
	while (1) {
		//send
		if (GetAsyncKeyState(VK_UP)) {
			Sleep(500);
			char w[] = "w";
			messageLen = strlen(w);
			if (messageLen == 0)
				break;
			ret = send(client, w, messageLen, 0);
			if (ret == SOCKET_ERROR)
				cout << "error " << WSAGetLastError() << ": cannot send data";
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			Sleep(150);
			char s[] = "s";
			messageLen = strlen(s);
			if (messageLen == 0)
				break;
			ret = send(client, s, messageLen, 0);
			if (ret == SOCKET_ERROR)
				cout << "error " << WSAGetLastError() << ": cannot send data";
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			Sleep(150);
			char a[] = "a";
			messageLen = strlen(a);
			if (messageLen == 0)
				break;
			ret = send(client, a, messageLen, 0);
			if (ret == SOCKET_ERROR)
				cout << "error " << WSAGetLastError() << ": cannot send data";
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			Sleep(150);
			char d[] = "d";
			messageLen = strlen(d);
			if (messageLen == 0)
				break;
			ret = send(client, d, messageLen, 0);
			if (ret == SOCKET_ERROR)
				cout << "error " << WSAGetLastError() << ": cannot send data";
		}
	}

	// step 6
	closesocket(client);

	// step 7
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
