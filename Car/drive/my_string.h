#ifndef _MY_STRING_H_
#define _MY_STRING_H_

void CopyString(char[], char[]);
enum CompResult { EQUAL, DIFFERENT } eCompareString(char[], char[]);
void AppendString(char[], char[]);
void ReplaceCharactersInString(char[], char, char);
enum Result { OK, ERROR } eHexStringToUInt(char[], unsigned int *);
void AppendUIntToString ( unsigned int uiValue, char pcDestinationStr[] );

#endif /* _MY_STRING_H_ */
