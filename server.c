#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address; 
    printf("%d\n\n", socket_fd);
    return 0;
}