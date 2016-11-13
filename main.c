
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "events_kb.h"
#include "nonblock.h"

#define  ONE_MS    	1000	   // One mseg

void * print_typing(void* start_of_string);  

int main() 
{
    //arreglo de punteros a char. Tamano = cantidad de letras    
    const char* excuse_pointers['z'-'a'+1] = {

    //excusas para no entregar un TP a tiempo
    "Tuve que pasear a mi pez",
    "Tengo falta de memoria a corto plazo y no se en que carpeta lo guarde",
    "Mi cabra se comio mi computadora",
    "Mi axolotl se comio mi computadora",
    "Lo deje en mis otros zapatos",
    "Intente pero stackoverflow estaba caido",
    "Tarea? Yo? Sabes quien soy?",
    "Bualo me formateo la compu",
    "Lo hice pero lo borre porque no tenia espacio para bajarme la serie completa de My Little Pony",
    "justo recien cai en la de sudo rm -rf/",
    "Para que hacerlo si C ya es un lenguaje muerto?",
    "Lo tengo en el drive, cuando ande el wifi del ITBA te lo mando",
    "Nadie me dijo que si o si habia que conectar un pin de a rpi a tierra",
    
    //excusas para faltar al parcial
    "Lamento no haber podido ir, pero no tenia ganas",
    "No te puede creer! Juraba que era en dos dias",
    "Me quede sin nafta para la bici",
    "La alfombra voladora me dejo a pata"
    };
    
    start_read_kb();
    char key;
    while((key=get_next_event())!= '\n')
    {
        if (key >= 'a' && key <= 'q')
        {
            printf("%s", excuse_pointers[key-'a']);
        }
    }
    
    
    /*pthread_t printing_thread;
    
    char i = get_next_event();
    
    while (1)
    {    
        i = get_next_event();
        if (i>='a' && i<='q')
        {
            pthread_create(&printing_thread, NULL, print_typing, excuse_pointers[i-'a']);
            //pthread_join(printing_thread, NULL);
        }
    }*/
    return 0;
}

void * print_typing(void* start_of_string)  
{
    int i = 0;    
    char key;                               //contiene caracter a imprimir
    while(key = ((char*)start_of_string)[i])  //repetir hasta que se llegue al terminador
    {               
        usleep(1000*ONE_MS);                 // 100ms * 
        
        nonblock(NB_DISABLE);
        putchar(key);
        nonblock(NB_ENABLE);
        
        i++;	
    }
}
