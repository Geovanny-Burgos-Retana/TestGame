#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "Connections.h"
#include "Database.h"
#define MSG_LEN 256

//Variables
int serverSocket;
int clientSocket;
struct sockaddr_in serverInfo, clientInfo;
int svrAddrSize;
int clntAddrSize;

//Functions
void initServer();
int registerUsername(char*, ClientNode*);
void startChat(void*);
void sendMessageToUser(char[], char[], ClientNode*);

#endif // SERVER_H_INCLUDED
