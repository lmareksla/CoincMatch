#include "Headers.h"
#include "Elist.h"
#include "GF.h"

using namespace std;


#ifndef FRAMEWORK_CoincMatch
#define FRAMEWORK_CoincMatch


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
				if(UseStandalone) Delete_CheckNull(FileLog);
				Delete_CheckNull(FileConfig);

				for (unsigned int i = 0; i < v_Elists.size(); ++i)
				{
					Delete_CheckNull(v_Elists[i]);
				}
			}

			//Constructor init called in each conctructor.
			int ConstructorInit();

			//Init fuction.
			int Init();

		protected:

			string ProgVer;			//Program version.
			string DateLastChange;	//Last date of program change..

			bool UseStandalone;		//Control to use CoincMatch as standalone.

	//===================================================================================
	//DATA PROCESSING
	//===================================================================================
	
		protected:

			std::vector<Elist*> v_Elists;
			string ElistKeyName;

			int N_Detectors;
			int N_ClusterToLoadAll;
			int N_ClusterToLoadElist;	
			std::vector<int> v_FileElists_Size;
			int FileElist_SizeMin;
			int FileElist_SizeMax;
			std::vector<bool> v_IsMoreData;
			bool IsMoreData;

			std::vector<std::vector<double> > vv_Clusters;

		public:

			//
			int ProcessData();

			//
			int CheckElistFormats();


			//
			int InsertClusterTimeSort(std::vector<double> v_Cluster);

			//
			int FindCoincMatch();

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

			//Init and scan loaded elist from INI config.
			//o_Section - section from INI config which includes info about elist.
			int InitScanElist(Section* o_Section);

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

			void Print_Help();
			void Print_Version();
			void Print_MainTitle();	//
			void Print_BasicInfo();	//
			
			//
			void Print();
	
	//===================================================================================
	//SET AND GET FUCTIONS
	//===================================================================================
		
		public:

			void Set_FileOut_Path(string set_FileOut_Path){FileOut_Path = set_FileOut_Path;return;}
			void Set_FileOut_Name(string set_FileOut_Name){FileOut_Name = set_FileOut_Name; return;}

			void Set_DoPrintOut(bool set_DoPrintOut){DoPrintOut = set_DoPrintOut; return;}
			void Set_DoLog(bool set_DoLog){DoLog = set_DoLog; return;}
			void Set_FileLog(fstream* set_FileLog){FileLog = set_FileLog; return;}

			std::vector<Elist* > Get_Elists(){return v_Elists;}


	//===================================================================================
};


#endif
