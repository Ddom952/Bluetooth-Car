#include "string.h"
#define NULL '\0'
//***************************************************************************************************

void CopyString (char pcSource[], char pcDestination[]){

    unsigned char ucLicznikZnakow;

    for (ucLicznikZnakow =0; NULL != pcSource[ucLicznikZnakow]; ucLicznikZnakow++){
        pcDestination[ucLicznikZnakow] = pcSource[ucLicznikZnakow];
    }
    pcDestination[ucLicznikZnakow] = pcSource[ucLicznikZnakow];

}

//***************************************************************************************************

//enum CompResult {DIFFERENT, EQUAL};
enum CompResult eCompareString(char pcStr1[], char pcStr2[]){

    unsigned char ucLicznikZnakow;

    for(ucLicznikZnakow =0; pcStr1[ucLicznikZnakow] == pcStr2[ucLicznikZnakow]; ucLicznikZnakow++){
        if(NULL == pcStr2[ucLicznikZnakow]){
            break;
        }
    }
    if ((NULL == pcStr1[ucLicznikZnakow]) && NULL == pcStr2[ucLicznikZnakow]){
            return EQUAL;
    }
    else{
            return DIFFERENT;
    }
}

//***************************************************************************************************

void AppendString (char pcSourceStr[],char pcDestinationStr[]){

    unsigned char ucLicznikZnakow;

    for(ucLicznikZnakow=0; pcDestinationStr[ucLicznikZnakow]!=NULL; ucLicznikZnakow++){}
    CopyString(pcSourceStr, pcDestinationStr+ ucLicznikZnakow);
}

//***************************************************************************************************

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){

    unsigned char ucLicznikZnakow;

    for(ucLicznikZnakow=0; pcString[ucLicznikZnakow]!=NULL; ucLicznikZnakow++){
        if (pcString[ucLicznikZnakow]==cOldChar){
            pcString[ucLicznikZnakow]=cNewChar;
        }
    }
}

//***************************************************************************************************

void UIntToHexStr (unsigned int uiValue, char pcStr[]){

  char cTetradCounter;
  char cTetradValue;
  pcStr[0]='0';
  pcStr[1]='x';

  for (cTetradCounter=0; cTetradCounter<4; cTetradCounter++){
    cTetradValue = ((uiValue) >> (cTetradCounter*4) & (0x000F));
    if (cTetradValue < 10){
      pcStr[5 - cTetradCounter] = cTetradValue + '0';
    }
    else{
       pcStr[5 - cTetradCounter] = cTetradValue + 'A' - 10 ;
    }
  }
  pcStr[6] = NULL;
}

 //***************************************************************************************************

enum Result eHexStringToUInt(char cStr[], unsigned int *puiValue){

  char cCharCounter;
  unsigned int uiValue = 0;

    if ( (cStr[0] != '0') || (cStr[1] != 'x') || (cStr[2] == NULL) ){
    return EROR;
  }
  for (cCharCounter=2; cStr[cCharCounter] != NULL; cCharCounter++){
        uiValue = uiValue << 4;
    if (6 == cCharCounter){
      return EROR;
    }
    else if (cStr[cCharCounter] < 'A'){
      uiValue = uiValue + cStr[cCharCounter] - '0';
    }
    else{
      uiValue = uiValue + cStr[cCharCounter] - 'A' + 10;
    }
  }
    *puiValue = uiValue;
  return OK;
}

//***************************************************************************************************

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){

  unsigned char ucCharCounter;

  for(ucCharCounter=0; (pcDestinationStr[ucCharCounter]) != NULL; ucCharCounter++){}
  UIntToHexStr (uiValue, &pcDestinationStr[ucCharCounter]);
}

//***************************************************************************************************

