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
    char* message="This is a message from your computer client. How are you today?\0";

    // Create socket 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char *ip_addr = "127.0.0.2";

    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(3001);
    inet_aton(ip_addr, &address.sin_addr);
    
    // Assign name to socket 
    int bind_ip = bind(socket_fd, (struct sockaddr*)&address, sizeof(address));

    // Connect 
    int connection = connect(socket_fd, (struct sockaddr*)&address, sizeof(address));

    write(socket_fd, message, strlen(message));
    
    if (connection < 0)
    {
        perror("CONNECTION ERROR ");
    };

    printf("%d", connection);

    return 0; 
};