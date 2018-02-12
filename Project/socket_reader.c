#include "socket_reader.h"
#include "queue.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

extern int socket_fd;
extern Queue eventi;
extern pthread_mutex_t mutex;

void* socket_reader_fnc(void* data){
    
    while(1){
        int nBytes;
        char buffer[MAX_LENGTH];
        
        while((nBytes = read(socket_fd, buffer, MAX_LENGTH)) > 0){
            buffer[nBytes] = '\0';
          //  printf("\n\nLetti %d bytes: %s\n\n", nBytes, buffer);
            
            Event event;
            event.type = EVT_TEXT;
            strcpy(event.msg, buffer);
            
            pthread_mutex_lock(&mutex);
              addToQueue(&eventi, event);
            pthread_mutex_unlock(&mutex);   
        }
       /* if((nBytes = read(socket_fd, buffer, MAX_LENGTH)) <= 0){
            break;
        }
        buffer[nBytes] = '\0';
        
        Event event;
        event.type = EVT_TEXT;
        strcpy(event.msg, buffer);
        
        pthread_mutex_lock(&mutex);
          addToQueue(&eventi, event);
        pthread_mutex_unlock(&mutex);*/
    }
    
}
