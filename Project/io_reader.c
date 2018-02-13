#include "socket_reader.h"
#include "queue.h"
#include "ui.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

extern Queue eventi;
extern pthread_mutex_t mutex;

void* io_reader_fnc(void* data){
    while(1){
        
        int res;
        fscanf(stdin, "%d", &res);
        
        Event event;
        event.type = EVT_COMMAND;
        
        switch(res){
        
            case NICK:
                {/*
                    char nick[256];
                    memset(nick, 0, sizeof(nick));
                    printf("Inserire il nick\n");
                    scanf("%s", nick);
                    
                    printf("%s", nick);
                    char buffer[512];
                    memset(buffer, 0, sizeof(buffer));
                    strcat(buffer, "NICK ");
                    strcat(buffer, nick); 
                    strcpy(event.msg, buffer);*/
                    char buffer[256];
                    memset(buffer, 0, sizeof(buffer));
                    sprintf(buffer, "NICK guest\r\n");
                    printf("Prova: %s\n", buffer);
                    strcpy(event.msg, buffer);
                    
                    
                    break;
                }
            
            case USER:
                {
                    strcpy(event.msg, "a a a a\r\n");
                    
                    break;
                }
            case TIME:
                {
                    sprintf(event.msg, "TIME\r\n");
                    
                    break;
                }
            
            default:
                continue;   //Ricomincia il loop dall'inizio (saltando quindi addToQueue())
            break;
        }
        
        pthread_mutex_lock(&mutex);
            addToQueue(&eventi, event);
        pthread_mutex_unlock(&mutex);
    }
}
