#%%
#Run from main DPE dir with command on linux: python ./Test/tests.py -b ./Release/Linux/ for testing bin in dir release
#
import argparse
import unittest
import platform
import os
import filecmp
from pathlib import Path
import shutil

def system2DPE(system):
    switcher = {
        "Linux": "dpe.sh", 
        "Windows": "DPE.exe",
        "Mac": "DPE",

    }
    assert(system in switcher)
    return switcher.get(system)

class DPETest(unittest.TestCase):

    def __init__(self, testname, DPE):
        super(DPETest, self).__init__(testname)
        self.DPE = DPE 

        self.do_mirror_compare = True

    def add_log_entry(self, entry):
        file_log = open("./test_log.txt", 'a')
        file_log.write(entry + "\n")
        file_log.close()

    def compare_files(self, path_out, path_ref, file):
        if file.find(".") == 0: return -1
        if file.find(".png") != -1: return -1
        if file.find(".idx") != -1: return -1                
        if os.path.isdir(path_out + file): 
            self.compare_dir(path_out, path_ref, file)
            return 0

        rv = filecmp.cmp(path_out + file, path_ref + file, shallow=False)

        if(not rv):
            print(path_out + file)
            self.add_log_entry(path_out + file)

        self.assertTrue(rv)
        return 0        

    def compare_dir(self, folder_out, folder_ref, directory):
        dir_cont_sub = os.listdir(folder_out + directory)

        #Check whether directory structure is the same
        rv = os.path.isdir(folder_ref + directory) 
        if(not rv): self.add_log_entry(folder_out + directory)            
        self.assertTrue(rv)

        for cont in dir_cont_sub:
            if self.compare_files(folder_out + directory + '/', folder_ref + directory + '/', cont):
                continue        

    def compare_DPE_outputs(self, folder_out, folder_ref, directory):
        self.compare_dir(folder_out, folder_ref, directory)

    def full_dir_test(self, file_config, folder_out, folder_ref, directory):
        rv = os.system(str(self.DPE) + ' ' + str(file_config)) 
        self.assertEqual(rv, 0)
        self.compare_DPE_outputs(folder_out, folder_ref, directory)
        if self.do_mirror_compare: self.compare_DPE_outputs(folder_ref, folder_out, directory)        

    def general_test(self, num):
        file_config = "Test/data/test_" + num + "/ParametersFile.txt"
        folder_out = "Test/out/"
        folder_ref = "Test/ref/"
        self.full_dir_test(file_config, folder_out, folder_ref, "test_" + num)

    def error_test(self, num, rv_expected):
        file_config = "Test/data/test_" + num + "/ParametersFile.txt"
        folder_out = "Test/out/"
        folder_ref = "Test/ref/"
        rv = os.system( str(self.DPE) + ' ' + str(file_config)) 
        file_rv = open(".ret_val_dpe.txt", 'r')
        for line in file_rv:
            line = line[:line.find(";")]
            rv = int(line)
        os.remove(".ret_val_dpe.txt") 
        self.assertEqual(rv, rv_expected)


    #Detector - TPX3
    #Input -    t3pa
    def test_001(self):
        self.general_test("001")

    #Detector - TPX3
    #Input -    multi file t3pa
    def test_002(self):
        self.general_test("002")

    #Detector - TPX3
    #Input -    frame clog tot+toa 
    def test_003(self):
        self.general_test("003")
    
    #Detector - TPX
    #Input -    frame clog tot
    def test_004(self):
        self.general_test("004")

    #Detector - TPX3
    #Input -    frame clog itot+count
    def test_005(self):
        self.general_test("005")

    #Detector - TPX3
    #Input -    t3pa 
    #Add -      Hist.ini
    def test_006(self):
        self.general_test("006")

    #Detector - TPX3
    #Input -    t3pa 
    #Add -      Filter.ini
    def test_007(self):
        self.general_test("007")
    
    #Detector - TPX3
    #Input -    t3pa 
    #Add -      SigVec.ini
    def test_008(self):
        self.general_test("008")

    #Detector - TPX3
    #Input -    t3pa 
    #Add -      Mask.txt
    def test_009(self):
        self.general_test("009")

    #Detector - TPX3 CdTe 2mm
    #Input -    t3pa 
    #Add -      Comparator
    def test_010(self):
        self.general_test("010")

    #Detector - TPX3 
    #Input -    elist
    def test_011(self):
        self.general_test("011")

    #Detector - TPX3 
    #Input -    t3pa no calibration, predefined values in table
    def test_012(self):
        self.general_test("012")

    #Detector - TPX3 
    #Input -    t3pa 
    #Add -      SigVec.ini, Hist.ini 
    def test_013(self):
        self.general_test("013")

    #Detector - TPX
    #Input -    clog event 
    def test_014(self):
        self.general_test("014")

    #Detector - TPX 
    #Input -    clog toa 
    def test_015(self):
        self.general_test("015")        

    #Detector - TPX3 
    #Input -    clog proc tot+toa 
    def test_016(self):
        self.general_test("016")

    #Detector - TPX3 
    #Input -    t3p 
    def test_017(self):
        self.general_test("017")      

    #Detector - TPX3 
    #Input -    t3r
    # def test_018(self):
    #     self.general_test("018")

    #Detector - TPX 
    #Input -    matrix event
    def test_019(self):
        self.general_test("019")        

    #Detector - TPX
    #Input -    matrix tot 
    def test_020(self):
        self.general_test("020")

    #Detector - TPX3 
    #Input -    elist extended 
    def test_021(self):
        self.general_test("021")      

    #Detector - TPX3 
    #Input -    clog tot+toa 
    #Output -   graphics
    def test_022(self):
        self.general_test("022") 

    #Detector - TPX3 
    #Input -    clog tot+toa 
    #Input only dir name
    def test_023(self):
        self.general_test("023") 

    #Detector - TPX3 
    #Input -    clog tot+toa 
    #Testing comparator with own DB
    def test_024(self):
        self.general_test("024") 

    #Error
    #Input -    missing param file
    def test_514(self):
        self.error_test("514", -1000)
    
    #Error
    #Input -    empty t3pa file 
    def test_515(self):
        self.error_test("515", -1020)
    
    #Error
    #Input -    simple elist
    def test_516(self):
        self.error_test("516", -1014)
    
    #Error
    #Input -    random unsupported file
    def test_517(self):
        self.error_test("517", -1017)

    #Error
    #Input -    empty clog
    def test_518(self):
        self.error_test("518", -1019)

    #Error
    #Input -    incorrect clog 
    def test_519(self):
        self.error_test("519", -1018)

    #Error
    #Input -    partial elist
    def test_520(self):
        self.error_test("520", -1016)

    #Error
    #Input -    dsc file
    def test_521(self):
        self.error_test("521", -1017)


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Run Sytem Tests for DPE.')
    parser.add_argument('-b', '--build-path', action='store',
                        default='.', help='path to DPE binary')

    arguments = parser.parse_args()
    DPE = Path(arguments.build_path) / system2DPE(platform.system())

    test_loader = unittest.TestLoader()
    test_names = test_loader.getTestCaseNames(DPETest)

    suite = unittest.TestSuite()
    
    #Run all tests    
    for test_name in test_names:
       suite.addTest(DPETest(test_name, DPE))

    # Run specific test
    # suite.addTest(DPETest("test_023", DPE))

    #Remove old out and test_log and create new out
    shutil.rmtree("Test/out/")
    os.mkdir("Test/out/")
    if os.path.exists("./test_log.txt"):  os.remove("./test_log.txt")

    #Run main testing routine
    rv = unittest.TextTestRunner().run(suite)

    #Show problematic files
    if rv and os.path.exists("./test_log.txt"):
        file_log = open("./test_log.txt" , 'r')
        print("\nProblematic files and directories:")
        for line in file_log:
            print("\t",line)
        file_log.close()

# %%
