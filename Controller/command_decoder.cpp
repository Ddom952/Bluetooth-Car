#include "command_decoder.h"
#include "string.h"
#define NULL '\0'
Keyword asKeywordList[MAX_KEYWORD_NR]={
    {DATA, "data" },
    {ID, "id" },
    {CALIB, "callib" },
    {GOTO,  "goto"  }
};

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;
//Keyword asKeywordList[];
extern Token asToken[];

enum State {TOKEN, DELIMITER};


//***************************************************************************************************

unsigned char ucFindTokensInString(char *pcString){
    unsigned char ucCharCounter, ucCurrentChar, ucTokenNr = 0;
    enum State eState = DELIMITER;

    for (ucCharCounter = 0;;ucCharCounter++){
        ucCurrentChar = pcString[ucCharCounter];

        switch (eState){
            case TOKEN:
                if (NULL == ucCurrentChar){
                    return ucTokenNr;
                }
                else if ( ' ' == ucCurrentChar){
                    eState = DELIMITER;
                }
                break;
            case DELIMITER :
                if (NULL == ucCurrentChar){
                    return ucTokenNr;
                }
                else if ( ' ' != ucCurrentChar){
                    asToken[ucTokenNr].uValue.pcString = &pcString[ucCharCounter];
                    eState = TOKEN;
                    ucTokenNr++;
                }
                break;
        }
    }
}

//***************************************************************************************************

 enum Result eStringToKeyword (char pcStr[], KeywordCode *peKeyword){

    unsigned char ucKeywordCodeCounter;
    enum CompResult eCompResult;

    for(ucKeywordCodeCounter = 0 ; ucKeywordCodeCounter < MAX_KEYWORD_NR ; ucKeywordCodeCounter++){
        eCompResult = eCompareString(asKeywordList[ucKeywordCodeCounter].cString,pcStr);
        if(eCompResult == EQUAL) {
            *peKeyword = asKeywordList[ucKeywordCodeCounter].eCode;
            return OK;
        }
    }
    return EROR;
}

//***************************************************************************************************

void DecodeTokens(void){
    unsigned char ucTokenCounter;
    char    *pcString;
    struct Token *sCurrentToken;

    for (ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){
        sCurrentToken = &asToken[ucTokenCounter];
        pcString = asToken[ucTokenCounter].uValue.pcString;
        if (OK == eStringToKeyword(pcString, &(*sCurrentToken).uValue.eKeyword)){
            sCurrentToken->eType = KEYWORD;
        }
        else if (OK == eHexStringToUInt(pcString, &(*sCurrentToken).uValue.uiNumber)){
            sCurrentToken->eType = NUMBER;
        }
        else{
            sCurrentToken->eType = STRING;
        }
    }
}

//***************************************************************************************************

void DecodeMsg(char *pcString){
     ucTokenNr = ucFindTokensInString( pcString );
     ReplaceCharactersInString( pcString, ' ',NULL );
     DecodeTokens();
}


