#include "GF.h"

#ifndef GF_FUNC
#define GF_FUNC



string GF_PrintBool(string VarName, bool VarVal)
{
	string PrintOut = "";

	if(VarVal)		PrintOut += VarName+":\t\tTrue\n";
	else  			PrintOut += VarName+":\t\tFalse\n";	

	return PrintOut;
}

bool GF_IsCharInVectorChar(char Char, vector<char> v_Char )
{
	for (unsigned int i = 0; i < v_Char.size(); ++i)
		if(Char == v_Char[i]) return true;
	return false;
}


string GF_ReplaceStrInStr(string MainStr, string ToBeReplacedStr, string ReplaceStr)
{
	if(MainStr.find(ToBeReplacedStr) > -1) return MainStr; 
	
	string NewMainStr = 	"";
	string DelStr = 		MainStr;

	while(DelStr.size() >= ToBeReplacedStr.size())
	{
		if(DelStr.find(ToBeReplacedStr) != -1)
		{
			NewMainStr +=  	DelStr.substr(0,DelStr.find(ToBeReplacedStr)) + ReplaceStr; 
			DelStr = 		DelStr.substr(DelStr.find(ToBeReplacedStr) + ToBeReplacedStr.size(),DelStr.size()-1);
		}
		else
		{
			NewMainStr += DelStr;
			break;
		}
	}

	return NewMainStr;
}


void GF_Error_ThrowAndCerr(int Error)
{
	cerr << Error << ";";
	throw(Error);
	return;
}

int GF_ConvertVecStrToStr(string &Str, std::vector<string> v_Str, char Parser)
{
	if(v_Str.size() == 0) return -1;

	Str = v_Str[0];

	for (int i = 1; i < v_Str.size(); ++i)
	{
		Str += Parser;
		Str += v_Str[i];
	}

	return 0;
}




#endif