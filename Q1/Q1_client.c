/**
 * @file Q1_client.c
 * @author Vishwajit Dalve
 * @brief This is a client side code for a full duplex chatting application using TCP
 * @version 0.1
 * @date 2022-07-22
 * 
 ** The comments for this code is same as the server 
	the only addition here is the comment for the connect() function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>

void chatting(int sfd) {
	char buffer[100];
	int n;
	for (;;) {
		bzero(buffer, sizeof(buffer));
		printf("Msg from Client : ");
		n = 0;
		while ((buffer[n++] = getchar()) != '\n');
		send(sfd, buffer, sizeof(buffer),0);
		bzero(buffer, sizeof(buffer));
		recv(sfd, buffer, sizeof(buffer),0);
		printf("From Server : %s", buffer);
		if((strncmp(buffer, "exit", 4)) == 0) {
			printf("Client Stopped...\n");
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("Enter the IP address and the port number after the ./fileName");
		exit(1);
	}

	int cfd, serv_port;
	serv_port = strtoul(argv[2], NULL, 10);

	if((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket was not created!");
		exit(2);
	}
	
	struct sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(serv_port);
	saddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	if(connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {	// connect() will connect the client with the server
		perror("Connect did not happen!");
		close(cfd);
		exit(3);
	}

    chatting(cfd);
	
    close(cfd);
	return 0;
}