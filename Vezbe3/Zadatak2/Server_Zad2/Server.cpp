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

#define SERVER_PORT 27016
#define BUFFER_SIZE 256

// TCP server that use blocking sockets
int main()
{
    // Socket used for listening for new clients 
    SOCKET listenSocket = INVALID_SOCKET;

    // Socket used for communication with client
    SOCKET acceptedSocket = INVALID_SOCKET;
    SOCKET acceptedSocket2 = INVALID_SOCKET;


    // Variable used to store function return value
    int iResult;
    int iResult2;

    bool wrong1 = false;
    bool wrong2 = false;

    // Buffer used for storing incoming data
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


    // Initialize serverAddress structure used by bind
    sockaddr_in serverAddress;
    memset((char*)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;				// IPv4 address family
    serverAddress.sin_addr.s_addr = INADDR_ANY;		// Use all available addresses
    serverAddress.sin_port = htons(SERVER_PORT);	// Use specific port


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

    do
    {
        // Struct for information about connected client
        sockaddr_in clientAddr;


        int clientAddrSize = sizeof(struct sockaddr_in);


        // Accept new connections from clients 
        acceptedSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

        // Check if accepted socket is valid 
        if (acceptedSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        printf("\First client request accepted. Client address: %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        acceptedSocket2 = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

        if (acceptedSocket2 == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        printf("\nSecond client request accepted. Client address: %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        printf("Choose letter:");
        char letter;
        scanf_s("%c", &letter);

        sprintf_s(dataBuffer, "Game start with letter : %c.", letter);

        iResult = send(acceptedSocket, dataBuffer, (int)strlen(dataBuffer), 0);

        // Check result of send function
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(acceptedSocket);
            WSACleanup();
            return 1;
        }

        printf("Message successfully sent. Total bytes: %ld\n", iResult);

        iResult2 = send(acceptedSocket2, dataBuffer, (int)strlen(dataBuffer), 0);
        // Check result of send function
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(acceptedSocket);
            WSACleanup();
            return 1;
        }

        printf("Message successfully sent. Total bytes: %ld\n", iResult);

        do
        {

            // Receive data until the client shuts down the connection
            iResult = recv(acceptedSocket, dataBuffer, BUFFER_SIZE, 0);

            if (iResult > 0)	// Check if message is successfully received
            {
                dataBuffer[iResult] = '\0';

                if (dataBuffer[0] == letter) {
                    // Log message text
                    printf("Client sent: %s.\n", dataBuffer);
                }
                else {
                    wrong1 = true;
                }
                if (!strcmp(dataBuffer, "Kraj")) {
                    wrong1 = true;
                }
            }
            else if (iResult == 0)	// Check if shutdown command is received
            {
                // Connection was closed successfully
                printf("Connection with client closed.\n");
                closesocket(acceptedSocket);
            }
            else	// There was an error during recv
            {

                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(acceptedSocket);
            }

            // Receive data until the client shuts down the connection
            iResult2 = recv(acceptedSocket2, dataBuffer2, BUFFER_SIZE, 0);

            if (iResult2 > 0)	// Check if message is successfully received
            {
                dataBuffer2[iResult2] = '\0';

                if (dataBuffer2[0] == letter) {
                    // Log message text
                    printf("Client2 sent: %s.\n", dataBuffer2);
                }
                else {
                    wrong2 = true;
                }
                if (!strcmp(dataBuffer, "Kraj")) {
                    wrong2 = true;
                }

            }
            else if (iResult2 == 0)	// Check if shutdown command is received
            {
                // Connection was closed successfully
                printf("Connection with client closed.\n");
                closesocket(acceptedSocket2);
            }
            else	// There was an error during recv
            {

                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(acceptedSocket2);
            }

            if (wrong1 && wrong2) {
                printf("Both client make a mistake and game continue");
                wrong1 = false;
                wrong2 = false;
            }
            else if (wrong1) {
                printf("Client2 WON!");
                break;
            }
            else if (wrong2) {
                printf("Client1 WON");
                break;
            }

        } while (iResult > 0 || iResult2 > 0);

        // Here is where server shutdown loguc could be placed

    } while (true);

    // Shutdown the connection since we're done
    iResult = shutdown(acceptedSocket, SD_BOTH);

    // Check if connection is succesfully shut down.
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(acceptedSocket);
        WSACleanup();
        return 1;
    }

    //Close listen and accepted sockets
    closesocket(listenSocket);
    closesocket(acceptedSocket);

    // Deinitialize WSA library
    WSACleanup();

    return 0;
}