
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
    "Tuve que pasear a mi pez\n",
    "Tengo falta de memoria a corto plazo y no se en que carpeta lo guarde\n",
    "Mi cabra se comio mi computadora\n",
    "Mi axolotl se comio mi computadora\n",
    "Lo deje en mis otros zapatos\n",
    "Intente pero stackoverflow estaba caido\n",
    "Tarea? Yo? Sabes quien soy?\n",
    "Bualo me formateo la compu\n",
    "Lo hice pero lo borre porque no tenia espacio para bajarme la serie completa de My Little Pony\n",
    "justo recien cai en la de sudo rm -rf/\n",
    "Para que hacerlo si C ya es un lenguaje muerto?\n",
    "Lo tengo en el drive, cuando ande el wifi del ITBA te lo mando\n",
    "Nadie me dijo que si o si habia que conectar un pin de la rpi a tierra\n",
    
    //excusas para faltar al parcial
    "no tenia ganas\n",
    "juraba que era en dos dias\n",
    "me quede sin nafta para la bici\n",
    "la alfombra voladora me dejo a pata\n",
    "me dijieron que la H me dejaba en la puerta del ITBA\n",
    "me regalaron un calcetin. Ya soy libre",
    "se rompio el boton de planta baja de mi ascensor\n",
    "se muerio mi pez\n",
    "llovia y no queria arruinar mis guantes nuevos\n",
    "me gano pachorra\n",
    "primero un elfo domestico no me dejo entrar a la estacion, y despues un arbol malvado ataco mi auto volador\n",
    "los Lannisters me mantuvieron cautivo todo el dia",
    "estaba pronosticado el fin del mundo. Menos mal que sigo vivo para poder darlo la semana que viene"
    };
    
    start_read_kb();   
    pthread_t printing_thread;    
    while (1)
    {    
        char i = get_next_event();
        if (i>='a' && i<='q')
        {
            pthread_create(&printing_thread, NULL, print_typing, excuse_pointers[i-'a']);
            pthread_join(printing_thread, NULL);
        }
    }
    stop_kb_read();
    return 0;
}

void* print_typing(void* start_of_string)  
{
    int i = 0;    
    char key;                               //contiene caracter a imprimir
    while(((char*)start_of_string)[i]!= 0)  //repetir hasta que se llegue al terminador
    {               
        key = (((char*)start_of_string)[i]);
        printf("%c",key);
        sleep(0.01);
        i++;	
    }
}
 