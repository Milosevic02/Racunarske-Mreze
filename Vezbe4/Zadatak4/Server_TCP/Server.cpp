#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"
#include "string.h"
#include <sstream>
#include <iostream>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define SERVER_PORT 18010
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
        sockaddr_in clientAddr2;


        int clientAddrSize = sizeof(struct sockaddr_in);

        // Prihvat veze sa 1. klijentom 
        acceptedSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        acceptedSocket2 = accept(listenSocket, (struct sockaddr*)&clientAddr2, &clientAddrSize);


        // Check if accepted socket is valid 
        if (acceptedSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        if (acceptedSocket2 == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        printf("\nClient request accepted. Client1 address: %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        printf("\nClient request accepted. Client2 address: %s : %d\n", inet_ntoa(clientAddr2.sin_addr), ntohs(clientAddr2.sin_port));


        //korak 2.a postavljanje uticnica namenjenih klijentima u neblokirajuci rezim
        unsigned long mode = 1; //non-blocking mode
        iResult = ioctlsocket(acceptedSocket, FIONBIO, &mode);
        iResult2 = ioctlsocket(acceptedSocket2, FIONBIO, &mode);

        if (iResult != NO_ERROR)
            printf("ioctlsocket failed with error: %ld\n", iResult);
        if (iResult2 != NO_ERROR)
            printf("ioctlsocket failed with error: %ld\n", iResult2);

        //polling model prijema poruka
        do
        {
            // Prijem poruke na 1. uticnici
            iResult = recv(acceptedSocket, dataBuffer, BUFFER_SIZE, 0);

            if (iResult > 0)	// Check if message is successfully received
            {
                dataBuffer[iResult] = '\0';

                printf("AcceptSocket1 recive message.Client1 sent: %s.\n", dataBuffer);


                int suma = 0;
                istringstream iss(dataBuffer);
                string token;
                char delim = ',';

                while (getline(iss, token, delim)) {
                    int num = stoi(token);
                    suma += num;
                }

                char message[50];
                sprintf_s(message, "Suma je : %d", suma);
                iResult = send(acceptedSocket, message, (int)strlen(message), 0);
                // Log message text
            }
            else if (iResult == 0)	// Check if shutdown command is received
            {
                // Connection was closed successfully
                printf("Connection with client closed.\n");
                closesocket(acceptedSocket);
                break;
            }
            else	// u neblokir. rezimu funkcija se cesto neuspesno iyvrsi jer nije spreman, pa bi zelela da blokira program
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK) {
                    Sleep(1500);
                }
                else {
                    // Desila se neka druga greska prilikom poziva operacije
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(acceptedSocket);
                    break;
                }

            }

            // Prijem poruke na 1. uticnici
            iResult2 = recv(acceptedSocket2, dataBuffer2, BUFFER_SIZE, 0);

            if (iResult2 > 0)	// Check if message is successfully received
            {
                dataBuffer2[iResult2] = '\0';

                printf("AcceptSocket2 recive message.Client2 sent: %s.\n", dataBuffer2);


                int suma = 0;
                istringstream iss(dataBuffer2);
                string token;
                char delim = ',';

                while (getline(iss, token, delim)) {
                    int num = stoi(token);
                    suma += num;
                    cout << num << endl;
                }
                char message[50];
                sprintf_s(message, "Suma je : %d", suma);
                iResult2 = send(acceptedSocket2, message, (int)strlen(message), 0);

                // Log message text
            }
            else if (iResult2 == 0)	// Check if shutdown command is received
            {
                // Connection was closed successfully
                printf("Connection with client closed.\n");
                closesocket(acceptedSocket);
                break;
            }
            else	// u neblokir. rezimu funkcija se cesto neuspesno iyvrsi jer nije spreman, pa bi zelela da blokira program
            {
                if (WSAGetLastError() == WSAEWOULDBLOCK) {
                    // U pitanju je blokirajuca operacija 
                    // tj. poruka jos nije stigla
                }
                else {
                    // Desila se neka druga greska prilikom poziva operacije
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(acceptedSocket2);
                    break;
                }

            }

        } while (true);

    } while (true);


    //Close listen and accepted sockets
    closesocket(listenSocket);
    closesocket(acceptedSocket);
    closesocket(acceptedSocket2);


    // Deinitialize WSA library
    WSACleanup();

    return 0;
}