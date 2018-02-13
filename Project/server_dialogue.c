#include "server_dialogue.h"

#include <stdio.h>
#include <string.h>

void server_dialogue_init(){
    FILE* f = fopen(SERVER_CONFIG_NAME, "rt");
    if(!f){
        printf("File %s non trovato.\n", SERVER_CONFIG_NAME);
        return;
    }
    
    char buffer[256];
    int port = 0;
    int i = 0;
    while(fscanf(f, "%s %d", buffer, &port) != EOF){
        
        server_list[i].server_port = port;
        strcpy(server_list[i].server_name, buffer);
        
        i++;
    }
    
    strcpy(server_list[i].server_name, "/END_LIST");  // ...
    
    fclose(f);
}

void server_dialogue_add(ServerInfo info){
    FILE* f = fopen(SERVER_CONFIG_NAME, "at");
    if(!f){
        printf("File %s non trovato.\n", SERVER_CONFIG_NAME);
        return;
    }
    
    fprintf(f, "%s %d", info.server_name, info.server_port);
    
    fclose(f);
}

void server_dialogue_ask(ServerInfo *out_info){
    
    ServerInfo info;
    int i = 0;
    
    printf("Scegliere il server a cui collegarsi:\n");
    while(strcmp(server_list[i].server_name, "/END_LIST") != 0){
        
        printf("%d) %s (porta %d).\n", i, server_list[i].server_name, server_list[i].server_port);
        
        i++;
    }
    
    printf("%d) Aggiungi un server alla lista.\n", i);
    
    int risp;
    scanf("%d", &risp);
    
    if(risp < i){
        info = server_list[risp];
    }else{
        char nome[256]; int porta;
        printf("Inserire il nome\n");
        scanf("%s", nome);
        printf("Inserire la porta\n");
        scanf("%d", &porta);
        
        info.server_port = porta;
        strcpy(info.server_name, nome);
        
        server_dialogue_add(info);
    }
    
    printf("--------------------------\n");
    
    *out_info = info;
}
