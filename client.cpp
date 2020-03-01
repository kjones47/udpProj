#include <stdio.h> 
#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8083


int main() { 
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr;
	char hello[20] = "Ping from client";
	
	//make socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("error creating client socket");
	}
	
	memset(&servaddr, 0, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	sendto(sockfd, (const char *)hello, strlen(hello), 
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
	printf("Hello message here sent.\n"); 

	n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);

	buffer[n] = '\0'; 
	printf("Server : %s\n", buffer); 
	close(sockfd); 
    	return 0; 
}
