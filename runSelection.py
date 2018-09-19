#!/bin/bash

import os
import concurrent.futures as cf
import time

#--------------------------------------------------------------------------------------------------------------------------------------------------
# Datasets and source files
#--------------------------------------------------------------------------------------------------------------------------------------------------
start = time.time()

#OFFLINE
offpath = '../Datasets_2016/'
#ONLINE
path = "/eos/user/g/gcorreia/Datasets_2016/"

dataset = {
#OFFLINE
"Signal_gogoj_750_80_Summer16": [offpath + "Signal-gogoj_750_80.root"],
#ONLINE
#"Signal_gogoj_750_80_Summer16": [path + "Signal/Signal-gogoj_750_80_v4.root", path + "Signal/Signal-gogoj_750_80_v5.root", path + "Signal/Signal-gogoj_750_80_v6.root"],  
#"Signal_gogoj_1000_100_Summer16": [path + "Signal/Signal-gogoj_1000_100_v3.root", path + "Signal/Signal-gogoj_1000_100_v4.root"], 
#"Signal_gogoj_250_40_Summer16": [path + "Signal/Signal-gogoj_250_40_v1.root"],  
#"Signal_gogoj_250_60_Summer16": [path + "Signal/Signal-gogoj_250_60_v1.root"], 
#"Signal_gogoj_500_60_Summer16": [path + "Signal/Signal-gogoj_500_60_v1.root"],  
#"Signal_gogoj_750_60_Summer16": [path + "Signal/Signal-gogoj_750_60_v1.root"],
#"Signal_gogoj_750_100_Summer16": [path + "Signal/Signal-gogoj_750_100_v1.root"],  
#"ZJetsToNuNu_HT-100To200_13TeV-madgraph": [path + "ZJets_HT100To200.root"],                                
#"ZJetsToNuNu_HT-200To400_13TeV-madgraph": [path + "ZJets_HT200To400.root"],                                
#"ZJetsToNuNu_HT-400To600_13TeV-madgraph": [path + "ZJets_HT400To600.root"],                                       
#"ZJetsToNuNu_HT-600To800_13TeV-madgraph": [path + "ZJets_HT600To800_1_500.root"],
#"ZJetsToNuNu_HT-800To1200_13TeV-madgraph": [path + "ZJets_HT800To1200_1_200.root", path + "ZJets_HT800To1200_201_318.root"],                                    
#"ZJetsToNuNu_HT-1200To2500_13TeV-madgraph": [path + "ZJets_HT1200To2500.root"],                                   
#"ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph": [path + "ZJets_HT2500ToInf.root"],                                    
#"TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "TTJets_1_600.root", path + "TTJets_601_1264.root"],    
#"WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT100To200_1_400.root", path + "WJets_HT100To200_401_800.root", path + "WJets_HT100To200_801_1312.root"],              
#"WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT200To400_1_400.root", path + "WJets_HT200To400_401_726.root"],              
#"WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT400To600.root"],              
#"WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT600To800.root"],              
#"WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT800To1200.root"],             
#"WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT1200To2500.root"],            
#"WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "WJets_HT2500ToInf.root"],             
#"QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT100To200_1_2000.root", path + "QCD_HT100To200_2001_3500.root", path + "QCD_HT100To200_3501_5400.root", path + "QCD_HT100To200_5401_7300.root", path + "QCD_HT100To200_7301_8099.root"],                      
#"QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT200To300.root"],                      
#"QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT300To500.root"],                      
#"QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT500To700.root"],                      
#"QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT700To1000.root"],                     
#"QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT1000To1500_1_200.root", path + "QCD_HT1000To1500_201_432.root"],                    
#"QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT1500To2000_1_200.root", path + "QCD_HT1500To2000_201_409.root"],                    
#"QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "QCD_HT2000ToInf.root"], 
#"DYJetsToLL_M-1To5_HT-150to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets1_5_HT150To200_1_1500.root", path + "DYJets1_5_HT150To200_1501_2789.root"],      
#"DYJetsToLL_M-1To5_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets1_5_HT200To400_1_1000.root", path + "DYJets1_5_HT200To400_1001_1692.root"],      
#"DYJetsToLL_M-1To5_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets1_5_HT400To600_1_1300.root", path + "DYJets1_5_HT400To600_1301_2459.root"],       
#"DYJetsToLL_M-1To5_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets1_5_HT600ToInf.root"], 
#"DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets_HT100To200.root"],      
#"DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets_HT200To400.root"],      
#"DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets_HT400To600.root"],       
#"DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets_HT600ToInf.root"],
#"DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT70To100_1_700.root", path + "DYJets50_HT70To100_701_1286.root"],  
#"DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT100To200.root"], 
#"DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT200To400.root"],
#"DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT400To600.root"],       
#"DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT600To800_1_500.root", path + "DYJets50_HT600To800_501_1003.root"],       
#"DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT800To1200.root"],      
#"DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT1200To2500.root"],     
#"DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "DYJets50_HT2500ToInf.root"],      
#"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4": [path + "ST_tW_top_5f.root"],            
#"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4": [path + "ST_tW_antitop_5f.root"],           
#"ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8": [path + "ST_s-channel_4f.root"],
#"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1": [path + "ST_t-channel_antitop_4f_1_1000.root", path + "ST_t-channel_antitop_4f_1001_2000.root", path + "ST_t-channel_antitop_4f_2001_3000.root", path + "ST_t-channel_antitop_4f_3001_4071.root"],
#"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1": [path + "ST_t-channel_top_4f_1_1700.root", path + "ST_t-channel_top_4f_1701_3400.root", path + "ST_t-channel_top_4f_3401_5100.root", path + "ST_t-channel_top_4f_5101_6500.root", path + "ST_t-channel_top_4f_6501_6999.root"],
#"ZZ_TuneCUETP8M1_13TeV-pythia8": [path + "ZZ.root"],
#"WW_TuneCUETP8M1_13TeV-pythia8": [path + "WW.root"],
#"WZ_TuneCUETP8M1_13TeV-pythia8": [path + "WZ.root"],
#"GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "GJets_HT40To100.root"],
#"GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "GJets_HT100To200.root"],
#"GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "GJets_HT200To400_1_1000.root", path + "GJets_HT200To400_1001_1914.root"],
#"GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "GJets_HT400To600.root"],
#"GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "GJets_HT600ToInf.root"],
#"Data_MET_Run2016B-23Sep2016": [path + "DATA_RUN2016B_1_1000.root", path + "DATA_RUN2016B_1001_2000.root", path + "DATA_RUN2016B_2001_3000.root", path + "DATA_RUN2016B_3001_4000.root", path + "DATA_RUN2016B_4001_5000.root", path + "DATA_RUN2016B_5001_5272.root"],
#"Data_MET_Run2016C-23Sep2016": [path + "DATA_RUN2016C_1_600.root", path + "DATA_RUN2016C_601_1200.root", path + "DATA_RUN2016C_1201_1738.root"], 
#"Data_MET_Run2016D-23Sep2016": [path + "DATA_RUN2016D_1_800.root", path + "DATA_RUN2016D_801_1600.root", path + "DATA_RUN2016D_1601_2400.root", path + "DATA_RUN2016D_2401_2916.root"],
#"Data_MET_Run2016E-23Sep2016": [path + "DATA_RUN2016E_1_800.root", path + "DATA_RUN2016E_801_1600.root", path + "DATA_RUN2016E_1601_2478.root"],
#"Data_MET_Run2016F-23Sep2016": [path + "DATA_RUN2016F_1_900.root", path + "DATA_RUN2016F_901_1808.root"], 
#"Data_MET_Run2016G-23Sep2016": [path + "DATA_RUN2016G_1_1000.root", path + "DATA_RUN2016G_1001_2000.root", path + "DATA_RUN2016G_2001_3000.root", path + "DATA_RUN2016G_3001_4000.root", path + "DATA_RUN2016G_4001_4269.root"],
#"Data_MET_Run2016H-Prompt": [path + "DATA_RUN2016H2_1_1000.root", path + "DATA_RUN2016H2_1001_2000.root", path + "DATA_RUN2016H2_2001_3000.root", path + "DATA_RUN2016H2_3001_4000.root", path + "DATA_RUN2016H2_4001_4622.root", path + "DATA_RUN2016H3.root"],
} 
#"ZJetsToNuNu_HT-600To800_13TeV-madgraph": [path + "ZJets_HT600To800.root"], 
#"ZJetsToNuNu_HT-600To800_13TeV-madgraph": [path + "ZJets_HT600To800_1_500.root", path + "ZJets_HT600To800_501_936.root"],
#"TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "TTJets_HT600To800_1_500.root", path + "TTJets_HT600To800_501_1000.root", path + "TTJets_HT600To800_1001_1500.root", path + "TTJets_HT600To800_1501_1935.root"], 
#"TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "TTJets_HT800To1200_1_400.root", path + "TTJets_HT800To1200_401_800.root", path + "TTJets_HT800To1200_801_1200.root", path + "TTJets_HT800To1200_1201_1417.root"],
#"TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "TTJets_HT1200To2500_1_150.root", path + "TTJets_HT1200To2500_151_314.root"],
#"TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path + "TTJets_HT2500ToInf.root"],
#"ST_t-channel_4f_scaledown_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1": [path + "ST_t-channel_4f_1_1000.root", path + "ST_t-channel_4f_1001_1918.root"],   

