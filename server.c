#include "serverhead.h" 

int main(int argc, char *argv[])
{
    pthread_t tid;
    char buffer[1028];
    char output[1028];
    int read_buf, socket_fd, new_socket, *new_sock;
    int option = 1;
    struct sockaddr_in client_address; 

    if (argc != 2){
        printf("Enter Port Number");
        return -1; 
    }

    port_number = atoi(argv[1]); 
    printf("%d\n", port_number);
    
    // CREATE SOCKET //
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        printf("SOCKET ERROR: ");
    };

    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_number);

    // BIND SOCKET //
    int bind_ip = bind(socket_fd, (struct sockaddr*)&address, sizeof(address));
    if (bind_ip == -1)
    {
        perror("BINDING ERROR: ");
    };

    fp = fopen(output_file_name,"w"); 
    signal(SIGINT, INThandler); 

    printMagenta("~~~ You have entered The Chat Room ~~~\n");
    fputs("~~~ You have entered The Chat Room ~~~\n", fp);

    // LISTEN // 
    int listening = listen(socket_fd, 5);
    if (listening != 0)
    {
        perror("LISTENING ERROR: ");
    };

    // ACCEPT CONNECTIONS // 
    int accept_con;
    socklen_t client_addr_size = sizeof(struct sockaddr_in);
    while(1)
    {
        accept_con = accept(socket_fd, (struct sockaddr*)&client_address, &client_addr_size);
        if (accept_con < 0) 
        {
            perror("ACCEPT ERROR: "); 
        }; 

        struct connection_t *new_connection = (struct connection_t *) (struct connection *) malloc(
                sizeof(struct connection_t));
        new_connection->p_sock = accept_con;
        new_connection->status = 1;
        new_connection->auth = 0;
        add_socket(new_connection); 
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = accept_con; 

        pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_connection);
    };  

    close(socket_fd); 
    shutdown(socket_fd, SHUT_RDWR);
    return 0;
}

// HANDLES EACH CLIENT CONNECTION // 
void *connection_handler(void *p_connection)
{
    struct connection_t *connection = (struct connection_t*) p_connection;
    int dummy = 0; 

    pthread_t receiving_thread;
    if( pthread_create( &receiving_thread , NULL ,  receiver_handler , (void*) p_connection) > 0) {
        perror("could not create receiving thread");
        return 0;
    }

    while (connection->status)
    {
        dummy++;
    }
};

// HANDLES RECEIVER FROM EACH CLIENT - JOINING ROOM // 
void *receiver_handler(void *p_connection)
{
    struct connection_t *connection = (struct connection_t*)p_connection;
   
    int sock = connection-> p_sock;
    char username[20]; 
    char token[41];

    int read_size; 
    char client_message[2000];
    char processed_client_message[2000];

    while ((read_size = recv(sock, client_message, 2000, 0)) > 0)
    {
        if (!connection->auth)
        {
            strcpy(token, client_message); 

            char ch = token[0]; 
            int i = 0; 
            while (ch != '\n' && ch != '\0')
            {
                username[i] = ch;
                i++;
                ch = token[i];
            }
            username[i] = '\0';
            strcpy(connection->username, username); 

            printBoldGreen(connection->username);
            printBoldGreen(" has joined the chat\n");
            fprintf(fp, "%s has joined\n", connection->username); 
            
            broadcast(connection, "", 1); 
        }
    }
};

void printYellow(char *string) {
    printf("\033[1;33m");
    printf("%s", string);
    printf("\033[0m");
}

void printMagenta(char *string) {
    printf("\033[1;35m");
    printf("%s", string);
    printf("\033[0m");
}

void printBoldGreen(char *string) {
    printf("\033[1;32m");
    printf("%s", string);
    printf("\033[0m");
}

void add_socket(struct connection_t *socket) {
    if (open_connections == 0) {
        socket->next = NULL;
        head = socket;
        tail = socket;
        open_connections++;

    } else if (open_connections > 0) {
        tail->next = socket;
        socket->next = NULL;
        tail = socket;
        open_connections++;
    }
}

void broadcast(struct connection_t *socket, char *message, int type)
{
    char signed_message[strlen(socket->username) + 2 + strlen(message)]; 
    int size = strlen(socket->username) + 2; 
    strcpy(signed_message, socket->username); 

    if (type == 0)
    {
        strcat(signed_message, ": "); 
        strcat(signed_message, message);
        size += strlen(message);
    } else if (type == 1) {
        strcat(signed_message, " has joined\n");
        size += strlen(" has joined\n"); 
    } else if (type == 1) {
        strcat(signed_message, " has left\n"); 
        size += strlen(" has left\n"); 
    }
    
    struct connection_t *currentSocket = head; 
    int i = 0; 
    while (i < open_connections)
    {
        if (socket != currentSocket){
            write(currentSocket->p_sock, signed_message, size); 
        }
        currentSocket = currentSocket->next;
        i++; 
    }
}   

void INThandler(int sig) {
    printYellow("\nDisconnected\n");
    fclose(fp);
    exit(0);
}