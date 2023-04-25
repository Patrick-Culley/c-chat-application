#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>



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
    inet_aton(ip_addr, &address.sin_addr);
    // Assign a name to socket 

    int bind_ip = bind(socket_fd, (struct sockaddr*)&address, sizeof(address));

    if (bind_ip == -1)
    {
        perror("ERROR --> ");
    }

    printf("%d\n\n", bind_ip);
    return 0;
}