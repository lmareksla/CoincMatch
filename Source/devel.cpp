#include "Headers.h"
#include "CoincMatch.h"
#include "Elist.h"

using namespace std;

int main(int argc, char const *argv[])
{
	int Case = 1; 
	if(argc > 1)
	{
		stringstream s(argv[1] );
		s >> Case;
	}

	string FileConfig_Path = "/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/DataProcessing/PreProcessing/Coincidence_Matching/Devel/ConfigFile/";

	switch(Case) 
	{
	    case 1 : 
    	{
		//===================================================================================
		//BASIC FUCTIONALITY
		//===================================================================================

    		printf("Test basic functionality.\n");

    		string DirTest_Path = "/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/DataProcessing/PreProcessing/Coincidence_Matching/Devel/Test/ReadElist/Input/";

    		CoincMatch* o_CoincMatch = new CoincMatch(FileConfig_Path, "ConfigFile.ini");

    		o_CoincMatch->Print_Help();
    		o_CoincMatch->Print_Version();
    		o_CoincMatch->Print_MainTitle();
    		o_CoincMatch->Print();

    		delete o_CoincMatch;

		//===================================================================================
		}
        break;

	    case 2 :
    	{
		//===================================================================================
		//ERROR FUCNTIONALITY
		//===================================================================================

    		printf("Test error functionality.\n");

    		//CoincMatch* o_CoincMatch = new CoincMatch(FileConfig_Path, "ConfigFile.ini");

    		//MISSING CONFIG FILE

	    		CoincMatch* o_CoincMatch = new CoincMatch("", "ConfigFile.ini");
	    		delete o_CoincMatch;

	    	//CAN NOT OPEN LOG FILE

	    		o_CoincMatch = new CoincMatch(FileConfig_Path, "ConfigFile_ErrorLog.ini");
	    		delete o_CoincMatch;

		//===================================================================================
		}
	    break;

	    case 3 : 
    	{
		//===================================================================================
		//TEST ELIST
		//===================================================================================

    		printf("Test basic functionality.\n");

    		string DirTest_Path = "/mnt/MainDisk/Soubory/Programy/Vlastni/c++/aplikace/DataProcessing/PreProcessing/Coincidence_Matching/Devel/Test/ReadElist/Input/";
    		string ElistName = "DataDriven_Elist_Full.txt";

    		Elist* o_Elist = new Elist(DirTest_Path, ElistName);

    		o_Elist->Print_MainTitle();
    		o_Elist->Print();

    		o_Elist->Scan();
    		o_Elist->Load();

    		std::vector<std::vector<double> > vv_Clusters = o_Elist->Get_Clusters();

    		for (unsigned int i = 0; i < vv_Clusters.size(); ++i)
    		{
    			PrintVec(vv_Clusters[i]);
    		}

    		delete o_Elist;

		//===================================================================================
		}
        break;

	    case 4 : 
    	{
		//===================================================================================
		//TEST COINC MATCH
		//===================================================================================

    		printf("Test coinc match load elists from config.\n");

    		CoincMatch* o_CoincMatch = new CoincMatch(FileConfig_Path, "ConfigFile_LoadElist.ini");

    		o_CoincMatch->ProcessData();

    		delete o_CoincMatch;

		//===================================================================================
		}
        break;

	}
	
	return 0;
}

