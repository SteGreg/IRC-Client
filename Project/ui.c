#include "ui.h"

#include <stdio.h>



void ui_main_menu(){
    
    printf("Benvenuto nella chat IRC. Scegliere un'opzione\n");
    printf("%d) Unisciti ad un canale\n", JOIN);
    printf("%d) Cambia nickname\n", NICK);
    printf("%d) Imposta nome utente\n", USER);
    printf("%d) Imposta il canale corrente\n", SET_CURR_CH);
    printf("%d) Mostra la lista dei canali (a cui sei iscritto)\n", SHOW_CHS);
    printf("%d) Lascia un canale\n", PART);
    printf("%d) TIME\n", TIME);
    
    printf("\n-------------------------------\n");
}
