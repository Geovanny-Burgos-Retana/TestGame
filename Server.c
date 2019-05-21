#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define NUM_CLIENTS 50
#define SIZE_MSG 1024

/*Variables de conexión para MySQL*/
MYSQL *conn;

/*Variable que contendra el resultado de la consulta*/
MYSQL_RES *res;

/*Variable que contendra los campos por cada regitro o consulta*/
MYSQL_ROW row;

/*Dirección del servidor*/
char *serverdb = "localhost";

/*usuario para consultar la base de datos*/
char *user = "root";

/*contraeña de labase de datos  consutar*/
char *password = "gio_97$";

/*nombre de labase de datos a consultar*/
char *database = "dbGame";

/* Server and client variables for connect with sockets */
int sockfd_server , client_sockfd;
struct sockaddr_in server, client;
int optval = 1;

void proof();
void menu();

int main() {    

    // Create socket
    sockfd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_server == -1) {
        perror("socket failed\n");
        exit(1);
    }
    
    // Prevents error such as: “address already in use”
    if (setsockopt(sockfd_server, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&optval, sizeof(int)) < 0) {
        perror("setsockopt failed\n");
        exit(2);
    }
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Assigns the address specified by addr to the socket referred to by the file descriptor sockfd
    if (bind(sockfd_server, (struct sockaddr*)&server, sizeof(server))) {
        perror("bind failed\n");
        close(sockfd_server);
        exit(3);
    }

    // Marks a connection-mode socket, specified by the socket argument and limits the number of outstanding connections in the listen queue
    if (listen(sockfd_server, 50)){
        perror("listen failed");
        close(sockfd_server);
        exit(4);
    }

    /* Inicializar conexión */
    conn = mysql_init(NULL);

    /* Conectar al servidor y a ala base de datos */
    if(!mysql_real_connect(conn, serverdb, user, password, database, 0, NULL, 0)) {        
        fprintf(stderr, "%s\n", mysql_error(conn));        
        exit(1);
    }    

    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_t thread_by_client;
        pthread_create(&thread_by_client, NULL, menu, NULL);
        pthread_join(thread_by_client, NULL);
    }
}

void menu() {
    int addrlen = sizeof(client);
    client_sockfd = accept(sockfd_server, (struct sockaddr *) &client, &addrlen);
    char* message[SIZE_MSG];
    /*while(1) {
        message = "1. ";
    }*/
}

void proof() {
    if(mysql_query(conn, "select * from pregunta")){
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    printf("Las bases son: \n");
    while((row = mysql_fetch_row(res)) != NULL)
        printf("%s\n", row[1]);

    // Close the connection
    mysql_free_result(res);
    mysql_close(conn);
}


