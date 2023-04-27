#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

int main()
{   
    char buffer[1028];
    int valread; 
    char* message="This is a message from the CLIENT. How are you today? \0";

    // Create socket 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(3001);
    address.sin_addr.s_addr = INADDR_ANY;
    
    // Assign name to socket 
    int bind_ip = bind(socket_fd, (struct sockaddr*)&address, sizeof(address));

    // Connect 
    int connection = connect(socket_fd, (struct sockaddr*)&address, sizeof(address));

    if (connection < 0)
    {
        perror("CONNECTION ERROR ");    
    };
    int wr, re, pr; 
    while (1)
    {
        wr = write(socket_fd, message, strlen(message)); 
        if (wr < 0)
            perror("WRITE ERROR: "); 
        bzero(buffer, 1028);
        re = read(socket_fd, buffer, 1028);
        if (re < 0) 
            perror("READ ERROR: "); 
        pr = printf("%s", buffer);
    };

    return 0; 
};