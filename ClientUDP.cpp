#pragma comment (lib, "ws2_32.lib")
#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <string>

using namespace std;
// Function prototype
void UDPClient(char *szServer, short nPort);

int main(int argc, char **argv) {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int nRet;
	short nPort;

	if (argc != 3) {
		fprintf(stderr, "\nSyntax: udp-client ServerName PortNumber\n");
		return 0;
	}

	nPort = atoi(argv[2]);

	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested) {
		fprintf(stderr, "\n Wrong version\n");
		return 0;
	}

	UDPClient(argv[1], nPort);

	WSACleanup();
	return 0;
}
void UDPClient(char *szServer, short nPort) {
	SOCKET theSocket;		// socket init
	char name[100];		// a string for the user name
	char msg[256], tmp[256];	// a string for the chat message

	printf("\nSimple.chat ver0.1\n");
	cout << "login: "; cin >> name;

	while (strcmp(msg, "quit") != 0) {	// loop until user types 'quit'
		printf("\n %s> ", name);
		cin >> ws;		// clear the keyboard buffer
		cin.getline(msg, 256);

		LPHOSTENT lpHostEntry;
		lpHostEntry = gethostbyname(szServer);	// find IP from domain name
		if (lpHostEntry == NULL) {
			printf("\n error in %s\n", "gethostbyname()");
			return;
		}
		//Create a UDP/IP datagram socket
		theSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (theSocket == INVALID_SOCKET) {
			printf("\n Socket error: %s", "socke()");
			return;
		}

		SOCKADDR_IN saServer;		// construct the address
		saServer.sin_family = AF_INET;
		saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
		saServer.sin_port = htons(nPort); // Port number from command line
		char szBuf[256];
		int nRet;
		// copy the buffer to the message cache
		strcpy_s(szBuf, msg);
		// send
		nRet = sendto(theSocket, szBuf, strlen(szBuf), 0, (LPSOCKADDR)&saServer,
			sizeof(struct sockaddr));	// Length of address
		if (nRet == SOCKET_ERROR) {
			printf("error: %s\n", "sendto()"); closesocket(theSocket); return;
		}
		// if user doesn't want to quit
		if (strcmp(msg, "quit") != 0) {
			memset(szBuf, 0, sizeof(szBuf));
			int nFromLen = sizeof(struct sockaddr);
			recvfrom(theSocket,		// Socket
				szBuf,		// Receive buffer
				sizeof(szBuf),	// Length of receive buffer
				0,		// Flags
				(LPSOCKADDR)&saServer,// Buffer to receive sender's address
				&nFromLen);	// Length of address buffer
			if (nRet == SOCKET_ERROR) {
				printf("recvfrom()"); closesocket(theSocket); return;
			}
			printf(" %s> %s", szServer, szBuf);
		}
	}
	closesocket(theSocket); 	// close the connection
}