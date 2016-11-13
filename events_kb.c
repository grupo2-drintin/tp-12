#include "events_kb.h"
#include "nonblock.h"
#include "char_buffer.h"
#include <pthread.h>
#include <stdio.h>

#ifndef TRUE
#define TRUE    1
#define FALSE   0
#endif //TRUE

#define BUFFER_SIZE 200

static void * read_kb_thread();

static int exit=TRUE;
static char_buffer_t buffer;


void start_read_kb(void)
{
    nonblock(NB_ENABLE);
    buffer=create_cb(BUFFER_SIZE);
    pthread_t r_kb;
    
    pthread_create(&r_kb, NULL, read_kb_thread, NULL);
}



static void * read_kb_thread()
{
    char last_in;
    
    while (exit)
    {
        if(kbhit())
        {
            last_in=getchar();
            
            if(!is_full_cb(buffer))
            {
                write_cb(&buffer, last_in);
            }
            else
            {
                exit=FALSE;
            }
        }
    }
}

char get_next_event(void)
{
    int could_read;
    
    char next_event = read_cb(&buffer, &could_read);
    
    if (!could_read)
    {
        next_event=FALSE;
    }
    
    return next_event;
}



void stop_kb_read(void)
{
    exit=FALSE;
    nonblock(NB_DISABLE);
    free_cb(&buffer);
}