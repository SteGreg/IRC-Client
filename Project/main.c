#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <string.h>

#include "types.h"
#include "queue.h"
#include "client.h"
#include "socket_reader.h"
#include "io_reader.h"

Queue eventi;

pthread_t th_sockReader, th_ioReader;
pthread_mutex_t mutex;

int main(int nArgs, char** args){
    
    if(nArgs == 1){
        printf("Specificare il nome del server a cui collegarsi e la porta.\n");
        return 1;
    }
   
    initQueue(&eventi);
    
    client_connect(args[1], atoi(args[2]));
    
    pthread_mutex_init(&mutex, NULL);
    
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
                    //Invia a socket_fd...
                    break;
                }
            }
            
        }
    }
    
    pthread_mutex_destroy(&mutex);
    client_disconnect();
    return 0;
}
