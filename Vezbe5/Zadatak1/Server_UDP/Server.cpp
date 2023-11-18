// UDP server that use non-blocking sockets
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define SERVER_PORT 15011	// Port number of server that will be used for communication with clients
#define SERVER_PORT2 15012	// Port number of server that will be used for communication with clients
#define BUFFER_SIZE 512		// Size of buffer that will be used for sending and receiving messages to clients

int main()
{
	// Server address
	sockaddr_in serverAddress;
	sockaddr_in serverAddress2;


	// Buffer we will use to send and receive clients' messages
	char dataBuffer[BUFFER_SIZE];

	// WSADATA data structure that is to receive details of the Windows Sockets implementation
	WSADATA wsaData;

	// Initialize windows sockets library for this process
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	// Initialize serverAddress structure used by bind function
	memset((char*)&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET; 			// set server address protocol family
	serverAddress.sin_addr.s_addr = INADDR_ANY;		// use all available addresses of server
	serverAddress.sin_port = htons(SERVER_PORT);

	memset((char*)&serverAddress2, 0, sizeof(serverAddress2));
	serverAddress2.sin_family = AF_INET; 			// set server address protocol family
	serverAddress2.sin_addr.s_addr = inet_addr("127.0.0.1");		// use all available addresses of server
	serverAddress2.sin_port = htons(SERVER_PORT2);

	// Create a socket
	SOCKET serverSocket = socket(AF_INET,      // IPv4 address famly
		SOCK_DGRAM,   // datagram socket
		IPPROTO_UDP); // UDP

	SOCKET serverSocket2 = socket(AF_INET,      // IPv4 address famly
		SOCK_DGRAM,   // datagram socket
		IPPROTO_UDP); // UDP

	// Check if socket creation succeeded
	if (serverSocket == INVALID_SOCKET)
	{
		printf("Creating socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	if (serverSocket2 == INVALID_SOCKET)
	{
		printf("Creating socket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Bind server address structure (type, port number and local address) to socket
	int iResult = bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress));



	// Check if socket is succesfully binded to server datas
	if (iResult == SOCKET_ERROR)
	{
		printf("Socket bind failed with error: %d\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	iResult = bind(serverSocket2, (SOCKADDR*)&serverAddress2, sizeof(serverAddress2));
	if (iResult == SOCKET_ERROR)
	{
		printf("Socket bind failed with error: %d\n", WSAGetLastError());
		closesocket(serverSocket2);
		WSACleanup();
		return 1;
	}

	printf("Simple UDP server started and waiting client messages.\n");

	// Declare and initialize client address that will be set from recvfrom


	//set serverSocket in nonblocking mode 
	unsigned long  mode = 1;
	if (ioctlsocket(serverSocket, FIONBIO, &mode) != 0 || ioctlsocket(serverSocket2, FIONBIO, &mode) != 0)
	{
		printf("ioctlsocket failed with error %d\n", WSAGetLastError());
		closesocket(serverSocket);
		closesocket(serverSocket2);
		WSACleanup();
		return 1;
	}
	// Main server loop
	while (true)
	{
		sockaddr_in clientAddress;
		memset(&clientAddress, 0, sizeof(clientAddress));

		// Set whole buffer to zero
		memset(dataBuffer, 0, BUFFER_SIZE);

		// size of client address
		int sockAddrLen = sizeof(clientAddress);

		fd_set readfds;
		FD_ZERO(&readfds);

		FD_SET(serverSocket, &readfds);
		FD_SET(serverSocket2, &readfds);



	}

	// Close server application
	iResult = closesocket(serverSocket);

	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	iResult = closesocket(serverSocket2);

	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	printf("Server successfully shut down.\n");

	// Close Winsock library
	WSACleanup();

	return 0;
}