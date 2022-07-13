Testing Procedure for DPE
===============================================================
Date:               1/7/2022
Author:             Lukáš Marek (lukas.marek@advacam.com) 

-------------------------------------------------------------------------------
Intro and Run
-------------------------------------------------------------------------------

System testing procedure based on file comparison
Estimated time duration: 35s
If some preponderances are found then it is written into file `./test.log.txt`  which is overwritten before each test run.

Standalone run can be done in the main directory of DPE with following command on linux system:

`python Test/tests.py -b Release/Linux/`

-------------------------------------------------------------------------------
List of tests
-------------------------------------------------------------------------------

List of tests which are implemented:

 1) **T3PA input** - t3pa input with default settings
 2) **Several T3PAs input** - several t3pa files as input with default settings
 3) **CLOG tot+toa TPX3 input** - clog tot+toa from TPX3 with default settings
 4) **CLOG tot TPX input** - clog tot from TPX with default settings
 5) **CLOG itot+count TPX3 input** - clog itot+count from TPX3 with default settings
 6) **Hist with T3PA** - Hist settings with T3PA file as input
 7) **Filter with T3PA** - Filter settings with T3PA file as input
 8) **SigVec with T3PA** - SigVec settings with T3PA file as input
 9) **Mask with T3PA** - Mask settings with T3PA file as input
 10) **Comparator with T3PA and CdTe** - Comparator with T3PA file as input
 11) **Elist input** - elist as input with default settings
 12) **Generated t3pa input** - pregenerated t3pa for physical variables etc.
 13) **SigVec and Hist with T3PA** - SigVec and Hist settings with T3PA file as input to produce SigVec from 2D hist
 14) **CLOG event input** - clog event with default settings
 15) **CLOG toa input** - clog toa with default settings
 16) **CLOG tot+toa proc input** - clog tot+toa after processing with default settings
 17) **T3P input** - t3p input with default settings
 <!-- 18) **T3R input** - t3r input with default settings -->
 19) **Matrix event input** - matrix event input with default settings
 20) **Matrix tot input** - matrix tot input with default settings
 21) **Elist extended input** - elist extended input with default settings
 22) **Graphics output tot+toa TPX3 input** - graphics output for tot+toa TPX3 input with default settings
 23) **Several T3PAs input, just dir name** - several t3pa files, just specifying dir name as input with default settings
 24) **Comparator with own DB** - input is own DB for camparator and settings of SigVec and Hist for t3pa input

 514) **Err - missing param file** - error behavior without parameters file (-1000)
 515) **Err - empty file** - error behavior with empty file file (-1020)
 516) **Err - simple elist** - error behavior with simple elist (-1014)
 517) **Err - nonsense file** - error behavior with nonsense file (-1017)
 518) **Err - empty clog** - error behavior with empty clog (-1019)
 519) **Err - incorrect clog** - error behavior with incorrect clog (-1018)
 520) **Err - partial elist** - error behavior with partial elist (-1016)
 520) **Err - dsc file** - error behavior with dsc file (-1017)

-------------------------------------------------------------------------------
Creating New Reference Files
-------------------------------------------------------------------------------

Only if major change is done in the file/directory structure  

 * Run the tests
 * Copy the content of out into ref


-------------------------------------------------------------------------------