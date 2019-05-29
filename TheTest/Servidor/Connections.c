#include "Connections.h"

ClientNode* newClient(int sockID, char* IP_addr) {
    //Allocate new client
    ClientNode *newClient = (ClientNode *)malloc(sizeof(ClientNode));

    //Fill new client info
    newClient->next = NULL;
    newClient->prev = NULL;

    newClient->sockID = sockID;
    strncpy(newClient->IP_addr, IP_addr, IP_LEN);

    return newClient;
}

void addClientToConnections(ClientNode* client){
    client->prev = last;
    last->next = client;
    last = client;
}

void removeClientFromConnections(ClientNode * client){
    client->prev->next = client->next;

    if(client != last)
		client->next->prev = client->prev;

    else
        last = client->prev;

    free(client);
}
