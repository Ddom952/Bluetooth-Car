#include "command_decoder.h"
#include "string.h"
#include "mbed.h"
#include "N_5110_Display.h"

#include "MMA8451Q.h"

#if   defined (TARGET_KL25Z) || defined (TARGET_KL46Z)
  PinName const SDA = PTE25;
  PinName const SCL = PTE24;
#elif defined (TARGET_KL05Z)
  PinName const SDA = PTB4;
  PinName const SCL = PTB3;
#elif defined (TARGET_K20D50M)
  PinName const SDA = PTB1;
  PinName const SCL = PTB0;
#else
  #error TARGET NOT DEFINED
#endif

#define MMA8451_I2C_ADDRESS (0x1d<<1)
#define BUFFER_SIZE 20

int GetString (char pcReciverBuffer[], unsigned char ucBufferSize);
extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

Serial Blue(USBTX, USBRX);  // plytka <-> Bt : Rx <-> Rx, Tx <-> Tx
DigitalIn Button1(PTC6);
DigitalIn Button2(PTC5);
enum state {IDLE,DRIVE, GETDATA};

DigitalOut L1(PTC16);
DigitalOut L2(PTC13);
DigitalOut L3(PTC12);

N_5110_Display Display( PTD2, PTD3, PTD1, PTD0, PTD5, PTA13 );  //mosi, miso, sclk, Data/Command, Reset, ChipSelect

int main(void){
    char    acRecBuffer[BUFFER_SIZE];
    state ControllerState = IDLE;
    MMA8451Q acc(SDA, SCL, MMA8451_I2C_ADDRESS);

    Display.clrDisp();
    Display.setCharPos( 0, 0 );              //x pos = 0, y pos = 0
    Display.printString( "Lukasz", 2, 3 );      //output string with char width 2, char height 3
    
    while (true) {
       
        switch(ControllerState){
            case IDLE:
                Display.clrDisp();
                Display.setCharPos( 0, 0 );              //x pos = 0, y pos = 0
                Display.printString( "STOP", 2, 3 );      //output string with char width 2, char height 3
                L1 = 1; L2 = 0; L3 = 0;
                ControllerState = Button1 ? (Button2 ? IDLE : GETDATA) : DRIVE;   // 0 jak wcisniety
                //if (Button1 == 0 | Button2 == 0){
                //    Display.clrDisp();
                //}
                break;
            case DRIVE:
                Display.clrDisp();
                Display.setCharPos( 0, 0 );              //x pos = 0, y pos = 0
                Display.printString( "DRIVING", 2, 3 );
                L1 = 0; L2 = 1; L3 = 0;
                ControllerState = Button1 ? DRIVE : IDLE;
                
                float x, y, z;
                x = acc.getAccX();
                y = acc.getAccY();
                z = acc.getAccZ();

                
                if (Blue.writeable()){
                    Blue.printf("x=%1.2f y=%1.2f z=%1.2f\n", x, y, z);
                }
                break;
            case GETDATA:
                Display.clrDisp();
                Display.setCharPos( 0, 0 );              //x pos = 0, y pos = 0
                Display.printString( "Data:", 2, 3 );
                Display.setCharPos( 0, 3 );
                
                L1 = 0; L2 = 0; L3 = 1;
                ControllerState = Button2 ? GETDATA : IDLE;
                if (Blue.readable()){
                    GetString(acRecBuffer, BUFFER_SIZE);
                    Display.printString(acRecBuffer,2,3);
                    wait(2);  
                }
                if (Blue.writeable()){
                    Blue.printf("DataOK\n");
                }
                break;
            default:
                break;
            
        }
        wait(0.2f);
        
   
    }
}


/***************************************************************************/

int GetString (char pcReciverBuffer[], unsigned char ucBufferSize){
    unsigned char ucCharCounter =0;
    while(1){
        if(ucCharCounter == ucBufferSize){
            return 1;
        }
        else{
            pcReciverBuffer[ucCharCounter] = Blue.getc();
            if(pcReciverBuffer[ucCharCounter] == '\r'){
                pcReciverBuffer[ucCharCounter] = NULL;
                return 0;  
            }
            else{
                ucCharCounter++;
            }
        }
    }
}