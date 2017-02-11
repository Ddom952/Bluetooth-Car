#ifndef _UART_H_
#define _UART_H_

#define RECEIVER_SIZE 32
#define TRANSMITER_SIZE 32

enum eReceiverStatus { EMPTY, READY, OVERFLOW };
void BLE_COM_UART_Init(void);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char *);

enum eTransmiterStatus { FREE, BUSY };
char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString ( char [] );
enum eTransmiterStatus Transmiter_GetStatus(void);

#endif /* _UART_H_ */
