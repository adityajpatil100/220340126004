/**
 * @file Q1_server.c
 * @author Vishwajit Dalve
 * @brief This is a server side code for a full duplex chatting application using TCP
 * @version 0.1
 * @date 2022-07-22
 */

// Import all the needed libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>

// This is a function that will be running until and unless the user wishes to stop/exit it
// The loop or chat can be stopped if some specific phrase or word is entered
void chatting(int cfd) {
	char buffer[100];
	int n;
	for (;;) {											// This is a for loop that will run unlimited times
		bzero(buffer, 100);									// We use bzero to make the buffer zero or basically emptying the buffer memory	
		recv(cfd, buffer, sizeof(buffer),0);				// recv() will receive the connection from the client
		printf("Msg from Client: %s\t Msg from Server : ", buffer);
		bzero(buffer, 100);
		n = 0;
		while ((buffer[n++] = getchar()) != '\n');			// WHILE loop to read each character from the buffer
		send(cfd, buffer, sizeof(buffer),0);				// send() will simply send the buffer to the client's file descriptor
		if(strncmp("exit", buffer, 4) == 0) {				// Validating condition to stop the conversation
			printf("Server Stopped...\n");
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	// Initially check the size of command line arguments
	// Since we are expecting to get a port number while running this server
	//		the size that we are expecting is of 2 
	// While running the .out file use the format 
	//		./fileName.out port_no
	//		if the above format asks for permission use sudo
	//		sudo ./fileName.out port_no 
	if(argc < 2) {
		printf("Enter the port number after ./fileName ");
		exit(1);
	}

	int sfd, cfd, port_no;

	// Assigning the values to the structure 
	struct sockaddr_in saddr = {0};			// Create a variable to store server address
	saddr.sin_family = AF_INET;				// IPv4 or IPv6
	saddr.sin_port = htons(port_no);		// This will convert the 16-bit number to byte order
	saddr.sin_addr.s_addr = INADDR_ANY;		// Assigning any IP address to the server

	struct sockaddr_in caddr = {0};			// Create a variable to store client address

	port_no = strtoul(argv[1], NULL, 10);	// Convert the port_no to unsigned long int

	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {	// Create a socket for the server
		perror("Socket was not created!");
		exit(2);
	}
	
	if(bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {	// Bind will bind the IP and the port_no
		perror("Failed to Bind!");
		close(sfd);
		exit(3);
	}
	
	if(listen(sfd, 5) < 0) {	// After binding is completed the server simply goes to the listening mode
		perror("Was not able to Listen!");
		close(sfd);
		exit(4);
	}

	socklen_t len = sizeof(caddr);		// The socklen_t will get the size of the caddr of type socket
	if((cfd = accept(sfd, (struct sockaddr *)&caddr, &len)) < 0) {		// accept() function will accept the connection from the client
		perror("Accept Failed!");
		exit(5);
	}
	
    chatting(cfd);		// Call the chatting() function to start the conversation

	close(cfd);			// Close both the client's and server's file descriptor to avoid any memory leak
	close(sfd);
	return 0;
}