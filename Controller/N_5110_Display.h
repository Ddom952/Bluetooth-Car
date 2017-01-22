#ifndef N_5110_Display_H
#define N_5110_Display_H
 
#include "mbed.h"
 
/*
 * This library is designed to make it easy for anyone to get the Nokia 5110 display 3.3V module up and running without delay
 * It provides a convenient interface for printing single characters or strings of characters and vertical bar graphs, all at various magnifications.
 * It is free to use and modify. I accept NO liability for malfunctions or damage caused by this software
 * I hope it is useful to the community and am open to suggestions for improvement.
 *
 *
 * ---Example code---
 * 
 * #include "mbed.h"
 * #include "N_5110_Display.h"
 *
 * N_5110_Display Display( p5, p6, p7, p8, p9, p10 );
 *
 * int main()
 * {
 *     Display.setCharPos( 0, 0 );              //x pos = 0, y pos = 0
 *     Display.printString( 'Bar', 2, 3 );      //output string with char width 2, char height 3
 *
 *     Display.setCharPos( 0, 3 );              //x pos = 0, y pos = 3
 *     Display.printString( 'Graph', 2, 3 );    //output string with char width 2, char height 3
 *
 *     Display.setCharPos( 11, 0 );             //x pos = 11, y pos = 0 .... X pos is 11 to allow for a bar graph with width 3
 *     Display.VertBarGraph( 40, 3, 6 );        //generate a vertical bar graph 40% full with width = 3 char, height = 6 char
 *
 *     while (1)
 *     {
 *
 *     }
 * }
 *
 *
 * ---End of example code
*/
class N_5110_Display {
 
    public:
 
        //mosi, miso, sclk, Data/Command, Reset, ChipSelect
        N_5110_Display(  PinName _mosi, PinName _miso, PinName _sclk, PinName _dc, PinName _reset, PinName _cs);
        int print1char( unsigned char c, unsigned char Xmag, unsigned char Ymag );
        void printString( char * str2prt, unsigned char Xmag, unsigned char Ymag);
        void VertBarGraph( int Percentage, unsigned char Xmag, unsigned char Ymag );
        void initDisplay( void );
        void clrDisp( void );
        int setCharPos( int x, int y );                                             //x axis position (0 to 13) y axis position (0 to 5)
        
    private:
    
        void clrMagArray( unsigned char Xmag, unsigned char Ymag, bool FullWidth );
        void magChar( unsigned char c, unsigned char Xmag, unsigned char Ymag );
        void smoothEdges( unsigned char Xmag, unsigned char Ymag );
        void setDispPos( int DispX, int DispY );                                    //DispX axis (0 to 84) DispY axis (0 to 5)
        int outputMagData (unsigned char Xmag, unsigned char Ymag, bool FulWidth);
 
        DigitalOut dc;
        DigitalOut rst;
        DigitalOut cs;
        SPI spi;
        unsigned char PixX, CharX, CharY;
        unsigned char magData[36][6];
};
 
 
#endif