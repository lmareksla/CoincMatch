//MAIN HEADERS

	#include <stdio.h> 
	#include <stdlib.h> 
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <vector>
	#include <sstream>
	#include <chrono> 
	#include <iomanip>
	#include <math.h>
	#include <thread>
	#include <algorithm>
	#include <random>
	//#include <filesystem>
	#include <ctype.h>

//LIB FOR WORK WITH FILES IN LINUX

	#if defined(unix) || defined(__unix__) || defined(__unix)
		#include <unistd.h>
		#include <dirent.h>
	#else
		#include <dirent_win.h>
		#include <direct.h>
	#endif

	#include <sys/types.h>
	#include <sys/stat.h>

//MY LIBS

	#include "INI_File.h"
	#include "GenFunc.h"

	#include "Hist1D.h"
	#include "Hist2D.h"
	#include "Hist_ProcessFile.h"

	#include "Filter.h"


//ROOT LIBRARIES

#if !NOT_ROOT_USE

	#include "TH2.h"
	#include "TH1.h"
	#include "TFile.h"
	#include "TTree.h"
	#include "TChain.h"
	#include "TBranch.h"
	#include "TCanvas.h"
	#include "TPad.h"
	#include "TObject.h"
	#include "TObjArray.h"
	#include "TMath.h"
	#include "TLegend.h"
	#include "TLatex.h"
	#include "TStyle.h"
	#include "TPaletteAxis.h"
	#include "TSystem.h"
	#include "THStack.h"
	#include "TPaveText.h"
	#include "TDirectory.h"
	#include "TMultiGraph.h"
	#include "TH3.h"
	#include "TPolyLine3D.h"
	#include <TGraph.h>
	#include <TGraphErrors.h>
	#include <TGraphMultiErrors.h>
	#include <TGraph2D.h>
	#include "TGraph2DErrors.h"
	#include "TRandom.h"
	#include "TColor.h"
	#include "TMathText.h"
	#include "TDatime.h"
	#include "TF1.h"

	#include "ROOT_Plot.h"

#endif


//ADDITIONAL VARIABLES

	#if defined(unix) || defined(__unix__) || defined(__unix)
		#ifndef DIR_SLASH
			#define DIR_SLASH "/"
		#else 
			#undef DIR_SLASH
			#define DIR_SLASH "/"
		#endif
	#else
		#ifndef DIR_SLASH
			#define DIR_SLASH "\\"
		#else
			#undef DIR_SLASH
			#define DIR_SLASH "\\"
		#endif
	#endif
