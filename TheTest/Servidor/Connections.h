#ifndef CONNECTIONS_H_INCLUDED
#define CONNECTIONS_H_INCLUDED
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"

//Variables
typedef struct Client{
    int sockID;
    struct Client* next;
    struct Client* prev;
    char IP_addr[IP_LEN];
    char username[USERNAME_LEN];
} ClientNode;

ClientNode *root, *last;

//Functions
ClientNode* newClient(int, char*);
void addClientToConnections(ClientNode*);
void removeClientFromConnections(ClientNode*);

#endif // CONNECTIONS_H_INCLUDED
