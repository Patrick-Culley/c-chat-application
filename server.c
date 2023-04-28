#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> // Library for threading functions 


int main()
{
    pthread_t tid[60];
    char buffer[1028];
    char output[1028];
    int read_buf, t_num;

    // Create a thread for practice 
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

    // Setup socket connection for IPv4 
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address, client_address; 
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

    // Accept incoming connection requests 
    int accept_con; 
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    accept_con = accept(socket_fd, (struct sockaddr*)&client_address, &client_addr_size);

    if (accept_con < 0) 
    {
        perror("ACCEPT ERROR: "); 
    }; 

    int res;
    while(1)
    {
        // Read from clients
        read_buf = read(accept_con, buffer, 1028);
        printf("Client: %s", buffer); 
        bzero(buffer, 1028);
        fgets(buffer, sizeof(buffer), stdin);
        write(accept_con, buffer, strlen(buffer));
        bzero(buffer, 1028);
    };  

    return 0;
}