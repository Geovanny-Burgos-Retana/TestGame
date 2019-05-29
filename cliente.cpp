// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#define PORT 8080 

using namespace std;

int main(int argc, char const *argv[]) {
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		printf("\n Socket creation error \n"); 
		return -1;
	}
	cout << "\n=> Socket client has been created..." << endl;

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "192.168.100.13", &serv_addr.sin_addr)<=0) { 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	}
	cout << "\n=> Socket client has been validated..." << endl;

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n"); 
		return -1; 
	}
	cout << "\n=> Socket client has been connected..." << endl;

	int opcionSeleccionada;
	while (1) {
		stringstream strs;strs << opcionSeleccionada;string temp_str = strs.str();
    	strcpy(buffer,(char*) temp_str.c_str());
		cout<<"Ingrese el numero de la funcion que desea realizar: ";
    	cin>>opcionSeleccionada;
		send(sock , buffer , strlen(buffer) , 0 );
		printf("Hello message sent\n");
	}
	return 0; 
} 
