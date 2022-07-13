#include "Headers.h"
#include "CoincMatch.h"

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

    		CoincMatch* o_CoincMatch = new CoincMatch(FileConfig_Path, "ConfigFile.ini");
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
	}
	
	return 0;
}

