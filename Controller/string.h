#ifndef STRING_H
#define STRING_H
 
//lancuchy znakowe - operacje proste
enum CompResult {DIFFERENT, EQUAL};

void CopyString (char pcSource[], char pcDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString (char pcSourceStr[],char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);


//lancuchy znakowe - konwersje
enum Result {OK, EROR};

void UIntToHexStr (unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char cStr[], unsigned int *puiValue);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);

#endif //STRING_H


