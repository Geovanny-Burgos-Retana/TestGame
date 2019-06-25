//LIBRERIAS
#include <iostream>
#include <sstream>
//Sockets
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

using namespace std;

// Globals
int clientSocket;
char username[USERNAME_LEN];
char recvBuffer[MSG_LEN];

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
    printf("\n=> Socket successfully created..\n");
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

    string ip;
    int port;

    cout << "\nIngrese la ip del servidor a conectarse: ";
    cin >> ip;
    cout << "\nIngrese el puerto por el cual conectarse: ";
    cin >> port;

    serverInfo.sin_addr.s_addr = inet_addr(ip.c_str()); //TODO cambiar esto por el del .config
    serverInfo.sin_port = htons(port);
    serverInfo.sin_family = AF_INET;

    if(inet_pton(AF_INET, ip.c_str(), &serverInfo.sin_addr)<=0) { 
		printf("\nInvalid address/ Address not supported \n"); 
		exit(-1);
	} 
    printf("\n=> Socket successfully with valid address..\n");

    int connectStatus = connect(clientSocket, (struct sockaddr*)&serverInfo, serverAddrLen);

    if (connectStatus == -1) {
        printf("Error falta al conectarse con el servidor\n");
        exit(-1);
    }

    printf("\n=> Sockect client connected to server\n");
    
    int option;

    //Send username to server
    send(clientSocket, username, USERNAME_LEN, 0);
    
    while(1) {
        cout << "\n---- MENU ----\n1.Comenzar juego\n2.Juegos pendientes\n3.Matchs\n4.Salir\nIngrese opcion: "; cin >> option;        
        stringstream strs;strs << option;string message = strs.str();        
        strcpy(recvBuffer, message.c_str());
        send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );        
        switch (option) {
        case 1:
            recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
            printf("%s\nIngrese id de jugador:", recvBuffer);
            scanf("%s", recvBuffer);
            send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );

            for (int i = 0; i < 2; i++) {
                recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
                printf("%s\nIngrese su respuesta:", recvBuffer);
                scanf("%s", recvBuffer);
                send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );
            }            
            
            break;
        case 2:
            recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
            printf("%s\nIngrese id cliente:", recvBuffer);
            scanf("%s", recvBuffer);
            send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );

            for (int i = 0; i < 2; i++) {
                printf("\nEntro\n");
                recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
                printf("%s\nAdivina la respuesta:", recvBuffer);
                scanf("%s", recvBuffer);
                printf("\n------Mi adivinanza es: %s\n",recvBuffer);
                send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );
                printf("\nSalio\n");
            }                  

            for (int i = 0; i < 2; i++) {
                recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
                printf("%s\nIngrese su respuesta:", recvBuffer);
                scanf("%s", recvBuffer);
                printf("\n------Mi respuesta es: %s\n",recvBuffer);
                send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );
            }                  

            break;
        case 3:
            
            break;   
        case 4:
            exit(1);
            break;        
        default:
            break;
        }

        recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);

        memset(recvBuffer, 0, sizeof(recvBuffer));
    }
    close(clientSocket);
    return 0;
}

void start_game(){
    recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
    printf("%s\nIngrese id de jugador:", recvBuffer);
    scanf("%s", recvBuffer);
    send(clientSocket, recvBuffer, strlen(recvBuffer), 0 );

}

void pending_game(){
    
}
