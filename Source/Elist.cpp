#include "Elist.h"

using namespace std;

#ifndef CLASS_ELIST_FUNC
#define CLASS_ELIST_FUNC

//===================================================================================
//DESTRUCTOR, CUNTRUCTOR and INIT FUNC
//===================================================================================

	Elist::Elist(bool con_UseStandalone)
	:	UseStandalone(	con_UseStandalone)		
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;
		RetCon = ConstructorInit();
	}

	Elist::Elist(string con_FileIn_Path, string con_FileIn_Name, bool con_UseStandalone)
	:	UseStandalone(	con_UseStandalone)
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		RetCon = ConstructorInit();

		FileIn_Name = con_FileIn_Name;
		FileIn_Path = con_FileIn_Path;

		RetCon = Init();
	}

	int Elist::ConstructorInit()
	{
		int RetCon = 		COINCMATCH_ERR_NO_ERROR;

		FileLog=			nullptr;
		DoPrintOut=			true;
		DoLog=				true;	
		FileLog_Name=		"LogFile.txt";
		FileLog_Path=		"";
		FileIn_Name=		"";
		FileIn_Path=		"." + string(DIR_SLASH);
		File = 				nullptr;
		LineCount =  		0;
		DoneScan = 			false;
		T_First =  			-1;
		T_OffSet =  		0;
		EventID_Offset =  	0;
		prev_T =  			-1;
		prev_EventID =  	-1;
		curr_T_Event =  	-1;
		N_NanLines =  		0;
		N_InfLines =  		0;	
		LineNum =  			0;
		N_ClusterDone =  	0;
		N_ClusterToDo =  	-1;
		v_VarNames.clear();
		v_VarUnits.clear();
		VarN =  			-1;
		Separator = 		' ';
		IsXYIn_mm =  		true;
		IsTimeIn_ns =  		true;
		i_T = 				-1;
		i_X = 				-1; 					            			
		i_Y = 				-1; 					             			
		i_S = 				-1; 
		i_E = 				-1; 									       			
		i_H = 				-1; 		
		i_PolarAng =		-1; 				           
		i_L2D = 			-1; 					       				       			         
		i_W2D = 			-1; 					       				       			         
		i_WStd_Perp = 		-1; 			
		i_WStd_Perp = 		-1; 
		i_Round = 			-1; 
		i_Linear = 			-1; 			         
		i_NBordPix = 		-1;
		i_Thick = 			-1;
		i_Thin = 			-1;
		i_CurlyThin = 		-1;  
		i_EPix_Mean = 		-1;  
		i_LET = 			-1;  
		i_EventID = 		-1;
		i_DetectorID = 		-1;
		i_Flags = 			-1;

		return RetCon;
	}

	int Elist::Init()
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
				RetCon = COINCMATCH_ERR_LOG_FILE_OPEN; 	
			}
		}

		File = new fstream((FileIn_Path + FileIn_Name).c_str(), ios_base::in);

		if(!File->is_open()) 
		{
			Print_Error(nullptr, to_string(COINCMATCH_ERR_OPEN_ELIST) +  " : Can not open elist: " + FileIn_Path + FileIn_Name + "." , true, false);
			cerr << COINCMATCH_ERR_OPEN_ELIST << ";";
			File = nullptr;
			RetCon = COINCMATCH_ERR_OPEN_ELIST;
		}			

		return RetCon;
	}
	
