#include "Headers.h"


#ifndef GF_HEADER
#define GF_HEADER


string GF_PrintBool(string VarName, bool VarVal);

bool GF_IsCharInVectorChar(char Char, vector<char> v_Char );

string GF_ReplaceStrInStr(string MainStr, string ToBeReplacedStr, string ReplaceStr);


//Throw error and print it into cerr.
//Error - error code which should be in throw and printed.
void GF_Error_ThrowAndCerr(int Error);


int GF_ConvertVecStrToStr(string &Str, std::vector<string> v_Str, char Parser = '|');

#endif