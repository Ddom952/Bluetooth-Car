#include "my_string.h"

#define NULL 0
#define NIBBLE_SEPARATOR 0x000F

void CopyString(char pcSource[], char pcDestination[]) {

    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; NULL != pcSource[ucCharacterCounter]; ucCharacterCounter++) {
        pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
    }

    pcDestination[ucCharacterCounter] = NULL;
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; pcStr1[ucCharacterCounter] == pcStr2[ucCharacterCounter]; ucCharacterCounter++) {
        if(NULL == pcStr1[ucCharacterCounter]) {
            return EQUAL;
        }
    }
        return DIFFERENT;
}

void AppendString(char pcSourceStr[], char pcDestinationStr[]) {

    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; NULL != pcDestinationStr[ucCharacterCounter]; ucCharacterCounter++) { };
    CopyString(pcSourceStr, pcDestinationStr+ucCharacterCounter);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar) {

    unsigned char ucCharacterCounter;

    for(ucCharacterCounter = 0; NULL != pcString[ucCharacterCounter]; ucCharacterCounter++) {
        if(pcString[ucCharacterCounter] == cOldChar) {
            pcString[ucCharacterCounter] = cNewChar;
        }
    }
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue) {

    unsigned char ucCharacterCounter, ucCurrentCharacter = pcStr[2];
    unsigned int uiCurrentValue;
    *puiValue = 0;

    if((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL)) {
        return ERROR;
    }
    for(ucCharacterCounter = 2; ucCurrentCharacter != NULL; ucCharacterCounter++) {
        if(ucCharacterCounter == 6) {
            return ERROR;
        }
        if(ucCurrentCharacter < 'A') {
            uiCurrentValue = ucCurrentCharacter - '0';
        }
        else {
            uiCurrentValue = ucCurrentCharacter - 'A' + 10;
        }
        *puiValue = (*puiValue << 4) | uiCurrentValue;
        ucCurrentCharacter = pcStr[ucCharacterCounter+1];
    }
    return OK;
}

void UIntToHexStr (unsigned int uiValue, char pcStr[])
{
unsigned char ucNibbleCounter, ucCurrentNibble;
pcStr[0] = '0' ;
pcStr[1] = 'x' ;
pcStr[6] = NULL;

for ( ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter++ ) 
	{
   ucCurrentNibble = ((uiValue >> ( 4*ucNibbleCounter )) & NIBBLE_SEPARATOR);
   if ( ucCurrentNibble <= 9)
    {
		 pcStr [ 5 - ucNibbleCounter] = ucCurrentNibble + '0' ;
	  }
	 else 
	  {
		 pcStr [ 5 - ucNibbleCounter] = ucCurrentNibble + 'A' - 10 ;
	  }
  }
}
	
void AppendUIntToString ( unsigned int uiValue, char pcDestinationStr[] )
{
	unsigned char ucCharCounter ;
	for ( ucCharCounter = 0; pcDestinationStr [ucCharCounter] != NULL; ucCharCounter++ ) {} ;
	UIntToHexStr ( uiValue, pcDestinationStr + ucCharCounter );
}
