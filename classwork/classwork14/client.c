 /*
    * filename: clientPC.c
    * purpose: simple communications client demonstrator
    *
    * to compile and link on Windows:
    *    gcc clientPC.c -lws2_32 -o clientPC.exe
    * to run the program:
    *    server must be running on localhost [127.0.0.1] and port 6789
    * modified from:
    *   http://softmc.servotronix.com/wiki/Program_Examples:TCP_IP:TCPIP_Winsock_Client
    */

   #ifndef UNICODE
   #define UNICODE
   #endif

   #define WIN32_LEAN_AND_MEAN

   #include <winsock2.h>
   #include <Ws2tcpip.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <inttypes.h>
   #include <ctype.h>
   #include <string.h>

   // Link with ws2_32.lib
   #pragma comment(lib, "Ws2_32.lib")

   #define DEFAULT_BUFLEN 512


   #define IP_ADDRESS  "127.0.0.1"
   #define TELNET_PORT 6789

	// not very good at validating ips
	// but good enough to differentiate between a probably-ip and a probably-not-ip
	// turns out I don't need this lol
	int is_ip(const char* s){
		if(strlen(s) < 1){
			return 0;
		}
		int num_numerics = 0;		
		for (int i = 0; i < strlen(s); i++){
			if (!isdigit(s[i]) && s[i] != '.'){
				return 0;
			}
			if (num_numerics == 0 && !isdigit(s[i])){
				return 0;
			}
			if (isdigit(s[i])){
				num_numerics++;
				if (num_numerics > 3){
					return 0;
				}					
			}
			else{
				num_numerics = 0;
			}
		}
		return 1;
	}

	int isnumeric(const char* s){
		if(strlen(s) < 1){
			return 0;
		}
		for (int i = 0; i < strlen(s); i++){
			if (!isdigit(s[i])){
				return 0;
			}
		}
		return 1;
	}

   int main(int argc, char** argv) {
	    uint32_t port = TELNET_PORT;
		char* ip_address = IP_ADDRESS;
		if (argc == 2){
			if (!isnumeric(argv[1])){
				ip_address = argv[1];
			}
			else{
				port = strtoul(argv[1], NULL, 10);
				if (!port){
					printf("Invalid port number given!\nQuitting now...\n");
					return 1;
				}
			}
		}
		else if (argc > 2){
			int ip_arg = ((!isnumeric(argv[1])) ? 1 : ((!isnumeric(argv[2])) ? 2 : 0));
			if (!ip_arg){
				printf("The program must be called in one of the following formats:\n\tclient.exe <ip> <port>\n\tclient.exe <port> <ip>\nQuitting now...\n");
				return 2;
			}
			int port_arg = ((ip_arg = 1) ? 2 : 1);
			
			ip_address = argv[ip_arg];
			port = strtoul(argv[port_arg], NULL, 10);
			if (!port){
				printf("Invalid port number given!\nQuitting now...\n");
				return 3;
			}
		}


       //----------------------
       // Declare and initialize variables.
       int iResult;
       WSADATA wsaData;

       SOCKET ConnectSocket = INVALID_SOCKET;
       struct sockaddr_in clientService;

       int recvbuflen = DEFAULT_BUFLEN;
       char sendbuf[512];
       char recvbuf[DEFAULT_BUFLEN] = "";

       //----------------------
       // Initialize Winsock
       iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
       if (iResult != NO_ERROR) {
           wprintf(L"WSAStartup failed with error: %d\n", iResult);
           return 1;
       }

       //----------------------
       // Create a SOCKET for connecting to server
       ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       if (ConnectSocket == INVALID_SOCKET) {
           wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
           WSACleanup();
           return 1;
       }

       //----------------------
       // The sockaddr_in structure specifies the address family,
       // IP address, and port of the server to be connected to.
       clientService.sin_family = AF_INET;
       clientService.sin_addr.s_addr = inet_addr( ip_address );
       clientService.sin_port = htons( port );

       //----------------------
       // Connect to server.
       iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
       if (iResult == SOCKET_ERROR) {
           wprintf(L"connect failed with error: %d\n", WSAGetLastError() );
           closesocket(ConnectSocket);
           WSACleanup();
           return 1;
       }

       Sleep(1000);

       iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
       if ( iResult > 0 ) {
           wprintf(L"Bytes received: %d\n", iResult);
           printf("%s\r\n", recvbuf);
       }
       else if ( iResult == 0 )
           wprintf(L"Connection closed\n");
       else
           wprintf(L"recv failed with error: %d\n", WSAGetLastError());

       Sleep(1000);

       //----------------------
       // Send an initial buffer
	   	   
	   printf("Welcome to the client interface!\nEnter messages to send them to the server.\nType \"000\" to quit.\n");
	   
	   while(1){
		   if (fgets(sendbuf, sizeof(sendbuf), stdin)){
				sendbuf[strcspn(sendbuf, "\n")] = '\0';
				if (strlen(sendbuf) != 0){
					iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf) + 1, 0 );
					if (iResult == SOCKET_ERROR) {
						wprintf(L"send failed with error: %d\n", WSAGetLastError());
						closesocket(ConnectSocket);
						WSACleanup();
						return 1;
					}

					printf("Bytes Sent: %d with message %s and length %d\n", iResult, sendbuf, strlen(sendbuf) );

					Sleep(1000);  
					
					if(!strcmp(sendbuf, "000")){
						break;
					}
				}
		   }
	   }
	   

       // shutdown the connection since no more data will be sent
       iResult = shutdown(ConnectSocket, SD_SEND);
       if (iResult == SOCKET_ERROR) {
           wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
           closesocket(ConnectSocket);
           WSACleanup();
           return 1;
       }


       // close the socket
       iResult = closesocket(ConnectSocket);
       if (iResult == SOCKET_ERROR) {
           wprintf(L"close failed with error: %d\n", WSAGetLastError());
           WSACleanup();
           return 1;
       }

       WSACleanup();
       return 0;
   }