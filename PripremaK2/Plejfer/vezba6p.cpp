// We do not want the warnings about the old deprecated and unsecure CRT functions since these examples can be compiled under *nix as well
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// Include libraries
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include "conio.h"
#include "pcap.h"
#include "protocol_headers.h"

// Function declarations
void packet_handler(unsigned char* fd, const struct pcap_pkthdr*
	packet_header, const unsigned char* packet_data);
const char* plejfer(char* poruka);
pcap_dumper_t* file_dumper;
// Plejfer matrica
char kljuc[5][5] = { {'R', 'A', 'C', 'U', 'N'}, 
					 {'B', 'D', 'E', 'F', 'G'}, 
					 {'H', 'I', 'K', 'L', 'M'},  
					 {'O', 'P', 'Q', 'S', 'T'},  
					 {'V', 'W', 'X', 'Y', 'Z'} };
char copy[10000];
int arp_counter = 0;
int packet_counter = 0;


int main()
{
	pcap_t* device_handle;
	char error_buffer[PCAP_ERRBUF_SIZE];
	// Open the capture file
	if ((device_handle = pcap_open_offline("packetsv12.pcap", // Name of the device
		error_buffer // Error buffer
	)) == NULL)
	{
		printf("\n Unable to open the file %s.\n", "packetsv12.pcap");
		return -1;
	}
	// Check the link layer. We support only Ethernet for simplicity.
	if (pcap_datalink(device_handle) != DLT_EN10MB)
	{
		printf("\nThis program works only on Ethernet networks.\n");
		return -1;
	}

	file_dumper = pcap_dump_open(device_handle, "encrypt.pcap");
	if (file_dumper == NULL)
	{
		printf("Cant create file ");
		return -1;
	}

	// Read and dispatch packets until EOF is reached
	pcap_loop(device_handle, 10, packet_handler, (unsigned char*)file_dumper);
	double udeo = arp_counter / packet_counter;

	// Close the file associated with device_handle and deallocates resources
	pcap_close(device_handle);

	printf("Udeo ARP je %lf", udeo);

	return 0;
}



void packet_handler(unsigned char* fd, const struct pcap_pkthdr*
	packet_header, const unsigned char* packet_data)
{
	packet_counter++;
	int velicinaPaketa = packet_header->len;
	memset(copy, 0,velicinaPaketa * sizeof(char));
	ethernet_header* eh = (ethernet_header*)packet_data;
	memcpy(copy, eh, sizeof(ethernet_header));

	printf("Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
		eh->src_address[0], eh->src_address[1], eh->src_address[2], eh->src_address[3], eh->src_address[4], eh->src_address[5]);
	if (ntohs(eh->type) == 0x806) {
		printf("ARP protocol\n");
		arp_counter++;
	}
	else if (ntohs(eh->type) == 0x800) {
		ip_header* ih = (ip_header*)(packet_data + sizeof(ethernet_header));
		memcpy(copy + sizeof(ethernet_header), ih, ih->header_length * 4);
		printf("Logicka adresa posiljaoca: %d.%d.%d.%d\n", ih->src_addr[0], ih->src_addr[1], ih->src_addr[2], ih->src_addr[3]);

		printf("%x", ih->ttl);

		if (ih->next_protocol == 6) {

			tcp_header* th = (tcp_header*)((unsigned char*)ih + ih->header_length*4);
			unsigned short src_port = ntohs(th->src_port);
			printf("Port Posiljaoca:%d\n", src_port);
			printf("Broj potvrde:%d\n", th->ack_num);

			if (th->flags == 18) {
				printf("Logicka adresa primaoca: %d.%d.%d.%d\n", ih->dst_addr[0], ih->dst_addr[1], ih->dst_addr[2], ih->dst_addr[3]);
				unsigned short dst_port = ntohs(th->dest_port);
				printf("Port primaoca:%d\n", dst_port);
			}

			if (ntohs(th->src_port) == 80 || ntohs(th->dest_port) == 80) {
				printf("HTTP sadrzaj:");
				char* app_data = (char*)((unsigned char*)th + th->header_length * 4);
				for (int i = 0;i < 16;i++) {
					printf("%c", app_data[i]);
				}
				printf("\n");
			}
		}
		else if (ih->next_protocol == 11) {

			udp_header* uh = (udp_header*)((unsigned char*)ih + ih->header_length*4);
			memcpy(copy + sizeof(ethernet_header) + ih->header_length * 4, uh, sizeof(uh));
			char* app_data = (char*)((unsigned char*)uh + sizeof(udp_header));
			int app_len = ntohs(uh->datagram_length) - sizeof(udp_header);
			printf("UDP: Packet size: %u\n", ntohs(uh->datagram_length));

			for (int i = 0; (i < app_len); i++)
			{
				printf("%.2x ", app_data[i]);
				if ((i + 1) % 16 == 0)
					printf("\n");
			}
			printf("\n\n");

			char cipher[200] = "\0";
			strcpy(cipher, plejfer(app_data));
			printf("Sifrovano: %s", cipher);

			memcpy(copy + sizeof(ethernet_header) + ih->header_length * 4 + sizeof(udp_header), cipher, app_len);
			pcap_dump((unsigned char*)fd, packet_header, (const unsigned char*)copy);


		}
	}



	// Save the packet on the dump file
}
const char* plejfer(char* poruka) {
	int x1 = -1, x2 = -1, y1 = -1, y2 = -1;

	int duzinaPoruke = strlen(poruka);
	char neutralniKarakter = 'S';//Pozicija [3][3]
	char kriptovanaPoruka[200];

	for (int i = 0;i < duzinaPoruke;i += 2) {
		for (int j = 0;j < 5;j++) {
			for (int k = 0;k < 5;k++) {
				if (kljuc[j][k] == poruka[i]) {
					x1 = j;
					y1 = k;
				}
				if (kljuc[j][k] == poruka[i + 1]) {
					x2 = j;
					y2 = k;
				}
			}
		}

		if (i == duzinaPoruke - 1) {
			x2 = 3;
			y2 = 3;
		}

		if (x1 == x2 && y1 == y2) {
			kriptovanaPoruka[i] = poruka[i];
			kriptovanaPoruka[i + 1] = 'X';
		}
		else {
			if (x1 == x2) {
				if (y1 == 4) {
					kriptovanaPoruka[i] = kljuc[x1][0];
				}
				else {
					kriptovanaPoruka[i] = kljuc[x1][y1 + 1];
				}
				if (y2 == 4) {
					kriptovanaPoruka[i + 1] = kljuc[x2][0];

				}
				else {
					kriptovanaPoruka[i + 1] = kljuc[x2][y2+1];
				}
			}
			if (y1 == y2) {
				if (x1 == 4) {
					kriptovanaPoruka[i] = kljuc[0][y1];
				}
				else {
					kriptovanaPoruka[i] = kljuc[x1 + 1][y1];
				}if (x2 == 4) {
					kriptovanaPoruka[i + 1] = kljuc[0][y2];
				}
				else {
					kriptovanaPoruka[i + 1] = kljuc[x2 + 1][y2];
				}
			}
			else {
				kriptovanaPoruka[i] = kljuc[x1][y2];
				kriptovanaPoruka[i + 1] = kljuc[x2][y1];
			}
		}
	}
	kriptovanaPoruka[duzinaPoruke] = '\0';
	return kriptovanaPoruka;
}
