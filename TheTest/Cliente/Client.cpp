#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "string.h"
#include "Client.h"
#define MSG_LEN 256
#define USERNAME_LEN 32
#define IP_LEN 16
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

// Globals
int clientSocket;
char username[USERNAME_LEN];

void reciveMessages() {
    char recvBuffer[MSG_LEN];
    while (1) {
        int recvStatus = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (recvStatus > 0) {
            printf(GRN "%s\n" RESET, recvBuffer);
            fflush(stdout);
            memset(recvBuffer, 0, sizeof(recvBuffer));
        }

        else if (recvStatus < 0) {
            printf("Error fatal al recibir mensaje\n");
            exit(-1);
        }
    }
}
int read_config_file(char* config_filename){
    int puerto;
    char nuevoport[10];
    FILE *infile;
    infile= fopen(config_filename,"rb");
    if(infile ==NULL){
        printf("Error al abrir archivo");
        exit(1);
    }
    fgets(nuevoport, sizeof(nuevoport), infile);
    // printf("Puerto nuevo:%s\n",nuevoport);
    fclose(infile);
    puerto = atoi(nuevoport);
    printf("Puerto int:%d\n",puerto);
    return puerto;
    
}
void sendMessages() {
    char sendBuffer[MSG_LEN];
    while (1) {

        while (fgets(sendBuffer, MSG_LEN, stdin) != NULL) {

            char* nl = strchr(sendBuffer, '\n');
            *nl = '\0';

            if (strlen(sendBuffer) == 0) {
                continue;
            }

            else {
                break;
            }
        }

        send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
        if (strcmp(sendBuffer, "/quit") == 0) {
            break;
        }
    }
}
void validInput(){
    printf("Ingrese su nombre: ");
    if (fgets(username, USERNAME_LEN, stdin) != NULL) {
        char* c = strchr(username, '\n');
        *c = '\0';
        
    }

    if (strlen(username) <= 0) {
        printf("\nEl usuario no ingresó un nombre. Cerrando el cliente\n");
        exit(-1);
    }
    
}

void createClient(){
    clientSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (clientSocket == -1) {
        printf("Error fatal al crear el socket del cliente");
        exit(-1);
    }
}

void initialize(struct sockaddr_in* serverInfo,struct sockaddr_in *clientInfo){
    int serverAddrLen = sizeof(serverInfo);
    int clientAddrLen = sizeof(clientInfo);

    memset(serverInfo, 0, serverAddrLen);
    memset(clientInfo, 0, clientAddrLen);

    serverInfo->sin_addr.s_addr = inet_addr("127.0.0.1"); //TODO cambiar esto por el del .config
    serverInfo->sin_port = htons(9001);
    serverInfo->sin_family = AF_INET;
}

void connection(struct sockaddr_in* serverInfo, struct sockaddr_in *clientInfo){
    int serverAddrLen = sizeof(serverInfo);
    int clientAddrLen = sizeof(clientInfo);

    int connectStatus = connect(clientSocket, (struct sockaddr*)serverInfo, serverAddrLen);

    if (connectStatus == -1) {
        printf("Error falta al conectarse con el servidor\n");
        exit(-1);
    }

    getsockname(clientSocket, (struct sockaddr*) clientInfo, (socklen_t*) &clientAddrLen);
    printf("Se ha conectado al servidor: %s\n", inet_ntoa(serverInfo->sin_addr));

    //Send username to server
    send(clientSocket, username, USERNAME_LEN, 0);
}

int start(){

    //Username input
    validInput();

    //Create client socket
    createClient();

    //Initialize variables
    struct sockaddr_in serverInfo;
    struct sockaddr_in clientInfo;

    int serverAddrLen = sizeof(serverInfo);
    int clientAddrLen = sizeof(clientInfo);

    memset(&serverInfo, 0, serverAddrLen);
    memset(&clientInfo, 0, clientAddrLen);

    serverInfo.sin_addr.s_addr = inet_addr("192.168.100.18"); //TODO cambiar esto por el del .config
    serverInfo.sin_port = htons(9001);
    serverInfo.sin_family = AF_INET;

    int connectStatus = connect(clientSocket, (struct sockaddr*)&serverInfo, serverAddrLen);

    if (connectStatus == -1) {
        printf("Error falta al conectarse con el servidor\n");
        exit(-1);
    }

    printf("Se ha conectado al servidor!\n");

    //Send username to server
    send(clientSocket, username, USERNAME_LEN, 0);
    
    //Make a child process
    int pid = fork();

    if (pid == 0) {
        sendMessages();
    }

    else{
        reciveMessages();
    }
    	
    close(clientSocket);
    return 0;
}


