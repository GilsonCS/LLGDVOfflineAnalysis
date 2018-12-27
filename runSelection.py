#!/bin/bash

import os
import concurrent.futures as cf
import time
from shutil import copyfile

#--------------------------------------------------------------------------------------------------------------------------------------------------
# Datasets and source files
#--------------------------------------------------------------------------------------------------------------------------------------------------
start = time.time()

#OUTPUT PATH
outpath = "../Work/Analysis/Analysis_new/BackgroundMC/"

#OFFLINE
offpath = '../../Offline_datasets_2016/crabJobs_8_0_28/crab_LLGDV_Analysis_'
#ONLINE
path = "/eos/user/g/gcorreia/crabJobs_8_0_28/old/crab_LLGDV_Analysis_"

dataset = {
#OFFLINE
#"Signal_gogoj_750_80_Summer16": [offpath+"Signal-gogoj_750_80_v"+str(i)+"_full.root" for i in range(1,3)],
#"Signal_gogoj_750_80_Summer16": [offpath + "Signal-gogoj_750_80.root"],
#"ZJetsToNuNu_HT-100To200_13TeV-madgraph": [offpath + "TTJets_GT.root"],
#"ZJetsToNuNu_HT-200To400_13TeV-madgraph": [offpath + "TTJets_wJEC_DB.root"],
#"ZJetsToNuNu_HT-400To600_13TeV-madgraph": [offpath + "TTJets_JER_DB.root"],
#"ZJetsToNuNu_HT-600To800_13TeV-madgraph": [offpath + "TTJets_MET.root"],
#"ZJetsToNuNu_HT-800To1200_13TeV-madgraph": [offpath + "TTJets_FINAL.root"],
#"Signal_250_40_2J_Summer16": [offpath+"Signal_250_40_2J/results/Output_"+str(i+1)+".root" for i in range(0,2)],
#"Signal_1000_100_2J_Summer16": [offpath+"Signal_1000_100_2J/results/Output_"+str(i+1)+".root" for i in range(0,2)],
#ONLINE
#"Signal_1000_100_0J_Summer16": [path+"Signal_1000_100_0J/results/Output_"+str(i+1)+".root" for i in range(0,2)], 
#"Signal_1000_100_1J_Summer16": [path+"Signal_1000_100_1J/results/Output_"+str(i+1)+".root" for i in range(0,2)], 
#"Signal_1000_100_2J_Summer16": [path+"Signal_1000_100_2J/results/Output_"+str(i+1)+".root" for i in range(0,2)],
#"Signal_250_40_0J_Summer16": [path+"Signal_250_40_0J/results/Output_"+str(i+1)+".root" for i in range(0,2)],
#"Signal_250_40_1J_Summer16": [path+"Signal_250_40_1J/results/Output_"+str(i+1)+".root" for i in range(0,2)],
#"Signal_250_40_2J_Summer16": [path+"Signal_250_40_2J/results/Output_"+str(i+1)+".root" for i in range(0,2)],
#"ZJetsToNuNu_HT-100To200_13TeV-madgraph": [path+"ZJets_HT100To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,511)],                                
#"ZJetsToNuNu_HT-200To400_13TeV-madgraph": [path+"ZJets_HT200To400/results/RecoOutput_"+str(i+1)+".root" for i in range(0,882)],                               
#"ZJetsToNuNu_HT-400To600_13TeV-madgraph": [path+"ZJets_HT400To600/results/RecoOutput_"+str(i+1)+".root" for i in range(0,185)],                                      
#"ZJetsToNuNu_HT-600To800_13TeV-madgraph": [path+"ZJets_HT600To800/results/RecoOutput_"+str(i+1)+".root" for i in range(0,936)],
#"ZJetsToNuNu_HT-800To1200_13TeV-madgraph": [path+"ZJets_HT800To1200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,318)],                                   
#"ZJetsToNuNu_HT-1200To2500_13TeV-madgraph": [path+"ZJets_HT1200To2500/results/RecoOutput_"+str(i+1)+".root" for i in range(0,56)],                                   
#"ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph": [path+"ZJets_HT2500ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,50)],                                   
#"TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"TTJets/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1264)],
#"TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"TTJets_HT600To800/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1935)],
#"TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"TTJets_HT800To1200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1417)],
#"TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"TTJets_HT1200To2500/results/RecoOutput_"+str(i+1)+".root" for i in range(0,314)],
#"TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"TTJets_HT2500ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,153)],
#"WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT100To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1312)],             
#"WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT200To400/results/RecoOutput_"+str(i+1)+".root" for i in range(0,726)],          
#"WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT400To600/results/RecoOutput_"+str(i+1)+".root" for i in range(0,255)],           
#"WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT600To800/results/RecoOutput_"+str(i+1)+".root" for i in range(0,477)],           
#"WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT800To1200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,231)],            
#"WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT1200To2500/results/RecoOutput_"+str(i+1)+".root" for i in range(0,39)],           
#"WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"WJets_HT2500ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,49)],             
#"QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT100To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,8099)],                    
#"QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT200To300/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1976)],                   
#"QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT300To500/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1820)],                  
#"QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT500To700/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1799)],                    
#"QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT700To1000/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1576)],                    
#"QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT1000To1500/results/RecoOutput_"+str(i+1)+".root" for i in range(0,432)],                    
#"QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT1500To2000/results/RecoOutput_"+str(i+1)+".root" for i in range(0,408)],                 
#"QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"QCD_HT2000ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,204)],
#"DYJetsToLL_M-1To5_HT-150to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets1_5_HT150To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,2789)],    
#"DYJetsToLL_M-1To5_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets1_5_HT200To400/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1692)],      
#"DYJetsToLL_M-1To5_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets1_5_HT400To600/results/RecoOutput_"+str(i+1)+".root" for i in range(0,2459)],     
#"DYJetsToLL_M-1To5_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets1_5_HT600ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,207)],
#"DYJetsToLL_M-5to50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets5_50_HT100To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,109)],     
#"DYJetsToLL_M-5to50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets5_50_HT200To400/results/RecoOutput_"+str(i+1)+".root" for i in range(0,145)],     
#"DYJetsToLL_M-5to50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets5_50_HT400To600/results/RecoOutput_"+str(i+1)+".root" for i in range(0,133)],     
#"DYJetsToLL_M-5to50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets5_50_HT600ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,146)],
#"DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT100To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,698)], 
#"DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT200To400/results/RecoOutput_"+str(i+1)+".root" for i in range(0,151)],
#"DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT400To600/results/RecoOutput_"+str(i+1)+".root" for i in range(0,169)],      
#"DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT600To800/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1003)],       
#"DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT800To1200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,372)],     
#"DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT1200To2500/results/RecoOutput_"+str(i+1)+".root" for i in range(0,89)],     
#"DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"DYJets50_HT2500ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,63)],     
#"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4": [path+"ST_tW_top_5f/results/RecoOutput_"+str(i+1)+".root" for i in range(0,100)],          
#"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4": [path+"ST_tW_antitop_5f/results/RecoOutput_"+str(i+1)+".root" for i in range(0,139)],        
#"ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8": [path+"ST_s-channel_4f/results/RecoOutput_"+str(i+1)+".root" for i in range(0,299)],
#"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1": [path+"ST_t-channel_antitop_4f/results/RecoOutput_"+str(i+1)+".root" for i in range(0,4071)],
#"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1": [path+"ST_t-channel_top_4f/results/RecoOutput_"+str(i+1)+".root" for i in range(0,6999)],
#"ZZ_TuneCUETP8M1_13TeV-pythia8": [path+"ZZ/results/RecoOutput_"+str(i+1)+".root" for i in range(0,108)],
#"WW_TuneCUETP8M1_13TeV-pythia8": [path+"WW/results/RecoOutput_"+str(i+1)+".root" for i in range(0,100)],
#"WZ_TuneCUETP8M1_13TeV-pythia8": [path+"WZ/results/RecoOutput_"+str(i+1)+".root" for i in range(0,105)],
#"GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"GJets_HT100To200/results/RecoOutput_"+str(i+1)+".root" for i in range(0,530)],
#"GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"GJets_HT200To400/results/RecoOutput_"+str(i+1)+".root" for i in range(0,1914)],
#"GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"GJets_HT400To600/results/RecoOutput_"+str(i+1)+".root" for i in range(0,315)],
#"GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": [path+"GJets_HT600ToInf/results/RecoOutput_"+str(i+1)+".root" for i in range(0,255)],
#"Data_MET_Run2016B-23Sep2016": [path+"DATA_RUN2016B/results/Output_"+str(i+1)+".root" for i in range(0,27)], 
#"Data_MET_Run2016C-23Sep2016": [path+"DATA_RUN2016C/results/Output_"+str(i+1)+".root" for i in range(0,9)], 
#"Data_MET_Run2016D-23Sep2016": [path+"DATA_RUN2016D/results/Output_"+str(i+1)+".root" for i in range(0,15)],
#"Data_MET_Run2016E-23Sep2016": [path+"DATA_RUN2016E/results/Output_"+str(i+1)+".root" for i in range(0,13)],
#"Data_MET_Run2016F-23Sep2016": [path+"DATA_RUN2016F/results/Output_"+str(i+1)+".root" for i in range(0,10)], 
#"Data_MET_Run2016G-23Sep2016": [path+"DATA_RUN2016G/results/Output_"+str(i+1)+".root" for i in range(0,22)],
#"Data_MET_Run2016H2-Prompt": [path+"DATA_RUN2016H2/results/Output_"+str(i+1)+".root" for i in range(0,24)],
#"Data_MET_Run2016H3-Prompt": [path+"DATA_RUN2016H3/results/Output_"+str(i+1)+".root" for i in range(0,1)],
#Tier2
#"ZJetsToNuNu_HT-1200To2500_13TeV-madgraph": ["root://cmsxrootd.fnal.gov///store/user/gcorreia/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/LLGDV_Analysis_ZJets_HT1200To2500_Summer16/181106_011200/0000/RecoOutput_"+str(i+1)+".root" for i in range(0,56)], 
} 


