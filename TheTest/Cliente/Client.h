#ifndef CLIENT_H
#define CLIENT_H

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
#define MSG_LEN 256
#define USERNAME_LEN 32
#define IP_LEN 16


void validInput();

void createClient();

void initialize(struct sockaddr_in*,struct sockaddr_in*);

void connection(struct sockaddr_in*, struct sockaddr_in*);

void reciveMessages();

void sendMessages();

int start();

#endif /* CLIENT_H */

