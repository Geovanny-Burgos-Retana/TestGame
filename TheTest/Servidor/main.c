#include <stdio.h>
#include <stdlib.h>
#include "Server.h"
#include <pthread.h>

int main(){
        
    initServer();

    root = newClient(serverSocket, inet_ntoa(serverInfo.sin_addr));
    last = root;

    while(1){
        
        printf("\n=> Wait for client...\n");
        clientSocket = accept(serverSocket, (struct sockaddr*) &clientInfo, (socklen_t*) &clntAddrSize);

        getpeername(clientSocket, (struct sockaddr*) &clientInfo, (socklen_t*) &clntAddrSize);
        char* clientIP = inet_ntoa(clientInfo.sin_addr);
        printf("\nNew client connected form IP: %s\n",clientIP);

        ClientNode* nc = newClient(clientSocket, clientIP);
        addClientToConnections(nc);

        if (fork() == 0) {
            conectionDB();
            startChat(nc);
        }
        fflush(stdout);
        /*pthread_t tid;
        pthread_create(&tid, NULL, (void*)startChat, (void*)nc);*/
    }

    close(serverSocket);
    return 0;
}
