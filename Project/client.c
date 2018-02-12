#include "client.h"
#include "debug.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
    TODO: Controllo errori
*/

void client_connect(const char *server_name, unsigned short int port){
    
    char ipv4[16];
    
    //Ottieni l'ip del server da server_name
    struct hostent *host_info = gethostbyname(server_name);
    if(!host_info) printf("Errore client: %s non trovato\n", server_name);
    
    
    char** addr_list = host_info->h_addr_list; //Lista dei vari indirizzi ip
    //prendi il primo elemento dell'array
    struct in_addr *in = (struct in_addr*)*addr_list; 
    strcpy(ipv4, inet_ntoa(*in));
    
    
    //Crea il socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);    //Tcp
    if(socket_fd == -1) _ERROR("Errore client");
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ipv4);
    
    int result = connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(result == -1) _ERROR("Errore client");
    else
        printf("Collegato a %s\n", server_name);
}

void client_disconnect(){
    close(socket_fd);
}
