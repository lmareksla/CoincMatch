#include "CoincMatch.h"

using namespace std;

#ifndef FRAMEWORK_CoincMatch_FUNC
#define FRAMEWORK_CoincMatch_FUNC


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
		RetCon = Init();
		RetCon = LoadConfig();
	}

	int CoincMatch::ConstructorInit()
	{
		int RetCon = 		COINCMATCH_ERR_NO_ERROR;

		ProgVer = 			string(COINCMATCH_PROG_VER);
		DateLastChange =  	string(COINCMATCH_DATE_LAST_CHANGE);
		FileConfig=			nullptr;
		FileLog=			nullptr;
		DoPrintOut=			true;
		DoLog=				true;	
		FileLog_Name=		"LogFile.txt";
		FileLog_Path=		"";
		DoExport = 			true;
		FileOut_EndData=	"";
		FileOut_EndInfo=	"";		
		FileOut_Name=		"";
		FileOut_Path=		"." + string(DIR_SLASH);
		ElistKeyName =  	"Elist";
		v_Elists.clear();
		N_Detectors =  		-1;
		N_ClusterToLoadAll = 1000000;
		N_ClusterToLoadElist= -1;	
		FileElist_SizeMin =	-1;
		FileElist_SizeMax = -1;
		v_FileElists_Size.clear();
		v_IsMoreData.clear();
		IsMoreData =  		true;
		vv_Clusters.clear();

		return RetCon;
	}

	int CoincMatch::Init()
	{
		int RetCon = 	COINCMATCH_ERR_NO_ERROR;

		if(UseStandalone)
		{
			FileLog = new fstream( (FileLog_Path + FileLog_Name).c_str(), ios_base::out);
			if(!FileLog->is_open())
			{
				Print_Error(FileLog, to_string(COINCMATCH_ERR_LOG_FILE_OPEN) +  " : Can not open log file: " + FileLog_Path + FileLog_Name,DoPrintOut, DoLog);
				cerr << COINCMATCH_ERR_LOG_FILE_OPEN << ";";
				FileLog = nullptr;
				return -1; 	
			}
		}

		Print_MainTitle();
		Print();

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

		Delete_CheckNull(FileConfig);

		FileConfig = new INI_File(FileConfig_Path, FileConfig_Name);
		FileConfig->Read();

		//ELIST

			for (unsigned int i = 0; i < FileConfig->v_Section.size(); ++i)
			{
				string KeyName = FileConfig->v_Section[i]->KeyName;
				
				if(KeyName.find(ElistKeyName) != -1)
				{
					InitScanElist(FileConfig->v_Section[i]);
				}
			}

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

		//ADDITIONAL SETTINGS

		return RetCon;
	}

	int CoincMatch::InitScanElist(Section* o_Section)
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		if(FileConfig == nullptr) return -1;

		string FileIn_Path = "";
		string FileIn_Name = "";
		bool IsMain = false;

		if(FileConfig->IsParInSection("FileIn_Path",o_Section)) 	FileIn_Path = FileConfig->FindParInSection("FileIn_Path", o_Section).v_ValStr[0];
		if(FileConfig->IsParInSection("FileIn_Name",o_Section)) 	FileIn_Name = FileConfig->FindParInSection("FileIn_Name", o_Section).v_ValStr[0];
		if(FileConfig->IsParInSection("IsMain",o_Section)) 			IsMain = FileConfig->FindParInSection("IsMain", o_Section).v_ValNum[0];

		Elist* o_Elist = new Elist(FileIn_Path, FileIn_Name, false);

		RetCon = o_Elist->Init();

		o_Elist->Set_DoLog(DoLog);
		o_Elist->Set_DoPrintOut(DoPrintOut);
		o_Elist->Set_FileLog(FileLog);

		RetCon = o_Elist->Scan();
		
		o_Elist->Print();

		//SAVE

			if(v_Elists.size() == 0) v_Elists.push_back(o_Elist);
			else
			{
				if(IsMain)	v_Elists.insert(v_Elists.begin(), o_Elist);	
				else    	v_Elists.push_back(o_Elist);
			}

		return RetCon;
	}

