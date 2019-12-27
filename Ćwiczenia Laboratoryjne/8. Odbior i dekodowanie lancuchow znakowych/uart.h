#define TERMINATOR '/'
#define RECIEVER_SIZE 12

enum eRecieverStatus { EMPTY, READY, OVERFLOW};

void UART_InitWithInt(unsigned int);
//void Reciever_PutCharacterToBuffer(char);
void Reciever_GetStringCopy(char *);
enum eRecieverStatus eReciever_GetStatus(void);
