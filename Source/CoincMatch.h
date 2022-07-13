#include "Headers.h"

using namespace std;

#define CoincMatch_PROG_VER				"1.0.0"

#define COINCMATCH_ERR_NO_ERROR			0 		//No error occurred.
#define COINCMATCH_ERR_LOG_FILE_OPEN	-100 	//Can not open log file.
#define COINCMATCH_ERR_CONFIG_FILE_OPEN	-101 	//Can not open config file.


#ifndef CLASS_CoincMatch
#define CLASS_CoincMatch

class CoincMatch
{
	//===================================================================================
	//DESTRUCTOR, CUNTRUCTOR and INIT FUNC
	//===================================================================================
		
		public:

			CoincMatch(bool con_UseStandalone = true);
			CoincMatch(string con_FileConfig_Path, string con_FileConfig_Name, bool con_UseStandalone = true);

			~CoincMatch()
			{
				Delete_CheckNull(FileLog);
				Delete_CheckNull(FileConfig);
			}

			//Constructor init called in each conctructor.
			int ConstructorInit();


			//Init fuction.
			int Init();

		protected:

			string ProgVer;			//Program version.

			bool UseStandalone;		//Control to use CoincMatch as standalone.

	//===================================================================================
	//INPUT VARIABLES
	//===================================================================================
		
		protected:

			string FileIn_Path;		//
			string FileIn_Name;		//

	//===================================================================================
	//
	//===================================================================================
	

	//===================================================================================
	//
	//===================================================================================
	


	//===================================================================================
	//CONFIG
	//===================================================================================
	
		protected:

			INI_File* FileConfig;		//

			string FileConfig_Path;		//
			string FileConfig_Name;		//

		public:

			//
	 		int LoadConfig();

	//===================================================================================
	//EXPORT/OUTPUT
	//===================================================================================;
		protected:

			bool DoExport;				//
		 	bool DoneExport;			//

			string FileOut_Path;		//
			string FileOut_Name;		//
			string FileOut_EndData;		//
			string FileOut_EndInfo;		//

		public:

			//
			int Export();

	//===================================================================================
	//PRINT and LOG
	//===================================================================================
	
		protected:

			bool DoPrintOut;		//

			bool DoLog;				//	
			string FileLog_Name;	//
			string FileLog_Path;	//
			fstream *FileLog;		//

		public:

			void Print_MainTitle();	//
			void Print_BasicInfo();	//

			//
			string PrintBool(string VarName, bool VarVal);
			
			//
			void Print();

			//Throw error and print it into cerr.
			//Error - error code which should be in throw and printed.
			void Error_ThrowAndCerr(int Error);

	//===================================================================================
	//SET AND GET FUCTIONS
	//===================================================================================
		
		public:

			void Set_FileIn_Name(string set_FileIn_Name){FileIn_Name = set_FileIn_Name; return;}
			void Set_FileIn_Path(string set_FileIn_Path){FileIn_Path = set_FileIn_Path; return;}

			void Set_FileOut_Path(string set_FileOut_Path){FileOut_Path = set_FileOut_Path;return;}
			void Set_FileOut_Name(string set_FileOut_Name){FileOut_Name = set_FileOut_Name; return;}

			void Set_DoPrintOut(bool set_DoPrintOut){DoPrintOut = set_DoPrintOut; return;}
			void Set_DoLog(bool set_DoLog){DoLog = set_DoLog; return;}
		
	//===================================================================================
	
};

#endif
