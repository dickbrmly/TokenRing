/******************************************************************************/
//  Richard Bromley 5001075854
//  CS 370 1001 Assignment 6
//
//                 Token Ring (Dijkstra's Algorithm) Network
//
// 
//                 *Most of the Code Provided for Assignment*
/******************************************************************************/
#include <stdio.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
    
/*******************************************************************************
*******************************************************************************/
void sendMessage(int address, int value) {
    send(address, &value, sizeof(int), 0);
}
/*******************************************************************************
*******************************************************************************/
int recieveMessage(int rightNeighbor) {
    int value;
    recv(rightNeighbor, &value, sizeof(int), 0);
    return value;
}
/*******************************************************************************
*******************************************************************************/
int createClientConnection(char* socketName) {
	int descriptor;
/* 
	The call to the function ‘socket()’ creates an UN-named socket inside the 
kernel and returns an integer known as socket descriptor. This function takes 
domain/family as its first argument.  For Internet family of IPv4 addresses we 
use AF_INET. The second argument ‘SOCK_STREAM’ specifies that the transport 
layer protocol that we want should be reliable ie it should have 
acknowledgement techniques. For example : TCP...  The third argument is 
generally left zero to let the kernel decide the default protocol to use for 
this connection. For connection oriented reliable connections, the default 
protocol used is TCP.
*/	
	if ((descriptor = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		printf("Error creating socket [%s]\n", socketName);
		return -1;
	}
    
	struct sockaddr_un address;
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, socketName);
	unsigned int addressLength = sizeof(address);
/*	
    Information like IP address of the remote host and its port is bundled up 
in a structure and a call to function connect() is made which tries to connect 
this socket with the socket (IP address and port) of the remote host.
*/
	if (connect(descriptor, (struct sockaddr*)&address, addressLength) < 0) {
		printf("Error connecting socket [%s]\n", socketName);
		return -1;
	}
	return descriptor;
}
/*******************************************************************************
*******************************************************************************/
int createServerConnection(char* socketName) {
	int descriptor;
	//To create endpoint for communication
	if ((descriptor = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		printf("Error creating socket [%s]\n", socketName);
		return -1;
	}
	struct sockaddr_un address;
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, socketName);
	unsigned int addressLength = sizeof(address);
    //To remove a socket if it exists. Its called before bind()

	unlink(socketName);
	
    //To assign a local socket address.
	if (bind(descriptor, (struct sockaddr*)&address, addressLength) < 0) {
		printf("Error binding socket [%s]\n", socketName);
		return -1;
	}
/*
    To instruct a socket to listen for incoming connections. It specifies the 
number of pending connections that can be queued for a server socket. After the
call to listen(), this socket becomes a fully functional listening socket.
*/
	if (listen(descriptor, 1) < 0) {
		printf("Error listening to socket [%s]\n", socketName);
		return -1;
	}
	
	int connectedDescriptor;
	
	//To accept the connection request from a client
	if ((connectedDescriptor = accept(descriptor, 
	(struct sockaddr*) &address, &addressLength)) < 0) {
		printf("Error accepting socket connection [%s]\n", socketName);
		return -1;
	};
	return connectedDescriptor;
}
/*******************************************************************************
*******************************************************************************/