//===================================================================================
//
//===================================================================================

	int Elist::Load()
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		if(File == nullptr || !File->is_open())
		{
			Print_Error(nullptr, to_string(COINCMATCH_ERR_ELIST_NOT_OPEN) +  " : Elist is not opened: " + FileIn_Path + FileIn_Name + "." , true, false);
			cerr << COINCMATCH_ERR_ELIST_NOT_OPEN << ";";
			return -1;
		}		

		string Line = "";
		std::vector<double> v_ClusterVar;
		
		double curr_T = 0;
		double curr_EventID = -1;

		if(!DoneScan)
		{
			getline(*File, Line);
			getline(*File, Line);
		}

		while(getline(*File, Line))
		{
			LineNum++;
			
			//REPLACE IN LINES NAN OR INF WITH -1 AND COUNT THEM

				if(Line.find("nan") != -1)
				{
					N_NanLines++;
					Line = GF_ReplaceStrInStr(Line, "-nan", "-1");
				}

				if(Line.find("inf") != -1) 
				{
					N_InfLines++;
					Line = GF_ReplaceStrInStr(Line, "-inf", "-1");
				}

			//LOAD VARIABLES FROM ONE LINE

				v_ClusterVar = FindNumsInLine(Line);
				if(v_ClusterVar.size() == 0) continue;

				N_ClusterDone++;
				curr_T = v_ClusterVar[i_T];
				curr_EventID = v_ClusterVar[i_EventID];

			//CHANGE UNITS

				if(!IsTimeIn_ns) curr_T *= 1e9;
				if(IsXYIn_mm)
				{	
					v_ClusterVar[i_X] *= 18.181818;
					v_ClusterVar[i_Y] *= 18.181818;
				}
			
			//INIT TIME VAR

				if(T_First == -1)
				{
					T_First = 0;					
					prev_T = curr_T;

					if(!IsTimeIn_ns)
					{
						T_First = curr_T;
						prev_T = 0;
					}
				}

			//CORRECT TIME FOR COINCIDENCES AND CHECK FOR TIME OFFSET FOR MULTI FILE PROCESSING

				if(!IsTimeIn_ns) curr_T -= T_First;
				
				if(i_EventID != -1 )
				{
					if(curr_EventID == 0 && prev_EventID > curr_EventID) EventID_Offset += prev_EventID + 1;

					curr_EventID += EventID_Offset;

					if(prev_EventID == curr_EventID) curr_T += curr_T_Event;
				}

				if(prev_EventID != curr_EventID) curr_T += T_OffSet;

				if(prev_T != curr_T && curr_T < prev_T)
				{
					curr_T -= 	T_OffSet;
					T_OffSet = 	prev_T;
					curr_T += 	prev_T;							
				}

				if(i_EventID != -1)
				{
					if(prev_EventID != curr_EventID) //New coinc group -> assign correct coinc num and new main time
					{
						prev_EventID = 	curr_EventID;
						curr_T_Event = 	curr_T;
					}
				}

				prev_T = curr_T;
		
			//WRITE CLUSTER INTO CLUSTER STORAGE

				v_ClusterVar[i_T] = curr_T;
				v_ClusterVar[i_EventID] = curr_EventID;

				vv_Clusters.push_back(v_ClusterVar);

			//CHECK MAX COUNT OF CLUSTERS

				if(N_ClusterToDo > 0 && LineNum-2 > N_ClusterToDo ) 
				{
					Print_Info(FileLog, "Process terminated after processing of " + to_string(LineNum-2) + " of clusters.", 1, DoPrintOut, DoLog);
					break;
				}

		}


		return RetCon; 
	}

	int Elist::Scan()
	{
		int RetCon =  COINCMATCH_ERR_NO_ERROR;

		if(File == nullptr || !File->is_open())
		{
			Print_Error(nullptr, to_string(COINCMATCH_ERR_ELIST_NOT_OPEN) +  " : Elist is not opened.: " + FileIn_Path + FileIn_Name + "." , true, false);
			cerr << COINCMATCH_ERR_ELIST_NOT_OPEN << ";";
			return -1;
		}			

		string Line = "";

		while(getline(*File, Line))
		{
			LineNum++;

			if(Line.size() == 0) break;

 			if(LineNum == 1) v_VarNames = FindWordsInLine(Line);
 			if(LineNum == 2) v_VarUnits = FindWordsInLine(Line);

			if(LineNum == 2) break; 
		}

		if(v_VarNames.size() == 0 || v_VarNames.size() == 0 || Line.size() == 0)
		{
			Print_Error(nullptr, to_string(COINCMATCH_ERR_INCOR_ELIST) +  " : Incorrect elist or different data format: " + FileIn_Path + FileIn_Name + "." , true, false);
			cerr << COINCMATCH_ERR_INCOR_ELIST << ";";
			return -2;			
		}

		VarN = v_VarNames.size();

		std::vector<char> v_CharNotInc = {'\t', ' ', '\r', ':', ';', '|'};

		for (unsigned int i = 0; i < Line.size(); ++i)
		{
			if(GF_IsCharInVectorChar(Line[i], v_CharNotInc))  
			{
				Separator = Line[i];
				break;
			}
		}

		RetCon = MapIndexes();
		RetCon = GetLinesCount();

		IsTimeIn_ns = !v_VarUnits[i_T].compare(string(UNIT_TIME_ns));
		IsXYIn_mm =  !v_VarUnits[i_X].compare(string(UNIT_POSITION_mm));

		// printf("Separator\t%c\n", Separator );
		// printf("VarN\t\t%d\n", VarN );
		// PrintVec(v_VarNames);
		// PrintVec(v_VarUnits); 

		DoneScan = true;

		return RetCon;
	}

	int Elist::GetLinesCount()
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		fstream* File = new fstream((FileIn_Path + FileIn_Name).c_str(), ios_base::in);

		LineCount = CountLinesInFile(File);
		LineCount++;

		File->close();
		delete File;

		return RetCon;
	}

	int Elist::MapIndexes()
	{
		int RetCon = COINCMATCH_ERR_NO_ERROR;

		for (unsigned int i = 0; i < v_VarNames.size(); ++i)
		{
			if(!v_VarNames[i].compare(NAME_CLDAN_DETECTOR_ID))  i_DetectorID = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_EVENT_ID))  	i_EventID = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_X))  			i_X = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_Y))  			i_Y = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_TIME_MIN))  	i_T = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_SIZE))  		i_S = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_ENERGY)) 		i_E = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_HEIGHT))  		i_H = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_BORDER_PIX_N)) i_NBordPix = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_ROUND))  		i_Round = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_LIN)) 			i_Linear = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_POLAR_ANGLE))  i_PolarAng = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_L2D))  		i_L2D = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_WIDTH))  		i_W2D = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_LET))  		i_LET = i;
			if(!v_VarNames[i].compare(NAME_CLDAN_EPIX_MEAN)) 	i_EPix_Mean = i;
			if(!v_VarNames[i].compare("Flags")) 				i_Flags = i;

		}

		return RetCon;
	}

	bool Elist::CompareElist(Elist* o_Elist)
	{
		if(o_Elist == nullptr)				 return false;
		if(!DoneScan || !o_Elist->DoneScan)	 return false;	

		if(VarN != o_Elist->VarN) return false;

		if(v_VarNames.size() == 0 || o_Elist->v_VarNames.size() == 0) return false;

		for (unsigned int i = 0; i < v_VarNames.size(); ++i)
		{
			bool IsInc = false;

			for (unsigned int j = 0; j < o_Elist->v_VarNames.size(); ++j)
			{
				if(!v_VarNames[i].compare(o_Elist->v_VarNames[j])) 
				{
					IsInc = true;
					break;
				}
			}

			if(!IsInc) return false;
		}

		return true;
	}


