
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "events_kb.h"
#include "nonblock.h"

#define ESCAPE_ASCII 27
#define MILISECOND 1000
#define WAITTIME 300


void * print_typing(void* start_of_string);
/* Recibe un puntero al string a imprimir
 * Imrime el string de a una letra por vez con una separacion de WAITTIME 
 * milisegundos entre cada letra
 */  

int main() 
{
    const char* welcome_message = "Bienvenido al generador de excusas. \
Si no hiciste un TP que habia que entregar hoy, selecciona una excusa entre la a y la m. \
Si faltaste a un parcial o final, selecciona una excusa entre la n y la z\n\n";
    
    //arreglo de punteros a char. Tamano = cantidad de letras    
    const char* excuse_pointers['z'-'a'+1] = {

    //excusas para no entregar un TP a tiempo
    "tuve que pasear a mi pez\n",
    "tengo falta de memoria a corto plazo y no se en que carpeta lo guarde\n",
    "mi cabra se comio mi computadora\n",
    "mi axolotl se comio mi computadora\n",
    "lo deje en mis otros zapatos\n",
    "intente pero stackoverflow estaba caido\n",
    "no entendi nada asi que me cambie a industrial\n",
    "Bualo me formateo la compu\n",
    "lo hice pero lo borre porque no tenia espacio para bajarme la serie completa de My Little Pony\n",
    "justo recien cai en la de sudo rm -rf/\n",
    "me di cuenta que me verdadera pasion es assembler de HC11\n",
    "lo tengo en el drive, cuando ande el wifi del ITBA te lo mando\n",
    "nadie me dijo que si o si habia que conectar un pin de la rpi a tierra\n",
    
    //excusas para faltar al parcial
    "no tenia ganas\n",
    "juraba que era en dos dias\n",
    "me quede sin nafta para la bici\n",
    "la alfombra voladora me dejo a pata\n",
    "me dijieron que la H me dejaba en la puerta del ITBA\n",
    "me regalaron un calcetin. Ya soy libre",
    "se rompio el boton de planta baja de mi ascensor\n",
    "se murio mi pez\n",
    "llovia y no queria arruinar mis guantes nuevos\n",
    "me gano pachorra\n",
    "primero un elfo domestico no me dejo entrar a la estacion, y despues un arbol malvado ataco mi auto volador\n",
    "los Lannisters me mantuvieron cautivo todo el dia\n",
    "estaba pronosticado el fin del mundo. Menos mal que sigo vivo para poder darlo la semana que viene\n"
    };
    printf("%s", welcome_message);  //Imprimir mensaje de bienvenida e instrucciones
    start_read_kb();                //comienza a guadar el input del teclado
    system("stty -echo");           //evita que se muestren las teclas apretadas en pantalla
    pthread_t printing_thread;      //crea el tag del thread que imprime strings
    char key;                       //contiene las teclas apretadas por el usuario
    while (key != ESCAPE_ASCII)     //salir del programa cuando se aprete la tecla 'Esc'
    {    
        key = get_next_event();
        if (key>='a' && key<='z')
        {
            pthread_create(&printing_thread, NULL, print_typing, excuse_pointers[key-'a']);
            pthread_join(printing_thread, NULL);
        }
    }

    system("stty echo");
    stop_read_kb();
    return 0;
}



void* print_typing(void* start_of_string)  
{
    int i = 0;    
    char key;                                   //contiene caracter a imprimir
    while(((char*)start_of_string)[i]!= '\0')   //repetir hasta que se llegue al terminador
    {               
        key = (((char*)start_of_string)[i]);    //dar a key el valor del proximo caracter a imprimir
        printf("%c",key);
        fflush(stdout);                         //imprime de a un caracter por vez
        usleep(WAITTIME*MILISECOND);            //tiempo de espera entre la impresion de los caracteres
        i++;	
    }
}
 