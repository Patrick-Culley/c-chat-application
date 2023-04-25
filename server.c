#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
    // Setup socket connection for IPv4 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char *ip_addr = "127.0.0.1";

    if (socket_fd < 0)
    {
        printf("Error creating socket!");
    };

    // Pass to connect() to connect to server  
    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(3000);
    address.sin_addr.s_addr = inet_aton(ip_addr, &address.sin_addr);

    

    printf("%d\n\n", socket_fd);
    return 0;
}