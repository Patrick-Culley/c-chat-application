#include "clienthead.h"

int main(int argc, char *argv[])
{   
    if (argc < 4)
    {
        printRed("Pass in port number, user name, and password"); 
        return 1; 
    }
    if (argc > 4)
    {
        printRed("Only pass in port number, user name, and password"); 
        return 1; 
    }

    port_number = atoi(argv[1]); 
    strcpy(username, argv[2]); 
    strcpy(password, argv[3]);

    // AUTHENTICATE PASS // 
    if (strcmp(password, server_password) != 0)
    {
        printRed("Password incorrect, try again");
        return 1; 
    } 

    // CREATE SOCKET //  
    char buffer[1028];
    int valread;
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("SOCKET ERROR: ");
        return 1; 
    };

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_port = htons(port_number);
    address.sin_addr.s_addr = inet_addr(ip_address); 
    
    // CONNECT TO REMOTE SERVER //  
    int connection = connect(socket_fd, (struct sockaddr*)&address, sizeof(address));
    if (connection < 0)
    {
        perror("CONNECTION ERROR ");    
        return 1; 
    };

    status = 0; 
    printMagenta("~~~ You have entered The Chat Room ~~~\n");

    pthread_t receiving_thread; 
    int new_socket = socket_fd; 
    int *new_sock;
    new_socket = malloc(1); 
    *new_sock = new_socket; 

    pthread_create(&receiving_thread, NULL, receiver_handler, (void*) new_sock);

    int wr, re, pr; 
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

void *receiver_handler(void *socket)
{
    int sock = *(int*)socket; 
    int read_size; 
    char server_message[2000]; 
    char processed_server_message[2000]; 

    // RECEIVE MSG FROM CLIENT 
    while ((read_size = recv(sock, server_message, 2000, 0)) > 0)
    {
        int ie = 0; 
        for (int i = 0; i <= strlen(server_message); i++)
        {
            if (server_message[i] == '\n'){
                server_message[i] == '\0';
            }
            processed_server_message[i] = server_message[i]; 
            ie = i; 
        }
        printBlue(processed_server_message); 
        printf("\n");
        processed_server_message[ie] = '\n';
    }
    if (read_size == 0){
        printYellow("Server disconnected\n");
        exit(0); 
    } else if (read_size == -1){
        perror("recv failed");
    }
    status = 0; 
    free(socket); 

    return 0; 
}

void printRed(char *string) {
    printf("\033[1;31m");
    printf("%s", string);
    printf("\033[0m");
}

void printBlue(char *string) {
    printf("\033[0;36m");
    printf("%s", string);
    printf("\033[0m");
}