#--------------------------------------------------------------------------------------------------------------------------------------------------
# Configuration
#--------------------------------------------------------------------------------------------------------------------------------------------------
selection = "SignalRegions"

ApplyEventWeights = 1
TARGET_LUMI = 35920     #pb-1
ApplyPileupWeights = 1

Get_Histograms = 1
Get_Tree = 1
Get_Image_in_EPS = 0
Get_Image_in_PNG = 1
Get_Image_in_PDF = 0

cuts = {
"JET_ETA_CUT          ": 2.4,
"MUON_PT_CUT          ": 15,       # GeV
"ELECTRON_PT_CUT      ": 15,       # GeV
"LEADING_SV_JET_CUT   ": 10000,    # GeV
"JET_PT_CUT_SV        ": 30,       # GeV
"JET_PT_CUT_PV        ": 30,       # GeV
"SUBJET_PT_CUT_PV     ": 90,       # GeV
"MJJ_CUT              ": 60,       # GeV
"MET_CUT              ": 350,      # GeV
"MVA_CUT_SV_750_80    ": -0.05,  
"MVA_CUT_SV_1000_100  ": 0.29,
"Track                ": 1,        # 0 -> Linear, 1 -> Curved
"ExtraVariables       ": 1,        
}


#--------------------------------------------------------------------------------------------------------------------------------------------------
# [DO NOT TOUCH THIS PART]
#--------------------------------------------------------------------------------------------------------------------------------------------------

