#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif

// Include libraries
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include "pcap.h"
#include "conio.h"

// Function declarations
void print_interface(pcap_if_t* dev);
char* convert_sockaddr_to_string(struct sockaddr* addr);


int main()
{
	pcap_if_t *devices;					// List of network interface controllers
	pcap_if_t *device;					// Network interface controller
	char errorMsg[PCAP_ERRBUF_SIZE+1];	// Error buffer

	// Retrieve the list of available network interfaces
	if(pcap_findalldevs(&devices, errorMsg) == -1)
	{
		printf("Error in pcap_findalldevs: %s\n", errorMsg);
		return 1;
	}

	// Print all available network interfaces
	for(device=devices; device; device=device->next)
	{
		// Print all the available information on the given interface
		print_interface(device);
	}

	// Free the device list
	pcap_freealldevs(devices);

	// For demonstration purpose
	printf("\nPress any key to exit: ");
	_getch();

	return 0;
}


void print_interface(pcap_if_t *dev)
{
	printf("\n\t ============================= Interface ====================================\n\n");

	/* Name */
	printf("\t Name: \t\t %s\n",dev->name);

	/* Description */
	if (dev->description)
		printf("\t Description: \t %s\n",dev->description);

	// TODO 1: ispisati sve logičke adrese, subnet masku i broadcast adrese povezane sa mrežnim adapterom

	if (dev->flags == PCAP_IF_LOOPBACK) {
		printf("\tLoopback:\tyes\n");
	}
	else {
		printf("\tLoopback:\tno\n");
	}

	pcap_addr *addresses = dev->addresses;
	pcap_addr* address;

	for (address = addresses;address;address = address->next) {
		printf("\n\tADDRESS\n");

		if (address->addr->sa_family == AF_INET) {
			printf("\t# Address Type:\t\tIPv4\n");

			if (address->addr) {
				printf("\t# Address:\t\t%s\n",convert_sockaddr_to_string(address->addr));
			}

			if (address->netmask) {
				printf("\t# Subnet mask:\t\t%s\n", convert_sockaddr_to_string(address->netmask));
			}
			if (address->broadaddr) {
				printf("\t# Broadcast Address:\t%s\n", convert_sockaddr_to_string(address->broadaddr));
			}


		}
		else if (address->addr->sa_family == AF_INET6) {
			printf("\t# Address Type:\tIPv6\n");
		}
	}
}

// TODO 2: prevedi strukturu sackaddr u string kako bi se mogla ispisati
char* convert_sockaddr_to_string(struct sockaddr* address)
{
	return inet_ntoa(((struct sockaddr_in*)address)->sin_addr);
}