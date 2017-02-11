#define MAX_TOKEN_NR 2

enum TokenType { KEYWORD, NUMBER, STRING };
enum KeywordCode { DIR_L, DIR_R, BK, FRW, SP_L, SP_R, LEFT, RIGHT, STOP, STOP_L, STOP_R };

union TokenValue
{
    enum KeywordCode eKeyword;
    unsigned int uiNumber;
    char *pcString;
};

struct Token
{
    enum TokenType eType;
    union TokenValue uValue;
};

void DecodeMsg(char *pcString);
