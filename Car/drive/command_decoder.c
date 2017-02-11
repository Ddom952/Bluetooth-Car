#include "command_decoder.h"
#include "my_string.h"

#define MAX_KEYWORD_STRING_LTH 15
#define MAX_KEYWORD_NR 11
#define NULL 0

struct Keyword
{
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
    {DIR_L, "dirleft"},
    {DIR_R, "dirright"},
	{BK, "back"},
	{FRW, "forward"},
	{SP_L, "speedleft"},
	{SP_R, "speedright"},
	{LEFT, "left"},
	{RIGHT, "right"},
	{STOP, "stop"},
	{STOP_L, "stopleft"},
	{STOP_R, "stopright"}
};

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

unsigned char ucFindTokensInString(char *pcString) {

    enum AutomatState { TOKEN, DELIMITER };
    enum AutomatState eAutomatState = DELIMITER;
    unsigned char ucCharacterCounter, ucTempCharacter;
    ucTokenNr = 0;

    for(ucCharacterCounter = 0; ; ucCharacterCounter++) {
        ucTempCharacter = pcString[ucCharacterCounter];
        switch (eAutomatState) {
            case TOKEN :
                    if(' ' == ucTempCharacter) {
                        eAutomatState = DELIMITER;
                    }
                    else if(MAX_TOKEN_NR == ucTokenNr) {
                        return ucTokenNr;
                    }
                    else if(NULL == ucTempCharacter) {
                        return ucTokenNr;
                    }
                    break;

            case DELIMITER :
                    if(' ' == ucTempCharacter) {
                        eAutomatState = DELIMITER;
                    }
                    else if(NULL == ucTempCharacter) {
                        return ucTokenNr;
                    }
                    else {
                        asToken[ucTokenNr].uValue.pcString = &pcString[ucCharacterCounter];
                        eAutomatState = TOKEN;
                        ucTokenNr++;
                    }
                    break;
        }
    }
}

enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode) {

    unsigned char ucKeywordCounter;

    for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++) {
        if( EQUAL == eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString)) {
            *peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
            return OK;
        }
    }
    return ERROR;
}

void DecodeTokens(void) {

    unsigned char ucTokenCounter;
    struct Token *asTokenPtr;
    char *pcTokenString;
    unsigned int *puiTokenNumber;
    enum KeywordCode *peTokenKeyword;

    for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++) {
        asTokenPtr = &asToken[ucTokenCounter];
        pcTokenString = asTokenPtr->uValue.pcString;
        puiTokenNumber = &(asTokenPtr->uValue.uiNumber);
        peTokenKeyword = &(asTokenPtr->uValue.eKeyword);

        if(OK == eStringToKeyword(pcTokenString, peTokenKeyword)) {
            asTokenPtr->eType = KEYWORD;
        }
        else if(OK == eHexStringToUInt(pcTokenString, puiTokenNumber)) {
            asTokenPtr->eType = NUMBER;
        }
        else {
            asTokenPtr->uValue.pcString = pcTokenString;
            asTokenPtr->eType = STRING;
        }
    }
}

void DecodeMsg(char *pcString) {
    ucFindTokensInString(pcString);
    ReplaceCharactersInString(pcString, ' ', NULL);
    DecodeTokens();
}
