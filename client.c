#include "serverhead.h"

int main()
{   
    char buffer[1028];
    int valread; 

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
    printf("Connected to Chat!\nType 'later' to quit.");
    while (1)
    {   
        fgets(buffer, sizeof(buffer), stdin);
        wr = write(socket_fd, buffer, strlen(buffer)); 
        if (wr < 0)
            perror("WRITE ERROR: "); 
        bzero(buffer, 1028);
        re = read(socket_fd, buffer, 1028);
        if (re < 0) 
            perror("READ ERROR: "); 
        pr = printf("Server: %s", buffer);
        bzero(buffer, 1028);
    };

    return 0; 
};