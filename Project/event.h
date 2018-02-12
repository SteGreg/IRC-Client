#define MAX_LENGTH 512

typedef enum{
    EVT_COMMAND,
    EVT_TEXT
}EventType;

struct SEvent{
    char msg[MAX_LENGTH];
    EventType type;
};
typedef struct SEvent Event;
