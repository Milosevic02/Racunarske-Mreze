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

#define BUFFER_SIZE 512		// Size of buffer that will be used for sending and receiving messages to clients

int main()
{
	// Server address
	sockaddr_in serverAddress;
	sockaddr_in serverAddress2;


	// Buffer we will use to send and receive clients' messages
	char dataBuffer[BUFFER_SIZE];
	char dataBuffer2[BUFFER_SIZE];

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
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");		// use all available addresses of server
	serverAddress.sin_port = htons((unsigned short)17010);

	// Initialize serverAddress structure used by bind function
	memset((char*)&serverAddress2, 0, sizeof(serverAddress2));
	serverAddress2.sin_family = AF_INET; 			// set server address protocol family
	serverAddress2.sin_addr.s_addr = INADDR_ANY;		// use all available addresses of server
	serverAddress2.sin_port = htons((unsigned short)17011);

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
	int iResult2 = bind(serverSocket2, (SOCKADDR*)&serverAddress2, sizeof(serverAddress2));


	// Check if socket is succesfully binded to server datas
	if (iResult == SOCKET_ERROR)
	{
		printf("Socket bind failed with error: %d\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	printf("Simple UDP server started and waiting client messages.\n");

	// Declare and initialize client address that will be set from recvfrom
	sockaddr_in clientAddress;
	memset(&clientAddress, 0, sizeof(clientAddress));

	// Set whole buffer to zero
	memset(dataBuffer, 0, BUFFER_SIZE);

	// size of client address
	int sockAddrLen = sizeof(clientAddress);

	//set serverSocket in nonblocking mode 
	unsigned long  mode = 1;
	iResult = ioctlsocket(serverSocket, FIONBIO, &mode);
	iResult = ioctlsocket(serverSocket2, FIONBIO, &mode);

	if (iResult != 0)
		printf("ioctlsocket failed with error.");

	int NOATTEMPTS = 30; // if server has received no message in period of 30 seconds, then server is shutting down.

	int points1 = 0;
	int points2 = 0;

	// Main server loop
	while (true)
	{
		int i;

		printf("\nUDP server waiting for new messages\n");


		for (i = 0; i < NOATTEMPTS; i++)
		{
			// Receive client message
			iResult = recvfrom(serverSocket,	// Own socket
				dataBuffer,						// Buffer that will be used for receiving message
				BUFFER_SIZE,					// Maximal size of buffer
				0,								// No flags
				(SOCKADDR*)&clientAddress,		// Client information from received message (ip address and port)
				&sockAddrLen);					// Size of sockadd_in structure

			// Check if message is succesfully received, print message and continue waiting for new message
			if (iResult != SOCKET_ERROR)
			{
				// Set end of string
				dataBuffer[iResult] = '\0';

				char ipAddress[16]; // 15 spaces for decimal notation (for example: "192.168.100.200") + '\0'

				// Copy client ip to local char[]
				strcpy_s(ipAddress, sizeof(ipAddress), inet_ntoa(clientAddress.sin_addr));

				// Convert port number from network byte order to host byte order
				unsigned short clientPort = ntohs(clientAddress.sin_port);
				printf("Client (ip: %s, port: %d,points:%d) sent: %s.\n", ipAddress, clientPort, dataBuffer,++points1);
				break;
			}
			else
			{
				// if recvfrom function returns WSAEWOULDBLOCK error,
				// nonblocking mode for socket is set and no data has received yet. 
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					Sleep(1500);
				}
				// some error occured during message receive, close server
				else
				{
					printf("recvfrom failed with error: %d\n", WSAGetLastError());
					iResult = closesocket(serverSocket);
					WSACleanup();
					return 1;
				}
			}


			iResult2 = recvfrom(serverSocket2,	// Own socket
				dataBuffer2,						// Buffer that will be used for receiving message
				BUFFER_SIZE,					// Maximal size of buffer
				0,								// No flags
				(SOCKADDR*)&clientAddress,		// Client information from received message (ip address and port)
				&sockAddrLen);					// Size of sockadd_in structure

			// Check if message is succesfully received, print message and continue waiting for new message
			if (iResult2 != SOCKET_ERROR)
			{
				// Set end of string
				dataBuffer2[iResult2] = '\0';

				char ipAddress[16]; // 15 spaces for decimal notation (for example: "192.168.100.200") + '\0'

				// Copy client ip to local char[]
				strcpy_s(ipAddress, sizeof(ipAddress), inet_ntoa(clientAddress.sin_addr));

				// Convert port number from network byte order to host byte order
				unsigned short clientPort = ntohs(clientAddress.sin_port);
				printf("Client (ip: %s, port: %d,points:%d) sent: %s.\n", ipAddress, clientPort, dataBuffer2,++points2);
				break;
			}
			else
			{
				// if recvfrom function returns WSAEWOULDBLOCK error,
				// nonblocking mode for socket is set and no data has received yet. 
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					Sleep(1500);
				}
				// some error occured during message receive, close server
				else
				{
					printf("recvfrom failed with error: %d\n", WSAGetLastError());
					iResult2 = closesocket(serverSocket);
					WSACleanup();
					return 1;
				}
			}


		}
		if (i == NOATTEMPTS)
		{
			break;
		}
	}

	// Close server application
	iResult = closesocket(serverSocket);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	iResult2 = closesocket(serverSocket2);
	if (iResult2 == SOCKET_ERROR)
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