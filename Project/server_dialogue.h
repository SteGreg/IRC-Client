#define MAX_SERVERS 200
#define SERVER_CONFIG_NAME "servers.config"

typedef struct{
    char server_name[256];
    int  server_port;
}ServerInfo;

ServerInfo server_list[MAX_SERVERS];

void server_dialogue_init();

void server_dialogue_add(ServerInfo info);

void server_dialogue_ask(ServerInfo *out_info);
