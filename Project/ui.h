
typedef enum{
    USER,
    NICK,
    JOIN,
    PART,
    QUIT,
    TOPIC,
    MSG,
    WHO,
    WHOIS,
    TIME,
    
    SET_CURR_CH,//imposta canale corrente
    SHOW_CHS    //Mostra canali
}CMD;

void ui_main_menu();
