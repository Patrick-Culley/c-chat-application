#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>


int main()
{
    char buffer[1028];
    char output[1028];
    int valread;

    // Setup socket connection for IPv4 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char *ip_addr = "127.0.0.2";
    char *message = "This is a message from the server. ";

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

    // Create Client struct 
    struct sockaddr_in client_address; 
    client_address.sin_family = AF_INET; 
    client_address.sin_port = htons(3001);
    inet_aton("127.0.0.2", &client_address.sin_addr);

    // Accept incoming connection requests 
    int accept_con; 
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    accept_con = accept(socket_fd, (struct sockaddr*)&client_address, &client_addr_size);

    if (accept_con < 0) 
    {
        perror("ACCEPT ERROR: "); 
    }; 

    // Read from connection to char buffer 
    valread = read(accept_con, buffer, 1028);
    printf("%s", buffer);

    return 0;
}