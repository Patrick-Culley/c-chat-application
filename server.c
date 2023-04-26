#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>


int main()
{
    char buffer[255];
    int valread;

    // Setup socket connection for IPv4 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char *ip_addr = "127.0.0.1";

    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(3000);
    inet_aton(ip_addr, &address.sin_addr);
    
    // Assign name to socket 
    int bind_ip = bind(socket_fd, (struct sockaddr*)&address, sizeof(address));

    if (bind_ip == -1)
    {
        perror("BINDING ERROR: ");
    };

    // Listen for connections 
    int backlog = 5; 
    int listening = listen(socket_fd, backlog);
    if (listening != 0)
    {
        perror("LISTENING ERROR: ");
    };

    // Accept incoming connection requests 
    int accept_con; 
    accept_con = accept(socket_fd, NULL, NULL);

    if (accept_con < 0)
    {
        perror("ACCEPT ERROR: "); 
    }; 

    // Read from connection to char buffer 
    valread = read(accept_con, buffer, 255);
    printf("%s\n", buffer);

    return 0;
}