//===================================================================================
//PRINT and LOG
//===================================================================================

	void Elist::Print_MainTitle()
	{
		string PrintOut = "";
		PrintOut = 
					PrintOut + "\n" + 
					"======================================================================= \n" +
					"                                  ELIST                                  \n"+
					"======================================================================= \n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, DoLog);

		return;
	}

	void Elist::Print()
	{
		string PrintOut = "\n";

		PrintOut += "---------------------------------------------------------\n";
		PrintOut += "ELIST \n\n";
		PrintOut += "FileIn_Path:\t\t" +   FileIn_Path+ "\n";
		PrintOut += "FileIn_Path:\t\t" +   FileIn_Name+ "\n";
		PrintOut += "\n";
		PrintOut += GF_PrintBool("DoPrintOut", DoPrintOut);
		PrintOut += "FileLog_Name:\t\t" +   FileLog_Name+ "\n";
		PrintOut += "FileLog_Path:\t\t" +   FileLog_Path+ "\n";		
		PrintOut += "\n";
		if(v_VarNames.size() != 0)
		{
			string Str = ""; GF_ConvertVecStrToStr( Str, v_VarNames, ';' );
			PrintOut += "VarNames:\t\t" + Str + "\n";
		}
		if(v_VarUnits.size() != 0)
		{
			string Str = ""; GF_ConvertVecStrToStr( Str, v_VarUnits, ';' );
			PrintOut += "VarUnits:\t\t" + Str + "\n";
		}
		PrintOut += "Separator (in ||):\t|"; PrintOut += Separator; PrintOut += "|\n";		
		PrintOut += "VarCount:\t\t" + to_string(VarN) +  "\n";	
		PrintOut += "\n";
		PrintOut += "LineCount (data lines):\t" + to_string(LineCount) + " (" + to_string(LineCount-2)  + ")\n";						
		PrintOut += "---------------------------------------------------------\n";

		Print_Info(FileLog, PrintOut, 0, DoPrintOut, DoLog);
		
		return;
	}	

//===================================================================================
	

#endif