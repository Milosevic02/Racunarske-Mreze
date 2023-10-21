#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"
#include <cstdint>

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"AdvApi32.lib")



int main()
{
	WSADATA wsaData;
	// Initialize windows sockets library for this process
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return 1;
	}

	/*
	struct sockaddr_in s;
	unsigned long some_long = 10;
	unsigned short some_short = 20;
	unsigned long network_byte_order;

	
	network_byte_order = htonl(some_long); //pretvara u bigendian uvek jer je u network big endian
	
	send(s, &network_byte_order, sizeof(unsigned int), 0);
	
	some_short == ntohs(htons(some_short)); //Ovo se potire i vraca broj
	*/

	SOCKADDR_IN socketAddress;

	short nPortId = 55555;

	socketAddress.sin_family = AF_INET; //IPv4 adresna familija

	socketAddress.sin_addr.s_addr = inet_addr("127.0.0.1");//Loopback IP adresa

	socketAddress.sin_port = htons(nPortId);

	SOCKET tcpsocket;
	tcpsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);












	return 0;
}

