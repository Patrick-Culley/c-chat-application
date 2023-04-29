#include "serverhead.h" 
 
void* create_thread(void* args)
{
    printf("Smaller thread"); 
};

int main(int argc, char *argv[])
{
    pthread_t tid;
    char buffer[1028];
    char output[1028];
    int read_buf, socket_fd; 
    int option = 1;
    struct sockaddr_in client_address; 

    // CREATE THREAD // 
    if (pthread_create(&tid, NULL, &create_thread, NULL) == 0);
    {
        printf("Thread created successfully.\n");
    };

    // CREATE SOCKET //
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(3001);
    address.sin_addr.s_addr = INADDR_ANY;

    if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option)) < 0)
    {
        printf("ERROR WITH SETTING OPTIONS");
    }; 
    
    // BIND SOCKET //
    int bind_ip = bind(socket_fd, (struct sockaddr*)&address, sizeof(address));

    if (bind_ip == -1)
    {
        perror("BINDING ERROR: ");
    };

    // LISTEN // 
    int backlog = 5; 
    int listening = listen(socket_fd, backlog);
    if (listening != 0)
    {
        perror("LISTENING ERROR: ");
    };

    // ACCEPT CONNECTIONS // 
    int accept_con;
    while(1)
    {
        socklen_t client_addr_size = sizeof(struct sockaddr_in);
        accept_con = accept(socket_fd, (struct sockaddr*)&client_address, &client_addr_size);
        if (accept_con < 0) 
        {
            perror("ACCEPT ERROR: "); 
        }; 
        // read_buf = read(accept_con, buffer, 1028);
        // printf("Client: %s", buffer); 
        // bzero(buffer, 1028);
        // fgets(buffer, sizeof(buffer), stdin);
        // write(accept_con, buffer, strlen(buffer));
        // bzero(buffer, 1028);
    };  

    close(socket_fd); 
    shutdown(socket_fd, SHUT_RDWR);
    return 0;
}