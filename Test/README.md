Testing Procedure for Coincidence Matching algortihms
===============================================================
Date:               1/7/2022
Author:             Lukáš Marek (lukas.marek@advacam.com) 

-------------------------------------------------------------------------------
Intro and Run
-------------------------------------------------------------------------------

System testing procedure based on file comparison
If some preponderances are found then it is written into file `./test.log.txt`  which is overwritten before each test run.

Standalone run can be done in the main directory of DPE with following command on linux system:

`python Test/tests.py -b Devel/`

-------------------------------------------------------------------------------
List of tests
-------------------------------------------------------------------------------

List of tests which are implemented:

 1) **T3PA input** - t3pa input with default settings

 501) **Err - dsc file** - error behavior with dsc file (-1017)

-------------------------------------------------------------------------------
Creating New Reference Files
-------------------------------------------------------------------------------

Only if major change is done in the file/directory structure  

 * Run the tests
 * Copy the content of out into ref


-------------------------------------------------------------------------------