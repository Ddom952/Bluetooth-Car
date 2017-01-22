#ifndef DECODER_H
#define DECODER_H

#define MAX_TOKEN_NR 4 //maksymalna dopuszczalna ilosc tokenów
#define MAX_KEYWORD_STRING_LTH 10 // mksymalna dlugosc komendy
#define MAX_KEYWORD_NR 4


//dekodowanie
typedef enum KeywordCode {DATA,ID,CALIB,GOTO}KeywordCode;
typedef enum TokenType {KEYWORD, NUMBER, STRING}TokenType;

typedef struct Keyword{
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
}Keyword;

typedef union TokenValue{
    enum KeywordCode eKeyword; // jezeli KEYWORD
    unsigned int uiNumber; // jezeli NUMBER
    char * pcString; // jezeli STRING
}TokenValue;

typedef struct Token{
    enum TokenType eType; // KEYWORD, NUMBER, STRING
    union TokenValue uValue; // enum, unsigned int, char*
}Token;

//***************************************************************
void DecodeMsg(char *pcString);

#endif // DECODER_H
