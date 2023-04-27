#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>


int main()
{
    char buffer[1028];
    char output[1028];
    int read_buf;

    // Setup socket connection for IPv4 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char *ip_addr = "127.0.0.2";
    char *message = "This is a message from the server. ";

    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address, client_address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(3001);
    inet_aton("127.0.0.2", &address.sin_addr);
    
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
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    accept_con = accept(socket_fd, (struct sockaddr*)&client_address, &client_addr_size);

    if (accept_con < 0) 
    {
        perror("ACCEPT ERROR: "); 
    }; 
    
    int res;
    while (1)
    {
        // Read from client 
        read_buf = read(accept_con, buffer, 1028);
        printf("%s", buffer); 
        bzero(buffer, 1028);
        fgets(buffer, sizeof(buffer),stdin);
        res = write(accept_con, buffer, strlen(buffer));
    };
     
    return 0;
}