#--------------------------------------------------------------------------------------------------------------------------------------------------
# Configuration
#--------------------------------------------------------------------------------------------------------------------------------------------------
selection = "CheckTTJets"

MaxJobs = 30000
ExtraVariables = 1

ApplyEventWeights = 1
TARGET_LUMI = 35918     #pb-1
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
"MET_CUT              ": 225,      # GeV
"MHT_CUT              ": 200,      # GeV
"MVA_CUT_SV_750_80    ": -0.05,  
"MVA_CUT_SV_1000_100  ": 0.29,
"Track                ": 0,        # 0 -> Linear, 1 -> Curved 
}


#--------------------------------------------------------------------------------------------------------------------------------------------------
# [DO NOT TOUCH THIS PART]
#--------------------------------------------------------------------------------------------------------------------------------------------------

if not os.path.exists(outpath+'/'+selection):
    os.makedirs(outpath+'/'+selection)
copyfile("_"+selection+".cpp", outpath+'/'+selection+"/"+"_"+selection+".cpp")

#for dataset, source in dataset.items():   
def analyze_dataset(datasetName):
    stat = "Dataset " + datasetName + " got an error."
    
    ConfigFile = "Configuration/ConfigFile_" + datasetName + ".txt"
    out = open(ConfigFile, "w")
    
    out.write("Selection            " + selection                              + "\n")
    
    out.write("Outpath              " + outpath                                + "\n")

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
    if len(dataset[datasetName]) < MaxJobs :
        for i in range(0,len(dataset[datasetName])):
            out.write("InputFile            " + dataset[datasetName][i]        + "\n")
    else:
        for i in range(0,MaxJobs):
            out.write("InputFile            " + dataset[datasetName][i]        + "\n")

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
    
    out.write("ExtraVariables       "  + str(ExtraVariables)                   + "\n")
    
    for cut, value in cuts.items():
        out.write( cut + str(value)                                            + "\n")
    out.close()
    
    runCommand = './RunAnalysis ' + ConfigFile
    os.system(runCommand)
    
    removeCommand = "rm " + ConfigFile
    os.system(removeCommand)
    
    out2 = open(outpath + "/" + selection + "/" + datasetName + "/" + "cutflow.txt", "a")
    for cut, value in cuts.items():
        out2.write( cut + str(value)  + "\n")
    out2.write("-----------------------------------------------------------------------------------")  
    out2.close()
    
    stat = "Dataset " + datasetName + " processed."
    
    with open(outpath+'/'+selection+"/"+"datasets.log", "a") as log:
        log.write( datasetName + "\n")
    
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
    CutflowFile = outpath + "/" + selection + '/' + datasetName + '/' + "cutflow.txt"
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

