#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <string>

using namespace std;
// Function prototype
void UDPServer(short nPort);
// Helper macro for displaying errors
#define PRINTERROR(s) printf("\n%s: %d\n", s, WSAGetLastError())

int main(int argc, char **argv) {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int nRet;
	short nPort;

	if (argc != 2) {
		fprintf(stderr, "\nSyntax: udp-server PortNumber\n");
		return 0;
	}

	nPort = atoi(argv[1]);

	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested) {
		fprintf(stderr, "\n Wrong version\n");
		return 0;
	}

	UDPServer(nPort);
	WSACleanup();
}
void UDPServer(short nPort) {
	SOCKET theSocket;

	theSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Protocol
	if (theSocket == INVALID_SOCKET) {
		PRINTERROR("socket()");
		return;
	}
	SOCKADDR_IN saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;	// Let WinSock assign address
	saServer.sin_port = htons(nPort);	// Use port passed from user

	int nRet;
	nRet = bind(theSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
	if (nRet == SOCKET_ERROR) {
		PRINTERROR("bind()");
		closesocket(theSocket);
		return;
	}

	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuf[256], tmpBuf[256], name[100], msg[256];
	nRet = gethostname(szBuf, sizeof(szBuf));
	if (nRet == SOCKET_ERROR) {
		PRINTERROR("gethostname()");
		closesocket(theSocket);
		return;
	}
	system("cls");
	printf("\n\n// simple.chat server v0.1\n");
	printf("\nServer named %s waiting on port %d\n", szBuf, nPort);
	// save name for later
	strncpy_s(name, szBuf, 100);
	// loop until client terminates the chat session
	while (strcmp(szBuf, "quit") != 0) {
		SOCKADDR_IN saClient;
		memset(szBuf, 0, sizeof(szBuf));
		nRet = recvfrom(theSocket, szBuf, sizeof(szBuf), 0, (LPSOCKADDR)&saClient, &nLen);

		// close connection and return if the client quits
		if (strcmp(szBuf, "quit") == 0) {
			closesocket(theSocket);
			return;
		}
		strcpy_s(tmpBuf, szBuf);
		//cout << "user> " << szBuf;
		printf(" user> %s", tmpBuf);
		printf(" ");
		// Send data back to the client
		printf("\n %s> ", name);

		cin >> ws;
		cin.getline(msg, 256);

		// simply echo back client message for now relay the message
		sendto(theSocket, msg, strlen(msg), 0, (LPSOCKADDR)&saClient, nLen);
	}
	closesocket(theSocket);
	return;
}