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

#define SERVER_PORT 18010
#define BUFFER_SIZE 256
#define MAX_CLIENTS 3


// TCP server that use blocking sockets
int main()
{
    // Socket used for listening for new clients 
    SOCKET listenSocket = INVALID_SOCKET;

    SOCKET clientSockets[MAX_CLIENTS];
    int count_clients = 0;


    // Variable used to store function return value
    int iResult;

    // Buffer used for storing incoming data
    char dataBuffer[BUFFER_SIZE];

    // WSADATA data structure that is to receive details of the Windows Sockets implementation
    WSADATA wsaData;

    // Initialize windows sockets library for this process
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }


    // Initialize serverAddress structure used by bind
    sockaddr_in serverAddress;
    memset((char*)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;				// IPv4 address family
    serverAddress.sin_addr.s_addr = INADDR_ANY;		// Use all available addresses
    serverAddress.sin_port = htons(SERVER_PORT);	// Use specific port

    memset(clientSockets, 0, MAX_CLIENTS * sizeof(SOCKET));


    // Create a SOCKET for connecting to server
    listenSocket = socket(AF_INET,      // IPv4 address family
        SOCK_STREAM,  // Stream socket
        IPPROTO_TCP); // TCP protocol

    // Check if socket is successfully created
    if (listenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket - bind port number and local address to socket
    iResult = bind(listenSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Check if socket is successfully binded to address and port from sockaddr_in structure
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    bool bOptVal = true;
    int bOptLen = sizeof(bool);
    iResult = setsockopt(listenSocket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&bOptVal, bOptLen);
    if (iResult == SOCKET_ERROR) {
        printf("setsockopt for SO_CONDITIONAL_ACCEPT failed with error: %u\n", WSAGetLastError());
    }

    unsigned long  mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != 0)
        printf("ioctlsocket failed with error.");

    // Set listenSocket in listening mode
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server socket is set to listening mode. Waiting for new connection requests.\n");
    fd_set readfds;
    timeval timeVal;
    timeVal.tv_sec = 1;
    timeVal.tv_usec = 0;

    while (true)
    {
        FD_ZERO(&readfds);

        if (count_clients != MAX_CLIENTS) {
            FD_SET(listenSocket, &readfds);
        }

        for (int i = 0;i < MAX_CLIENTS;i++) {
            FD_SET(clientSockets[i], &readfds);
        }

        int sResult = select(0, &readfds, NULL, NULL, &timeVal);

        if (sResult == SOCKET_ERROR)
        {
            printf("Select failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }
        else if (sResult == 0) // timeout expired
        {
            if (_kbhit()) //check if some key is pressed
            {
                getch();
                printf("Primena racunarskih mreza u infrstrukturnim sistemima 2019/2020\n");
            }
            continue;
        }
        else if (FD_ISSET(listenSocket, &readfds))
        {
            sockaddr_in clientAddr;
            int clientAddrSize = sizeof(struct sockaddr_in);

            clientSockets[count_clients] = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

            if (clientSockets[count_clients] == INVALID_SOCKET)
            {
                if (WSAGetLastError() == WSAECONNRESET)
                {
                    printf("accept failed, because timeout for client request has expired.\n");
                }
                else
                {
                    printf("accept failed with error: %d\n", WSAGetLastError());
                }
            }
            else
            {
                if (ioctlsocket(clientSockets[count_clients], FIONBIO, &mode) != 0)
                {
                    printf("ioctlsocket failed with error.");
                    continue;
                }
                count_clients++;
                printf("New client request accepted (%d). Client address: %s : %d\n", count_clients, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

            }
        }
        else {

        }


    };


    //Close listen and accepted sockets
    closesocket(listenSocket);

    // Deinitialize WSA library
    WSACleanup();

    return 0;
}