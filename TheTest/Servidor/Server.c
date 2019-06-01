#include "Server.h"

void initServer(){
    int optSock = 1;
        
    serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (serverSocket == -1) {
        perror("\n=><= Socket failed"); 
		exit(EXIT_FAILURE);
    }
    printf("\n=> Socket successfully created..\n");
    
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optSock, sizeof(optSock))) {
		perror("\n=><= Socket setsockopt failed..\n"); 
		exit(EXIT_FAILURE); 
	} 

    svrAddrSize= sizeof(serverInfo);
    clntAddrSize= sizeof(clientInfo);

    memset(&serverInfo, 0, svrAddrSize);
    memset(&clientInfo, 0, clntAddrSize);
    
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(9001);
    serverInfo.sin_addr.s_addr = INADDR_ANY/*inet_addr("172.19.55.217")*/;
    
    if(bind(serverSocket, (struct sockaddr *)&serverInfo, svrAddrSize) == -1){
        perror("\n=><= Socket bind failed\n"); 
		exit(EXIT_FAILURE); 
    }
    printf("\n=> Socket successfully binded..\n");

    if(listen(serverSocket, 5) == -1){
        perror("\n=><= Socket listen failed\n"); 
		exit(EXIT_FAILURE); 
    }
    printf("\n=> Socket successfully listening..\n"); 

    getsockname(serverSocket, (struct sockaddr*) &serverInfo, (socklen_t*) &svrAddrSize);
    printf("\n=> Server listening in: %s, port: %d\n\n", inet_ntoa(serverInfo.sin_addr), ntohs(serverInfo.sin_port));

}

void startChat(void* nc){
    char *hello = "Hello from server"; 

    char recvBuffer[MSG_LEN];
    char sendBuffer[MSG_LEN];
    int quit = 0;
    ClientNode* client = (ClientNode*)nc;

    if(registerUsername(sendBuffer, client) != 1){
        quit = 1;
    }

    while(quit == 0){
        int msgRecv = recv(client->sockID, recvBuffer, sizeof(recvBuffer), 0);

        if (msgRecv == 0){
            printf("Desconectando al cliente: %s\n\n", client->username);
            break;
        }
        
        switch (atoi(recvBuffer)) {
        case 1:
            get_users_no_start_game(client->user_id);
            hello = "Hello message sented form server";
            send(client->sockID , hello , strlen(hello) , 0 ); 
            printf("Hello message sent OPT1\n");					
            break;
        case 2:
            hello = "Hello message sented form server";
            send(client->sockID , hello , strlen(hello) , 0 ); 
            printf("Hello message sent OPT2\n");
            break;
        case 3:	
            printf("=> Client desconnected..\n");
            exit(1);
            break;
        default:
            break;
        }

        
        //Clean buffers
        memset(recvBuffer, 0, sizeof(recvBuffer));
        memset(sendBuffer, 0, sizeof(sendBuffer));
    }


    //End connection
    close(client->sockID);
    removeClientFromConnections(client);
}

int registerUsername(char* sendBuffer, ClientNode* client){
    char username[USERNAME_LEN];

    //Set username
    int usrRecv = recv(client->sockID, username, USERNAME_LEN, 0);

    if(usrRecv <= 0 || strlen(username) <= 0){
        printf("El cliente %s no ingresó un nombre\n", client->IP_addr);
        return 0;
    }

    else {
        //Get the client's username and store it
        strncpy(client->username, username, strlen(username));        

        // INSERTAR O RECUPERAR EL ID DEL USUARIO DE LA BASE DE DATOS

        // AGREGAR EL ID RECUPERADO AL OBJETO DEL CLIENTE

        client->user_id = get_idUser(username);

        printf("\n=> Cliente con identificar: %d\n", client->user_id);

        memset(username, 0, sizeof(username));

        return 1;
    }

}

void sendMessageToUser(char recvBuffer[], char sendBuffer[], ClientNode* client){

}
