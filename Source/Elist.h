#include "Headers.h"
#include "GF.h"

using namespace std;

#ifndef CLASS_ELIST
#define CLASS_ELIST

class Elist
{
	//===================================================================================
	//DESTRUCTOR, CUNTRUCTOR and INIT FUNC
	//===================================================================================
		
		public:

			Elist(bool con_UseStandalone = true);
			Elist(string con_FileIn_Path, string con_FileIn_Name, bool con_UseStandalone = true);

			~Elist()
			{
				if(UseStandalone) Delete_CheckNull(FileLog);
				if(File->is_open())
				{
					File->close();
					Delete_CheckNull(File);
				}
			}

			//Constructor init called in each conctructor.
			int ConstructorInit();

			//Init function.
			int Init();

		protected:

			bool UseStandalone;		//Control to use CoincMatch as standalone.

	//===================================================================================
	//FORMAT AND SCAN OF FORMAT
	//===================================================================================
	
		protected:

			string FileIn_Path;		//
			string FileIn_Name;		//

			fstream *File;			//

			std::vector<string> v_VarNames;		//
			std::vector<string> v_VarUnits;		//
			char Separator;						//		
			int VarN;

			bool DoneScan;

			bool IsTimeIn_ns;
			bool IsXYIn_mm;

			int i_T;				//			
			int i_X; 				//			
			int i_Y; 				//
			int i_E; 				//
			int i_S; 				//
			int i_H; 				//
			int i_PolarAng; 		//
			int i_L2D; 				//
			int i_W2D; 				//
			int i_WStd_Perp; 		//
			int i_WStd_Along; 		//
			int i_Round; 			//
			int i_Linear; 			//
			int i_NBordPix; 		//
			int i_Thick; 			//
			int i_Thin; 			//
			int i_CurlyThin; 		//
			int i_EPix_Mean; 		//
			int i_LET; 				//
			int i_DetectorID;		//		
			int i_EventID;			//	
			int i_Flags;			//

			int LineCount;			//

			std::vector<std::vector<double>> vv_Clusters;		//

		public:

			//
			int Scan();

			//
			int GetLinesCount();

			//
			int MapIndexes();

			//Compare this elist with input elist - name and units of var
			//o_Elist - elist which should be compared with this elist
			bool CompareElist(Elist* o_Elist);


	//===================================================================================
	//LOAD EVENTS/CLUSTERS
	//===================================================================================
	
		protected:

			double T_First;
			double T_OffSet;

			double EventID_Offset;

			double prev_T;
			double prev_EventID;
			double curr_T_Event;

			int N_NanLines;
			int N_InfLines;	

			long int N_ClusterDone;				//Count of clusters already read/done in all calls of load function.
			long int N_ClusterToDo;				//Count clusters which should be done in the load.
			long int N_ClusterDoneInCurrLoad;	//Count of clusters done in the current load.

			int LineNum;						//Count of lines processed in the File.


		public:

			//Load of elist clusters into vv_Clusters where time is converted into ns and x and y coord in mm into px.
			int Load();

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

			//
			void Print();

	//===================================================================================
	//SET AND GET FUCTIONS
	//===================================================================================

		public:

			void Set_DoPrintOut(bool set_DoPrintOut){DoPrintOut = set_DoPrintOut; return;}
			void Set_DoLog(bool set_DoLog){DoLog = set_DoLog; return;}
			void Set_FileLog(fstream* set_FileLog){FileLog = set_FileLog; return;}

			void Set_N_ClusterToDo(long int  set_N_ClusterToDo) {N_ClusterToDo = set_N_ClusterToDo; return;}

			double  Get_T_First() {return T_First;}
			double  Get_T_OffSet() {return T_OffSet;}
			double  Get_EventID_Offset() {return EventID_Offset;}
			double  Get_prev_T() {return prev_T;}
			double  Get_prev_EventID() {return prev_EventID;}
			double  Get_curr_T_Event() {return curr_T_Event;}
			int  Get_N_NanLines() {return N_NanLines;}
			int  Get_N_InfLines() {return N_InfLines;}
			long int  Get_N_ClusterDone() {return N_ClusterDone;}
			long int  Get_N_ClusterToDo() {return N_ClusterToDo;}
			long int  Get_N_ClusterDoneInCurrLoad() {return N_ClusterDoneInCurrLoad;}
			int  Get_LineNum() {return LineNum;}



			std::vector<std::vector<double>> Get_Clusters(){return vv_Clusters;}
			std::string Get_FileIn_Path(){return FileIn_Path;}
			std::string Get_FileIn_Name(){return FileIn_Name;}

	//===================================================================================

};

#endif
