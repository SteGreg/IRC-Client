#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <string.h>

#include "types.h"
#include "queue.h"
#include "server_dialogue.h"
#include "client.h"
#include "socket_reader.h"
#include "ui.h"
#include "io_reader.h"

Queue eventi;

pthread_t th_sockReader, th_ioReader;
pthread_mutex_t mutex;

int main(int nArgs, char** args){
    
    ServerInfo server_info;
    
    server_dialogue_init("servers.config");
    server_dialogue_ask(&server_info);
    
    initQueue(&eventi);
    
    client_connect(server_info.server_name, server_info.server_port);
    
    pthread_mutex_init(&mutex, NULL);
    
    ui_main_menu();
    
    if(pthread_create(&th_sockReader, NULL, socket_reader_fnc, NULL) != 0)
        printf("Errore nella creazione del thread\n");
    
    if(pthread_create(&th_ioReader, NULL, io_reader_fnc, NULL) != 0)
        printf("Errore nella creazione del thread\n");
    
    
    int i = 1;
    while(1){
        //Scorri la coda degli eventi
        Event currentEvent;
    
        int res = FALSE;
        pthread_mutex_lock(&mutex);
            res = removeFromQueue(&eventi, &currentEvent);
        pthread_mutex_unlock(&mutex);
        
        if(res == TRUE){
        
            switch(currentEvent.type){
                case EVT_TEXT:
                {
                    printf("%d) %s", i++, currentEvent.msg);
                    
                    break;
                }
                case EVT_COMMAND:
                {                    
                    printf("Bytes mandati: %d\n", write(socket_fd, currentEvent.msg, strlen(currentEvent.msg)));
                    break;
                }
            }
            
        }
    }
    
    pthread_mutex_destroy(&mutex);
    client_disconnect();
    return 0;
}
