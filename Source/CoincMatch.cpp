#include "CoincMatch.h"

using namespace std;

#ifndef CLASS_CoincMatch_FUNC
#define CLASS_CoincMatch_FUNC

//===================================================================================
//DESTRUCTOR, CUNTRUCTOR and INIT FUNC
//===================================================================================

	CoincMatch::CoincMatch(bool con_UseStandalone)
	:	UseStandalone(	con_UseStandalone)		
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;
		RetCon = ConstructorInit();
	}

	CoincMatch::CoincMatch(string con_FileConfig_Path, string con_FileConfig_Name, bool con_UseStandalone)
	:	FileConfig_Path(con_FileConfig_Path),
		FileConfig_Name(con_FileConfig_Name),
		UseStandalone(	con_UseStandalone)
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		RetCon = ConstructorInit();
		RetCon = LoadConfig();
		RetCon = Init();
	}

	int CoincMatch::ConstructorInit()
	{
		int RetCon = 		COINCMATCH_ERR_NO_ERROR;

		ProgVer = 			CoincMatch_PROG_VER;
		FileConfig=			nullptr;
		FileLog=			nullptr;
		DoPrintOut=			true;
		DoLog=				true;	
		FileLog_Name=		"LogFile.txt";
		FileLog_Path=		"";
		FileIn_Name=		"";
		FileOut_EndData=	"";
		FileOut_EndInfo=	"";		
		FileIn_Path=		"." + string(DIR_SLASH);
		FileOut_Name=		"";
		FileOut_Path=		"." + string(DIR_SLASH);

		return RetCon;
	}

	int CoincMatch::Init()
	{
		int RetCon = 	COINCMATCH_ERR_NO_ERROR;

		if(UseStandalone)
		{
			printf("%s\n", (FileLog_Path + FileLog_Name).c_str() );

			FileLog = new fstream( (FileLog_Path + FileLog_Name).c_str(), ios_base::out);
			if(!FileLog->is_open())
			{
				Print_Error(FileLog, to_string(COINCMATCH_ERR_LOG_FILE_OPEN) +  " : Can not open log file: " + FileLog_Path + FileLog_Name,DoPrintOut, DoLog);
				cerr << COINCMATCH_ERR_LOG_FILE_OPEN << ";";
				FileLog = nullptr;
				return -1; 	
			}
		}

		return RetCon;
	}

//===================================================================================
//LOAD CONFIG
//===================================================================================

	int CoincMatch::LoadConfig()
	{	
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		if(!CheckFileExist(FileConfig_Path + FileConfig_Name))
		{
			Print_Error(FileLog, to_string(COINCMATCH_ERR_CONFIG_FILE_OPEN) +  " : Can not open config file: " + FileConfig_Path + FileConfig_Name,DoPrintOut, DoLog);
			cerr << COINCMATCH_ERR_CONFIG_FILE_OPEN << ";";
			return -1; 	
		}

		FileConfig = new INI_File(FileConfig_Path, FileConfig_Name);
		FileConfig->Read();

		//INPUT

			string Input_SecName = "Input";

			if(FileConfig->IsParInSection("FileIn_Path",Input_SecName)) 		FileIn_Path = FileConfig->FindParInSection("FileIn_Path", Input_SecName).v_ValStr[0];
			if(FileConfig->IsParInSection("FileIn_Name",Input_SecName)) 		FileIn_Name = FileConfig->FindParInSection("FileIn_Name", Input_SecName).v_ValStr[0];

		//EXPORT

			string Export_SecName = "Export";

			if(FileConfig->IsParInSection("DoExport",Export_SecName)) 			DoExport = StringToBool(FileConfig->FindParInSection("DoExport", Export_SecName).v_ValStr[0]);

			if(FileConfig->IsParInSection("FileOut_Path",Export_SecName)) 		FileOut_Path = FileConfig->FindParInSection("FileOut_Path", Export_SecName).v_ValStr[0];
			if(FileConfig->IsParInSection("FileOut_Name",Export_SecName)) 		FileOut_Name = FileConfig->FindParInSection("FileOut_Name", Export_SecName).v_ValStr[0];
			if(FileConfig->IsParInSection("FileOut_EndData",Export_SecName)) 	FileOut_EndData = FileConfig->FindParInSection("FileOut_EndData", Export_SecName).v_ValStr[0];
			if(FileConfig->IsParInSection("FileOut_EndInfo",Export_SecName)) 	FileOut_EndInfo = FileConfig->FindParInSection("FileOut_EndInfo", Export_SecName).v_ValStr[0];

		//PRINT AND LOG
			
			string LogPrint_SecName = "LogPrint";

			if(FileConfig->IsParInSection("DoPrintOut",LogPrint_SecName)) 		DoPrintOut = StringToBool(FileConfig->FindParInSection("DoPrintOut", LogPrint_SecName).v_ValStr[0]);
			if(FileConfig->IsParInSection("DoLog",LogPrint_SecName)) 			DoLog = StringToBool(FileConfig->FindParInSection("DoLog", LogPrint_SecName).v_ValStr[0]);

			if(FileConfig->IsParInSection("FileLog_Name",LogPrint_SecName)) 	FileLog_Name = FileConfig->FindParInSection("FileLog_Name", LogPrint_SecName).v_ValStr[0];
			if(FileConfig->IsParInSection("FileLog_Path",LogPrint_SecName)) 	FileLog_Path = FileConfig->FindParInSection("FileLog_Path", LogPrint_SecName).v_ValStr[0];
			

		return RetCon;
	}

//===================================================================================
//
//===================================================================================

//===================================================================================
//
//===================================================================================

//===================================================================================
//PRINT and LOG
//===================================================================================


	void CoincMatch::Print_MainTitle()
	{
		string PrintOut = "";
		PrintOut = 
					PrintOut + "\n" + 
					"======================================================================= \n" +
					"                               CoincMatch \n"+
					"======================================================================= \n\n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, DoLog);

		return;
	}

	string CoincMatch::PrintBool(string VarName, bool VarVal)
	{
		string PrintOut = "";

		if(VarVal)		PrintOut += "\t"+VarName+":\tTrue\n";
		else  			PrintOut += "\t"+VarName+":\tFalse\n";	

		return PrintOut;
	}

	void CoincMatch::Print()
	{
		string PrintOut = "\n";

		PrintOut += "===========================================================\n";
		PrintOut += "MAIN SETTINGS\n\n";
		PrintOut += "\tFileIn_Path:\t" +   FileIn_Path+ "\n";
		PrintOut += "\tFileIn_Path:\t" +   FileIn_Name+ "\n";
		PrintOut += "\n";
		PrintOut += PrintBool("DoExport", DoExport);
		PrintOut += "\tFileOut_Path:\t" +   FileOut_Path+ "\n";
		PrintOut += "\tFileOut_Name:\t" +   FileOut_Name+ "\n";
		PrintOut += "\tFileOut_EndData:\t" +   FileOut_EndData+ "\n";
		PrintOut += "\tFileOut_EndInfo:\t" +   FileOut_EndInfo+ "\n";
		PrintOut += "\n";
		PrintOut += PrintBool("DoPrintOut", DoPrintOut);
		PrintOut += "\tFileLog_Name:\t" +   FileLog_Name+ "\n";
		PrintOut += "\tFileLog_Path:\t" +   FileLog_Path+ "\n";		
		PrintOut += "===========================================================\n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, DoLog);
		
		return;
	}	


	void CoincMatch::Error_ThrowAndCerr(int Error)
	{
		cerr << Error << ";";
		throw(Error);
		return;
	}


//===================================================================================
	

#endif