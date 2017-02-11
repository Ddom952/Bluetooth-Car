#include "uart.h"
#include "my_string.h"
#include "fsl_uart.h"

// Macro
#define TERMINATOR '.'

/* UART instance and clock */
#define BLE_COM_UART UART3
#define BLE_COM_UART_CLKSRC UART3_CLK_SRC
#define BLE_COM_UART_IRQn UART3_RX_TX_IRQn
#define BLE_COM_UART_IRQHandler UART3_RX_TX_IRQHandler
#define BLE_COM_UART_BAUDRATE 115200U

/************ Structures definitions and declarations *************/

struct ReceiverBuffer
{
	char cData [RECEIVER_SIZE];
	unsigned char ucCharCtr;
	enum eReceiverStatus eStatus;
};

struct ReceiverBuffer sRxBuffer;

struct TransmiterBuffer
{
	char cData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char cCharCtr;
};

struct TransmiterBuffer sTransmiterBuffer;

/************ Definitions of receiver's functions  *************/

void Receiver_putCharacterToBuffer ( char cCharacter )
{
		if ( ( cCharacter == TERMINATOR ) && ( sRxBuffer.eStatus != OVERFLOW ) )
		{
			sRxBuffer.cData[sRxBuffer.ucCharCtr] = (intptr_t) NULL;
			sRxBuffer.eStatus = READY;
			sRxBuffer.ucCharCtr = 0;
		}
		else if ( sRxBuffer.ucCharCtr >= ( RECEIVER_SIZE - 1 ) )
			sRxBuffer.eStatus = OVERFLOW;
		else
		{
			sRxBuffer.cData[sRxBuffer.ucCharCtr] = cCharacter;
			sRxBuffer.ucCharCtr = sRxBuffer.ucCharCtr + 1;
		}
}


enum eReceiverStatus eReceiver_GetStatus(void)
{
	return ( sRxBuffer.eStatus );
}

void Receiver_GetStringCopy( char * ucDestination )
{
		unsigned char ucCharCounter;
	
		for(ucCharCounter = 0; sRxBuffer.cData[ucCharCounter]; ucCharCounter++ )
		{
			*ucDestination = sRxBuffer.cData[ucCharCounter];
			ucDestination++;
		}
		*ucDestination = (intptr_t) NULL;
		sRxBuffer.eStatus = EMPTY;
}

/************ Definitions of transmiter's functions  *************/

char Transmiter_GetCharacterFromBuffer(void)
{
	/*
	switch ( sTransmiterBuffer.fLastCharacter )
	{
		case 0:
				if ( sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr] != (char) NULL )
				{
					//sTransmiterBuffer.cCharCtr++;
					return ( sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr++] );
				}
				else
				{
					sTransmiterBuffer.fLastCharacter = 1;
					sTransmiterBuffer.eStatus = FREE;
					return '\r';
				}
		case 1:
				sTransmiterBuffer.eStatus = FREE;
				return NULL;
		default:
				return NULL;
	}
	*/
	__asm__("NOP");
	return ' ';
}

void Transmiter_SendString ( char cString[])
{
	CopyString ( ( char * ) cString, sTransmiterBuffer.cData );
	sTransmiterBuffer.cCharCtr = 0;
	sTransmiterBuffer.eStatus = BUSY;
	sTransmiterBuffer.fLastCharacter = 0;
	//U0THR = sTransmiterBuffer.cData[0];
}

enum eTransmiterStatus Transmiter_GetStatus(void)
{
	return sTransmiterBuffer.eStatus;
}

void BLE_COM_UART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(BLE_COM_UART))
    {
        data = UART_ReadByte(BLE_COM_UART);

		Receiver_putCharacterToBuffer(data);
    }
}

void BLE_COM_UART_Init(void)
{
    uart_config_t config;

	/*
	 * config.baudRate_Bps = 115200U;
	 * config.parityMode = kUART_ParityDisabled;
	 * config.stopBitCount = kUART_OneStopBit;
	 * config.txFifoWatermark = 0;
	 * config.rxFifoWatermark = 1;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */

	UART_GetDefaultConfig(&config);
	config.baudRate_Bps = BLE_COM_UART_BAUDRATE;
	config.stopBitCount = kUART_OneStopBit;
	config.enableTx = false;
	config.enableRx = true;

	UART_Init(BLE_COM_UART, &config, CLOCK_GetFreq(BLE_COM_UART_CLKSRC));

	/* Enable RX interrupt. */
	UART_EnableInterrupts(BLE_COM_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
	EnableIRQ(BLE_COM_UART_IRQn);
}