//===================================================================================
//DATA PROCESSING
//===================================================================================

	int CoincMatch::ProcessData()
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		RetCon = CheckElistFormats();

		// for (unsigned int i = 0; i < v_Elists.size(); ++i)
		// {
		// 	printf("%s\n", v_Elists[i]->Get_FileIn_Name().c_str() );
		// }

		for (unsigned int i = 0; i < v_Elists.size(); ++i)
		{
			LoadElist(v_Elists[i]);
		}

		// while(IsMoreData)
		// {
		// 	for (unsigned int i = 0; i < v_Elists.size(); ++i)
		// 	{
		// 		LoadElist(v_Elists[i]);
		// 	}

		// 	// RetCon = FindCoincMatch();

		// 	vv_Clusters.clear();
		// }
		
		return RetCon; 
	}	

	int CoincMatch::CheckElistFormats()
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		for (unsigned int i = 1; i < v_Elists.size(); ++i)
		{
			if(!v_Elists[0]->CompareElist(v_Elists[i]))
			{
				Print_Error(FileLog, to_string(COINCMATCH_ERR_ELISTS_DIFF_FORM) +  " : Different format of elist to main one: " + v_Elists[i]->Get_FileIn_Path() + v_Elists[i]->Get_FileIn_Name(),DoPrintOut, DoLog);
				cerr << COINCMATCH_ERR_ELISTS_DIFF_FORM << ";";

				v_Elists.erase(v_Elists.begin() + i);
				i--;
			}
		}

		return RetCon;
	}


	int CoincMatch::InsertClusterTimeSort(std::vector<double> v_Cluster)
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		return RetCon; 
	}


	int CoincMatch::FindCoincMatch()
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		return RetCon; 
	}	

//===================================================================================
//PRINT and LOG
//===================================================================================

	void CoincMatch::Print_Help()
	{
		string PrintOut = "";
		PrintOut += "\nCoincidence and matching algortihms - version: " + ProgVer + "\t" + DateLastChange + "\n\n";/* +
				  	"Program should be used with one parameter which is a name and path of a parameters file.\n" +
				  	"Linux example:\t\t./dpe.sh ./ParametersFile.txt\n" +
				  	"Windows example:\tDPE.exe .\\ParametersFile.txt\n" +				  	
				  	"For more information, see readme or examples.\n\n";*/

		PrintOut +=  "Other possible program parameters:\n\n";		
		PrintOut +=  "\t-v --version\treturns version of program\n";
		PrintOut +=  "\t-h --help\treturns help of program\n";

		PrintOut +=  "\nContact: lukas.marek@advacam.com\n";


		Print_Info(FileLog, PrintOut, 0, DoPrintOut, true);

		return;
	}

	void CoincMatch::Print_Version()
	{
		string PrintOut = "";
		PrintOut = PrintOut + "\nCoincidence and matching algortihms version: " + ProgVer + "\t" + DateLastChange + "\n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, true);

		return;
	}


	void CoincMatch::Print_MainTitle()
	{
		string PrintOut = "";
		PrintOut = 
					PrintOut + "\n" + 
					"======================================================================= \n" +
					"                        COINCIDENCE and MATCHING                        \n"+
					"======================================================================= \n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, DoLog);

		return;
	}

	void CoincMatch::Print()
	{
		string PrintOut = "\n";

		PrintOut += "---------------------------------------------------------\n";
		PrintOut += "MAIN SETTINGS\n\n";
		PrintOut += GF_PrintBool("DoExport", DoExport);
		PrintOut += "FileOut_Path:\t\t" +   FileOut_Path+ "\n";
		PrintOut += "FileOut_Name:\t\t" +   FileOut_Name+ "\n";
		PrintOut += "FileOut_EndData:\t\t" +   FileOut_EndData+ "\n";
		PrintOut += "FileOut_EndInfo:\t\t" +   FileOut_EndInfo+ "\n";
		PrintOut += "\n";
		PrintOut += GF_PrintBool("DoPrintOut", DoPrintOut);
		PrintOut += "FileLog_Name:\t\t" +   FileLog_Name+ "\n";
		PrintOut += "FileLog_Path:\t\t" +   FileLog_Path+ "\n";		
		PrintOut += "---------------------------------------------------------\n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, DoLog);
		
		return;
	}	

//===================================================================================



#endif