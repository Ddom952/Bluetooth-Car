#include "mbed.h"
#include "N_5110_Display.h"
#include "N_5110_Font.h"
 
 
N_5110_Display::N_5110_Display(  PinName _mosi, PinName _miso, PinName _sclk, PinName _dc, PinName _reset, PinName _cs): 
                        spi( _mosi, _miso, _sclk ), dc( _dc ), rst( _reset ), cs( _cs )
{
    initDisplay();
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::initDisplay()
{
    rst=0;                  //display reset
    cs=1;                   //Chip Disabled
    
    wait(0.5);              //allow chip to settle for half second
        
    spi.format(8,3);        //set the SPI interface perameters for the Display
    spi.frequency(1000000); //1 MHz clock speed
    PixX = 0;               //zero the x, y variables
    CharX = 0;
    CharY = 0;
    
    rst=1;                  //display reset done
    
    dc=0;                   //select Control mode
    cs=0;                   //Chip Enabled
        
    spi.write(0x21);        //Function Set (Extenden Instructions)
    spi.write(0x04);        //set 'Temp Coef' value
    spi.write(0x13);        //set 'Bias' value
    spi.write(0xBF);        //set 'V_op' value
    spi.write(0x22);        //Function Set (Basic Instructions)
    spi.write(0x0C);        //Display Control
        
    clrDisp();              //Clear the Display
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::clrDisp()
{
    long x;
 
    dc=1;                   //select Data mode
    cs=0;                   //Chip Enabled
    
    for (x=0; x<504; x++)   //Clear the display memory
    {
        spi.write( 0 );
    }
    
    cs=1;                   //Chip Disabled
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::setDispPos(int DispX, int DispY)
{
    unsigned char Xtemp, Ytemp;
 
    Xtemp = DispX | 0x80;       //add in the column select BIT
    Ytemp = (DispY & 0x07) | 0x40;
    
    dc=0;                       //select Control mode
    cs=0;                       //Chip Enabled
        
    spi.write(Xtemp);           //Set the column value
    spi.write(Ytemp);           //set the row value
    
    cs=1;                       //Chip Disabled
}
 
//----------------------------------------------------------------------
 
int N_5110_Display::setCharPos(int x, int y)
//x is the character column number 0 to 13. y is the character row number 0 to 5.
//The column is multiplied by 6 to get the display column value, as each 5 x 8 char occupies a 6 x 8 space
{
    unsigned char Xacc;
 
    if (x>13 || y>5) return -1; //check magnitude of co-ordinates and store
    
    Xacc = x<<2;                //multiply the char column (x) by 6 to get the Display column
    Xacc = Xacc + (x<<1);
 
    PixX = Xacc;
    CharX = x;
    CharY = y;
 
    setDispPos(PixX, CharY);
    
    return 0;
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::clrMagArray( unsigned char Xmag, unsigned char Ymag, bool FullWidth )
{
    unsigned char magDataX, magDataY, width;
 
    width = FullWidth?6:5;
    
    for (magDataX=0; magDataX<Xmag*width; magDataX++)   //clear the magnification array
    {
        for (magDataY=0; magDataY<Ymag; magDataY++)
        {
            magData[magDataX][magDataY] = 0;
        }
    }
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::smoothEdges( unsigned char Xmag, unsigned char Ymag )
//Quick and dirty character smoothing but only if there is magnification in both X and Y directions. Intended to improve readability
//at higher magnifications but doesn't realy smooth very well.
//I'm sure that someone can come up with a better solution than this, but I didn't have time to code an Interpolation algorithm or
//creata vectored drawing system.
{
    unsigned char Xpos, Ypos, tempByte1, tempByte2, tempByte3, and1, and2, totaland, repeater;
    
    if (Xmag<2 || Ymag<2) return;                               //check for enough magnification to work with
    
    for (repeater=0; repeater<(Xmag*Ymag)/(Xmag+Ymag); repeater++)  //calc sensible number of itterations
    {
    
        for (Ypos=0; Ypos<Ymag; Ypos++)
        {
            for (Xpos=0; Xpos<Xmag*6-1; Xpos++)                     //scan left to right
            {
                tempByte1 = magData[Xpos+1][Ypos];                  //get the following byte
                tempByte2 = magData[Xpos][Ypos];                    //get the current byte
                tempByte3 = tempByte1 ^ tempByte2;                  //check for a change
            
                if (tempByte3 != 0)
                {
                    tempByte2 >>= 1;                                //shift up (Right towards LSB)
                
                    if (Ypos+1 <= Ymag)
                    {
                        tempByte3 = magData[Xpos][Ypos+1];          //get missing BIT from byte below
                        tempByte3 <<= 7;
                        tempByte2 |= tempByte3;
                    }
                
                    and1 = tempByte1 & tempByte2;
                        
                    tempByte2 = magData[Xpos][Ypos];                //re-load the current byte
                    tempByte2 <<= 1;                                //shift down (Left towards the MSB)
           
                    if (Ypos > 0)
                    {
                        tempByte3 = magData[Xpos][Ypos-1];          //get missing BIT from byte above
                        tempByte3 >>= 7;
                        tempByte2 |= tempByte3;
                    }
                
                    and2 = tempByte1 & tempByte2;
            
                    totaland = (and1 | and2);
                    magData[Xpos][Ypos] |= totaland;                //incorpoate the extra bits into the magData                }
                }
            }
        
            for (Xpos=Xmag*6; Xpos>0; Xpos--)                       //scan right to left
            {
                tempByte1 = magData[Xpos-2][Ypos];                  //get following byte
                tempByte2 = magData[Xpos-1][Ypos];                  //get the current byte
                tempByte3 = tempByte1 ^ tempByte2;                  //check for change
                
                if (tempByte3 != 0)
                {
                    tempByte2 >>= 1;                                //shift up (Right towards the LSB)
 
                    if (Ypos+1 <= Ymag)
                    {
                        tempByte3 = magData[Xpos-1][Ypos+1];        //get missing BIT from byte below
                        tempByte3 <<= 7;
                        tempByte2 |= tempByte3;
                    }
                
                    and1 = tempByte1 & tempByte2;
            
                    tempByte2 = magData[Xpos-1][Ypos];              //re-load the current byte
                    tempByte2 <<= 1;                                //shift down (Left towards the MSB)
                
                    if (Ypos > 0)
                    {
                        tempByte3 = magData[Xpos-1][Ypos-1];        //get missing Bits from byte above
                        tempByte3 >>= 7;
                        tempByte2 |= tempByte3;
                    }
                    and2 = tempByte1 & tempByte2;
            
                    totaland = (and1 | and2);
                    magData[Xpos - 1][Ypos] |= totaland;
                }
            }
        }
    }
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::magChar( unsigned char c, unsigned char Xmag, unsigned char Ymag )
//Expand the basic 5 x 8 char def to the required X and y magnification using an buffer Array
{
    unsigned char tempPat, count, Idx, Xexp, Yexp, bitCounter, bitAcc, srcBit, magDataX, magDataY;
    
    clrMagArray( Xmag, Ymag, false );
    
    Idx = c - 32;                               //shift the ASCII code so it starts from zero
    
    magDataX = 0;
    
    for (count=0; count<5; count++)             //5 bytes per char def
    {
        bitCounter = Ymag/2;                    //offset the image Y position by half the Y magnification factor
        bitAcc = 0;
        magDataY = 0;
        tempPat = font_data[Idx][count];        //get column Bit pattern to expand in the y direction by bit replication
                                                //LSB is top Bit position
        
        for (srcBit=0; srcBit<8; srcBit++)      //process each of the 8 bits in the source byte
        {
            for (Yexp=0; Yexp<Ymag; Yexp++)     //each Bit in each def byte is duplicated Ymag times in the Y direction
            {
                bitAcc >>= 1;                   //shift the accumulator 1 bit to the left
                
                if ((tempPat & 1) > 0)
                {
                    bitAcc |= 0x80;             //set msb
                } else {
                    bitAcc &= 0x7F;             //clear msb
                }
                
                bitCounter++;
                
                if (bitCounter > 7)             //if the bit accumulator is full then store it and clear it to continue
                {
                    for (Xexp=0; Xexp<Xmag; Xexp++) //do the X magnification while storingthe Bit Accumulator
                    {
                        magData[magDataX + Xexp][magDataY] = bitAcc;
                    }
                    
                    bitAcc = 0;
                    magDataY++;
                    bitCounter = 0;
                }
            }
            tempPat>>=1;
        }
        magDataX += Xmag;
    }
    smoothEdges( Xmag, Ymag );
}
 
//----------------------------------------------------------------------
 
int N_5110_Display::outputMagData (unsigned char Xmag, unsigned char Ymag, bool FullWidth )
{
    unsigned char XpixTemp, mx, my, width;
    
    XpixTemp = PixX;
    width = FullWidth?6:5;
    
    if (FullWidth == false)
    {
        for (mx=0; mx<Xmag/2; mx++)
        {
            dc=1;                       //select Data mode
            cs=0;                       //Chip Enabled
    
            for (my=0; my<Ymag; my++)
            {
                spi.write( 0 );
            }
        
            cs=1;                       //Chip Disabled
    
            XpixTemp += 1;
            setDispPos(XpixTemp, CharY);
        }
    }
    
    for (mx=0; mx<Xmag*width; mx++)
    {
        dc=1;                       //select Data mode
        cs=0;                       //Chip Enabled
        
        for (my=0; my<Ymag; my++)
        {
            spi.write( magData[mx][my] );
        }
        
        cs=1;                       //Chip Disabled
        
        XpixTemp += 1;
        setDispPos( XpixTemp, CharY );
    }
    
    if (FullWidth == false)
    {
        for (mx=0; mx<(Xmag+1)/2; mx++)
        {
            dc=1;                       //select Data mode
            cs=0;                       //Chip Enabled
    
            for (my=0; my<Ymag; my++)
            {
                spi.write( 0 );
            }
        
            cs=1;                       //Chip Disabled
    
            XpixTemp += 1;
            setDispPos(XpixTemp, CharY);
        }
    }
    
    PixX = XpixTemp;
    CharX += Xmag;
    
    return 0;
}
 
//----------------------------------------------------------------------
 
int N_5110_Display::print1char(unsigned char c, unsigned char Xmag, unsigned char Ymag)
{    
    if (c<32 | c>127) return -1;    //Exit if char is out of range
    
    if (Xmag<1) Xmag=1;             //Clamp the magnification values
    if (Ymag<1) Ymag=1;
    if (Xmag>6) Xmag=6;
    if (Ymag>6) Ymag=6;
        
    magChar( c, Xmag, Ymag );
 
    outputMagData( Xmag, Ymag, false );
    
    return 0;
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::printString( char * str2prt, unsigned char Xmag, unsigned char Ymag)
{
    unsigned char c;
    
    for (c=0; c<strlen(str2prt); c++)
    {
        print1char( str2prt[c], Xmag, Ymag );
    }
}
 
//----------------------------------------------------------------------
 
void N_5110_Display::VertBarGraph( int Percentage, unsigned char Xmag, unsigned char Ymag )
{
    unsigned char Xidx, Yidx, activeHeight, wholeBytes, pixRemaining, mask, count, dither;
    
    if (Xmag<1) Xmag=1;                                     //Clamp the magnification values
    if (Ymag<1) Ymag=1;
    if (Xmag>6) Xmag=6;
    if (Ymag>6) Ymag=6;
    
    clrMagArray( Xmag, Ymag, true );
    
    activeHeight = 8 * Ymag * Percentage /100;              //Calc the magnitude of the Bar
    wholeBytes = activeHeight / 8;
    pixRemaining = activeHeight % 8;
    
    mask = 0xFF;
    for(count=0; count<8-pixRemaining; count++)             //creat the mask for pixRemaining
    {
        mask <<= 1;
    }
    
    for (Xidx=0; Xidx<6*Xmag-1; Xidx++)                     //step along the pixel columns
    {
        dither = Xidx&1?0x55:0xAA;                          //Dither value alternates for each odd, ecen pixel column
    
        for (Yidx=0; Yidx<Ymag; Yidx++)                     //step through each row
        {
            if (Yidx == Ymag - wholeBytes - 1)              //do the remainder
            {
                magData[Xidx][Yidx] |= dither;
                magData[Xidx][Yidx] &= mask;
            }
            else if (Yidx >= Ymag-wholeBytes)                //else do the whole bytes
            {
                magData[Xidx][Yidx] |= dither;
            }
                                                            //now add the border
            if (Xidx==0 || Xidx==6*Xmag-2)                  //Left & Right
            {
                magData[Xidx][Yidx] |= 0xFF;
            }
            
            if (Yidx==0)                                    //Top
            {
                magData[Xidx][Yidx] |= 0x01;
            }
            
            if (Yidx==Ymag-1)                               //Bottom
            {
                magData[Xidx][Yidx] |= 0x40;
                magData[Xidx][Yidx] &= 0x7F;
            }
        }
    }
    
    outputMagData( Xmag, Ymag, true );
}
 