#for dataset, source in dataset.items():   
def analyze_dataset(datasetName):
    stat = "Dataset " + datasetName + " got an error."
    
    ConfigFile = "Configuration/ConfigFile_" + datasetName + ".txt"
    out = open(ConfigFile, "w")
    
    out.write("Selection            " + selection                              + "\n") 

    out.write("InputTree            RecoData                                 " + "\n")
    out.write("InputType            1                                        " + "\n")
    out.write("RequireGenBranches   0                                        " + "\n")
    out.write("GenFileName          none                                     " + "\n")
    """
    out.write("InputType            2                                        " + "\n")
    out.write("RequireGenBranches   1                                        " + "\n")
    out.write("GenFileName          ../../Offline_datasets/Signal_750_80_gen.root" + "\n")
    """
    out.write("DatasetName          " + datasetName                            + "\n")
    for i in range(0,len(dataset[datasetName])):
        out.write("InputFile            " + dataset[datasetName][i]            + "\n") 

    out.write("MetadataFileName     ./Configuration/DatasetMetadata.txt      " + "\n")
    out.write("TARGET_LUMI          " + str(TARGET_LUMI)                       + "\n")
    out.write("PileupFileName       ./Configuration/PileupHistograms.root    " + "\n")
    if( datasetName[:4] == "Data" ):
        out.write("ApplyEventWeights    " + str(0)                             + "\n")
        out.write("ApplyPileupWeights   " + str(0)                             + "\n")
    else:
        out.write("ApplyEventWeights    " + str(ApplyEventWeights)             + "\n")
        out.write("ApplyPileupWeights   " + str(ApplyPileupWeights)            + "\n")

    out.write("Get_Histograms       "  + str(Get_Histograms)                   + "\n")
    out.write("Get_Tree             "  + str(Get_Tree)                         + "\n")
    out.write("Get_Image_in_EPS     "  + str(Get_Image_in_EPS)                 + "\n")
    out.write("Get_Image_in_PNG     "  + str(Get_Image_in_PNG)                 + "\n")
    out.write("Get_Image_in_PDF     "  + str(Get_Image_in_PDF)                 + "\n")
    
    for cut, value in cuts.items():
        out.write( cut + str(value)                                            + "\n")
    out.close()
    
    runCommand = './RunAnalysis ' + ConfigFile
    os.system(runCommand)
    
    removeCommand = "rm " + ConfigFile
    os.system(removeCommand)
    
    out2 = open(selection + "/" + datasetName + "/" + "cutflow.txt", "a")
    for cut, value in cuts.items():
        out2.write( cut + str(value)  + "\n")
    out2.write("-----------------------------------------------------------------------------------")  
    out2.close()
    
    stat = "Dataset " + datasetName + " processed."
    
    return stat

for datasetName, status in zip( dataset.keys(), cf.ProcessPoolExecutor().map(analyze_dataset, dataset.keys()) ):
    #print(status)
    print("")


end = time.time()
hours = int((end - start)/3600)
minutes = int(((end - start)%3600)/60)
seconds = int(((end - start)%3600)%60)

print("")
print("-----------------------------------------------------------------------------------")
print("Total process duration: " + str(hours) + " hours " + str(minutes) + " minutes " + str(seconds) + " seconds")  
print("-----------------------------------------------------------------------------------")
print("")

   
for datasetName in dataset.keys():       
    CutflowFile = selection + '/' + datasetName + '/' + "cutflow.txt"
    out = open(CutflowFile, "r")
    for line in out:
        if( line.rstrip()[:4] == "Time" ):
            print(line.rstrip())
            print('-----------------------------------------------------------------------------------')
            print(' ')
            break
        else:
            print(line.rstrip())
    out.close()

