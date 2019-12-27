#define TERMINATOR '\r'
#define RECIEVER_SIZE 15
#define TRANSMITER_SIZE 15

enum eRecieverStatus { EMPTY, READY, OVERFLOW};
enum eTransmiterStatus {FREE, BUSY};

struct RecieverBuffer{
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};

struct TransmiterBuffer{
	char cData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char ucCharCtr;
};

extern struct TransmiterBuffer sTransmiterBuffer;

void UART_InitWithInt(unsigned int);
void Reciever_PutCharacterToBuffer(char);
void Reciever_GetStringCopy(char *);
enum eRecieverStatus eReciever_GetStatus(void);
char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString(char *);
enum eTransmiterStatus Transmiter_GetStatus(void);
