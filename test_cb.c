#include <stdio.h>
#include "char_buffer.h"

int main (void)
{
    int error;
    char first_in;
    char string[]="Hola mundo 12341234"; //"Hola mundo" son 10 caracteres
 
    int i=0;
 
    char_buffer_t cb = create_cb(10); //Crea un buffer circular de 10 elementos
 
    while (!is_full_cb(cb))
    /* Esta condicion se verificara cuando se hayan escrito 10 caracteres.
     * Es equivalente a hacer "while (error) { error = write_cb... }*/
    {
        write_cb(&cb, string[i]);   //Escribe del string al buffer
        i++;
    }
    
    while (error)
    /* Se saldra del loop cuando se hayan leido todos los caracteres.
     * Es equivalente a hacer "while (cb.n_written)" e ignorar el error */
    {
        putchar(read_cb(&cb, &error));
    }    
    putchar('\n');
    
    free_cb(&cb);   //Libera la memoria asignada al buffer
}