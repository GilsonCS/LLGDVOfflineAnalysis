#include "LLGAnalysis.h"

namespace SignalRegions{
    //--------------------------------------------------------------------------
    // Define the output variables
    //--------------------------------------------------------------------------
    int S1;
    int S2;
    int S3;
    int S4;
}


void LLGAnalysis::SetupSignalRegions() {

    //--------------------------------------------------------------------------
    // Setup the cutflow
    //--------------------------------------------------------------------------
    _cutFlow.insert(pair<string,double>("1_Trigger", 0) );
    _cutFlow.insert(pair<string,double>("2_MET", 0) );
    _cutFlow.insert(pair<string,double>("3_MuonVeto", 0) );
    _cutFlow.insert(pair<string,double>("4_ElectronVeto", 0) );
    _cutFlow.insert(pair<string,double>("5_PVcut", 0) );
    _cutFlow.insert(pair<string,double>("6_S1", 0) );
    _cutFlow.insert(pair<string,double>("6_S2", 0) );
    _cutFlow.insert(pair<string,double>("6_S3", 0) );
    _cutFlow.insert(pair<string,double>("6_S4", 0) );


    //--------------------------------------------------------------------------
    // Setup the histograms
    //--------------------------------------------------------------------------
    //makeHist( "histogramName", 40, 0., 40., "xlabel", "ylabel" );   [example]
    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]


    //--------------------------------------------------------------------------
    // Setup the branches
    //--------------------------------------------------------------------------
    _outputTree->Branch("S1", &SignalRegions::S1 ); 
    _outputTree->Branch("S2", &SignalRegions::S2 );
    _outputTree->Branch("S3", &SignalRegions::S3 );
    _outputTree->Branch("S4", &SignalRegions::S4 );


    //--------------------------------------------------------------------------
    // Open the passedLogFile
    //--------------------------------------------------------------------------
    //_passedLogFile.open( _LogFileName.c_str(), ios::out );

    return;
}

void LLGAnalysis::SignalRegionsSelection() {

    //--------------------------------------------------------------------------
    // Write your analysis code here
    //--------------------------------------------------------------------------

    // MET plots
    double missing_energy = sqrt( met_x->at(SYSMET)*met_x->at(SYSMET) + met_y->at(SYSMET)*met_y->at(SYSMET) );
   
    bool passTrigger = false;
    for( unsigned int iTrig = 0; iTrig < triggerNames->size(); ++iTrig ) {
        if( triggerNames->at(iTrig).find("HLT_PFMET170_HBHECleaned") != std::string::npos && triggerBits->at(iTrig) == 1 ) passTrigger = true;
    }

    //--------------------------------------------------------------------------
    // 1) Trigger (MET > 170 GeV)
    //--------------------------------------------------------------------------
    if( !(passTrigger) ) return;
    _cutFlow.at("1_Trigger") += evtWeight;
    
    //--------------------------------------------------------------------------
    // 2) MET > MET_CUT
    //--------------------------------------------------------------------------
    if( !(missing_energy > MET_CUT) ) return;
    _cutFlow.at("2_MET") += evtWeight;
    
    //--------------------------------------------------------------------------
    // 3) Muons veto
    //--------------------------------------------------------------------------
    if( !(vetoMuons.size() == 0) ) return; 
    _cutFlow.at("3_MuonVeto") += evtWeight;
        
   
    //--------------------------------------------------------------------------
    // 4) Electrons veto  
    //--------------------------------------------------------------------------
    if( !(vetoElectrons.size() == 0) ) return;
    _cutFlow.at("4_ElectronVeto") += evtWeight;
    
    
    //--------------------------------------------------------------------------
    // 5) PVJetPt >= 30
    //--------------------------------------------------------------------------
    if( !( _LeadingPV >= 0) ) return;  
    _cutFlow.at("5_PVcut") += evtWeight; 
    
    
    //--------------------------------------------------------------------------
    // 6) SVJets
    //--------------------------------------------------------------------------
    SignalRegions::S1 = 0; SignalRegions::S2 = 0; SignalRegions::S3 = 0; SignalRegions::S4 = 0;
    if( _SV2Jets.size() >= 1 ){
        SignalRegions::S1 = evtWeight;
        _cutFlow.at("6_S1") += evtWeight;
    }
    if( (_SV2Jets.size() == 0) && (_SV1Jet.size() >= 2) ){
        SignalRegions::S2 = evtWeight;
        _cutFlow.at("6_S2") += evtWeight;
    }
    if( (_SV2Jets.size() == 0) && (_SV1Jet.size() == 1) ){
        SignalRegions::S3 = evtWeight;
        _cutFlow.at("6_S3") += evtWeight;
    }
    if( (_SV2Jets.size() == 0) && (_SV1Jet.size() == 0) ){
        SignalRegions::S4 = evtWeight; 
        _cutFlow.at("6_S4") += evtWeight;
    }
    

    //--------------------------------------------------------------------------
    // Fill the histograms
    //--------------------------------------------------------------------------
    //_histograms1D.at("histogram1DName").Fill( var1, evtWeight );         [Example]
    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );   [Example]

    //--------------------------------------------------------------------------
    // Apply the cut
    //--------------------------------------------------------------------------
    //if( !(CutCondition) ) return;              [Example]
    //_cutFlow.at("CutName") += evtWeight;       [Example]

    //--------------------------------------------------------------------------
    // Fill the passedLogFile
    //--------------------------------------------------------------------------
    //_passedLogFile << _EventPosition << setw(10) << RunNumber << setw(10) << LumiBlock << setw(10) << EventNumber << endl;

    //--------------------------------------------------------------------------
    // Fill the output tree
    //--------------------------------------------------------------------------
    _outputTree->Fill();

    return;
}

void LLGAnalysis::FinishSignalRegions() {

    //--------------------------------------------------------------------------
    // Make efficiency plots
    //--------------------------------------------------------------------------
    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]

    return;
}
