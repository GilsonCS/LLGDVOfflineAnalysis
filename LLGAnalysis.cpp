#include "LLGAnalysis.h"

//---------------------------------------------------------------------------------------------------------------
// LLGAnalysis
//---------------------------------------------------------------------------------------------------------------
LLGAnalysis* LLGAnalysis::GetInstance( char *configFileName ) {
    if( !_instance ) {
        _instance = new LLGAnalysis( configFileName );
    }
    return _instance;
}

LLGAnalysis *LLGAnalysis::_instance = 0;


LLGAnalysis::LLGAnalysis( char *configFileName ) {
    
    //---------------------------------------------------------------------------------------------------
    _begin = time(NULL);
    
    // Setup the default values:
    SELECTION = "SignalRegion";
    InputType = 1;
    
    requireGenBranches = false;
    GenFileName = "";
    
    datasetName = "Signal_500_60";
    metadataFileName = "Configuration/DatasetMetadata.txt";
    applyEventWeights = false;
    TARGET_LUMI = 1000.;
    
    applyPileupWeights = false;
    
    JET_PT_CUT_SV = 30;
    JET_PT_CUT_PV = 150;
    JET_ETA_CUT = 5.0;
    MUON_PT_CUT = 15.;
    ELECTRON_PT_CUT = 15.;
    MJJ_CUT = 10000;
    LEADING_SV_JET_CUT = 10000.;
    MET_CUT = 250.;
    MHT_CUT = 200.;
    MVA_CUT_SV_750_80 = 0.4;
    MVA_CUT_SV_1000_100 = 0.1;
    
    Get_Histograms = true;
    Get_Tree = true;
    Get_Histograms = true;
    Get_Histograms = true;
    Get_Histograms = true;
    
    
    //---------------------------------------------------------------------------------------------------
    PROC_XSEC = 1.;
    PROC_NTOT = 1.;
    GENLEVEL_HT_CUT = 600;
    
    PUTYPE = "True";
    applyGenHTLowerCut = false;
    applyGenHTUpperCut = false;
    
    RUNSYS = "NOMINAL";
    SYSMET = 0;
    SYSJET = 0;
    SYSPILEUP = "NOMINAL";
    
    Track = 0;
    ExtraVariables = false;

    //---------------------------------------------------------------------------------------------------

    ifstream configFile( configFileName, ios::in );
    while( configFile.good() ) {
        string key, value;
        configFile >> key >> ws >> value;
        if( configFile.eof() ) break;
        if( key == "Selection"          )   SELECTION = value;
        if( key == "Outpath"            )   _outputDirectory = value;
        if( key == "InputFile"          )   _inputFileNames.push_back( value ); 
        if( key == "InputTree"          )   _inputTreeName = value; 
        if( key == "InputType"          )   InputType = atoi(value.c_str()); 
        
        if( key == "GenFileName"        )   GenFileName = value;
        
        if( key == "DatasetName"        )   datasetName = value;
        if( key == "MetadataFileName"   )   metadataFileName = value;
        if( key == "ApplyEventWeights"  )   applyEventWeights = ( atoi(value.c_str()) == 1 );
        if( key == "TARGET_LUMI"        )   TARGET_LUMI = atof(value.c_str());
        
        if( key == "PileupFileName"     )   PUFILE = value;
        if( key == "ApplyPileupWeights" )   applyPileupWeights = ( atoi(value.c_str()) == 1 );
        if( key == "PileupType"         )   PUTYPE = value;                                          
        
        if( key == "JET_PT_CUT_SV"      )   JET_PT_CUT_SV = atof(value.c_str());
        if( key == "JET_PT_CUT_PV"      )   JET_PT_CUT_PV = atof(value.c_str());
        if( key == "SUBJET_PT_CUT_PV"   )   SUBJET_PT_CUT_PV = atof(value.c_str());
        if( key == "JET_ETA_CUT"        )   JET_ETA_CUT = atof(value.c_str());
        if( key == "MUON_PT_CUT"        )   MUON_PT_CUT = atof(value.c_str()); 
        if( key == "ELECTRON_PT_CUT"    )   ELECTRON_PT_CUT = atof(value.c_str()); 
        if( key == "MJJ_CUT"            )   MJJ_CUT = atof(value.c_str());
        if( key == "LEADING_SV_JET_CUT" )   LEADING_SV_JET_CUT = atof(value.c_str());
        if( key == "MET_CUT"            )   MET_CUT = atof(value.c_str()); 
        if( key == "MHT_CUT"            )   MHT_CUT = atof(value.c_str());
        if( key == "MVA_CUT_SV_750_80"  )   MVA_CUT_SV_750_80 = atof(value.c_str());
        if( key == "MVA_CUT_SV_1000_100")   MVA_CUT_SV_1000_100 = atof(value.c_str());
        
        if( key == "Track"              )   Track = atoi(value.c_str());
        if( key == "ExtraVariables"     )   ExtraVariables = (bool)(atoi(value.c_str()));
        
        if( key == "Get_Histograms"     )   Get_Histograms = (bool)(atoi(value.c_str()));
        if( key == "Get_Tree"           )   Get_Tree = (bool)(atoi(value.c_str()));
        if( key == "Get_Image_in_EPS"   )   Get_Image_in_EPS = (bool)(atoi(value.c_str()));
        if( key == "Get_Image_in_PNG"   )   Get_Image_in_PNG = (bool)(atoi(value.c_str()));
        if( key == "Get_Image_in_PDF"   )   Get_Image_in_PDF = (bool)(atoi(value.c_str()));
        
        if( key == "SystUncert"         )   RUNSYS = value;                                          
        if( key == "GENLEVEL_HT_CUT"    )   GENLEVEL_HT_CUT = atof(value.c_str());                              
    }
    
    if( RUNSYS == "JECUP"   ) { SYSJET = 1; SYSMET = 3; }
    if( RUNSYS == "JECDOWN" ) { SYSJET = 2; SYSMET = 4; }
    if( RUNSYS == "UNCUP"   ) { SYSMET = 11; }
    if( RUNSYS == "UNCDOWN" ) { SYSMET = 12; }
    if( RUNSYS == "PUUP"    ) { SYSPILEUP = "MBXSUP"; }
    if( RUNSYS == "PUDOWN"  ) { SYSPILEUP = "MBXSDOWN"; }

    
    //---------------------------------------------------------------------------------------------------
    if( datasetName.substr(0,6) == "Signal" ) requireGenBranches = true;
    if( datasetName == "TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"               ) applyGenHTUpperCut = true;
    if( datasetName == "TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"   ) applyGenHTLowerCut = true;
    if( datasetName == "TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"  ) applyGenHTLowerCut = true;
    if( datasetName == "TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8" ) applyGenHTLowerCut = true;
    if( datasetName == "TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"  ) applyGenHTLowerCut = true;
    
    
    //---------------------------------------------------------------------------------------------------    
    
    _outputDirectory = _outputDirectory + "/" + SELECTION + "/" + datasetName + "/";
    mkdir(_outputDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    
    //---------------------------------------------------------------------------------------------------
    int pos = _inputFileNames.at(0).find("results");
    string path = _inputFileNames.at(0).substr(0,pos+7);
    cout << endl;
    cout << endl;
    cout << "===================================================================================" << endl;
    cout << "RUNNING SELECTION " << SELECTION << " ON " << datasetName << endl; 
    cout << "===================================================================================" << endl;
    //cout << "Input files:" << endl;
    //for( unsigned int i=0; i < _inputFileNames.size(); ++i ){
    //    cout << _inputFileNames.at(i) << endl;
    //}
    cout << "Ntuples path:" << endl;
    cout << path << endl;
    cout << "Number of files = " << _inputFileNames.size() << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << endl;
    
    
    _CutflowFileName = _outputDirectory + "cutflow.txt";
    _CutflowFile.open( _CutflowFileName.c_str(), ios::out );
    
    _CutflowFile << "===========================================================================================" << endl;
    _CutflowFile << "RUNNING SELECTION " << SELECTION << " ON " << datasetName << endl; 
    _CutflowFile << "===========================================================================================" << endl;
    //_CutflowFile << "Input files:" << endl;
    //for( unsigned int i=0; i < _inputFileNames.size(); ++i ){
    //    _CutflowFile << _inputFileNames.at(i) << endl;
    //}
    _CutflowFile << "Ntuples path:" << endl;
    _CutflowFile << path << endl;
    _CutflowFile << "Number of files = " << _inputFileNames.size() << endl;
   
    //---------------------------------------------------------------------------------------------------
    _LogFileName = _outputDirectory + "passedEvents.txt";
    
    
    //---------------------------------------------------------------------------------------------------
    // generate the pileup reweighting histogram 
    if( applyPileupWeights ) {
      
      string mcHistogramName   = "Distribution_" + PUTYPE + "_" + datasetName;
      string dataHistogramName = "Distribution_Data_" + PUTYPE + "_" + SYSPILEUP;
      TFile *fPU = new TFile( PUFILE.c_str(), "OPEN" );
      if( !fPU || fPU->IsZombie() ) {
        cout << "FATAL: COULDN'T OPEN PILEUPFILE: " << PUFILE << endl;
        exit(-1);
      }

      
      TH1D *hdata = (TH1D*)fPU->Get(dataHistogramName.c_str());
      TH1D *hmc = (TH1D*)fPU->Get(mcHistogramName.c_str());
      if( !hdata || !hmc ) {
        std::cout << "FATAL: COULDN'T LOAD HISTOGRAM(S): Distribution_Data or " << mcHistogramName << std::endl;
      }
      hdata->Scale( 1./hdata->Integral() );
      hmc->Scale( 1./hmc->Integral() );
      hPU_weights = new TH1D("PileupWeights", "PileupWeights", hdata->GetXaxis()->GetNbins(), hdata->GetXaxis()->GetBinLowEdge(1), hdata->GetXaxis()->GetBinLowEdge( hdata->GetXaxis()->GetNbins() + 1) );
      for( int iBin = 1; iBin <= hdata->GetXaxis()->GetNbins(); ++iBin ) {
        hPU_weights->SetBinContent( iBin, hdata->GetBinContent(iBin) / hmc->GetBinContent(iBin) );
      }

    }

    //---------------------------------------------------------------------------------------------------
    _inputTree = new TChain(_inputTreeName.c_str());
    _metaTree = new TChain("MetaData");
    for( vector<string>::iterator itr = _inputFileNames.begin(); itr != _inputFileNames.end(); ++itr ) {
        _inputTree -> Add( (*itr).c_str() ); 
        _metaTree -> Add( (*itr).c_str() );
    }
    
    //---------------------------------------------------------------------------------------------------
    // Metadata
    //---------------------------------------------------------------------------------------------------
    _metaTree->SetBranchAddress("SumOfWeights", &_SumOfWeights );
    double nEffEventsProcessed=0;
    for( int i = 0; i < _metaTree -> GetEntries(); ++i ) {
        _metaTree->GetEntry(i);
        nEffEventsProcessed += _SumOfWeights;
    }
    PROC_NTOT = nEffEventsProcessed;
    
    bool foundMetadata = false;
    ifstream metadataFile( metadataFileName.c_str(), ios::in );
    while( metadataFile.good() ) {
      string name, xs, xs_unc, Nevt;
      metadataFile >> name >> ws >> xs >> ws >> xs_unc >> ws >> Nevt;
      //cout << name << " " << xs << " " << xs_unc << " " << Nevt << endl;
      if( metadataFile.eof() ) break;
      if( name == datasetName ) {
        PROC_XSEC = atof( xs.c_str() );
        foundMetadata = true;
        break;
      }
    }
    if( !foundMetadata ) {
      cout << "Did not find dataset " << datasetName << " in " << metadataFileName << ". Using standard values for xsec and ntot: " << PROC_XSEC << endl;
    }
    generatorWeight = 1.;
    lumiWeight = applyEventWeights ? PROC_XSEC/PROC_NTOT * TARGET_LUMI : 1.;
    
    
    //---------------------------------------------------------------------------------------------------
    if( Get_Tree ) {
        _outputFileName = _outputDirectory + "Tree.root";
        _outputFile = new TFile( _outputFileName.c_str(), "RECREATE" );
        _outputTree = new TTree( _inputTreeName.c_str(), _inputTreeName.c_str() );
    }
    
    
}


//---------------------------------------------------------------------------------------------------------------
// Init
//---------------------------------------------------------------------------------------------------------------
bool LLGAnalysis::Init() {
   
    //---------------------------------------------------------------------------------------------------
    //gROOT->ProcessLine(".L Loader.C+");
    //gROOT->ProcessLine("#include <vector>");
    //gSystem->Load("Loader_C.so");
    
    //---------------------------------------------------------------------------------------------------
    // set the style
    setStyle(1.0,true,0.15);
    
    
    //---------------------------------------------------------------------------------------------------
    // allocate memory for the input variables
    //---------------------------------------------------------------------------------------------------
    
    //---------------------------------------------------------------------------------------------------
    // InputType 1 and 2
    vertex_x = new vector<double>;
    vertex_y = new vector<double>;
    vertex_z = new vector<double>;
    vertex_ndof = new vector<double>;
    
    vertex_dx = new vector<double>;
    vertex_dy = new vector<double>;
    vertex_dz = new vector<double>;
    vertex_nTracks = new vector<double>;
    vertex_pt = new vector<double>;
    secVertex_x = new vector<double>;
    secVertex_y = new vector<double>;
    secVertex_z = new vector<double>;
    secVertex_ndof = new vector<double>;
    secVertex_chi2 = new vector<double>;
    secVertex_pt = new vector<double>;
    secVertex_dx = new vector<double>;
    secVertex_dy = new vector<double>;
    secVertex_dz = new vector<double>;
    
    //---------------------------------------------------------------------------------------------------
    // InputType 1
    
    if( InputType == 1 ) {
        recoJet_eta = new vector<double>;
        recoJet_phi = new vector<double>;
        recoJet_pt = new vector<vector<double> >;
        recoJet_vertex_x = new vector<double>;
        recoJet_vertex_y = new vector<double>;
        recoJet_vertex_z = new vector<double>;
        recoJet_C_vertex_x = new vector<double>;
        recoJet_C_vertex_y = new vector<double>;
        recoJet_C_vertex_z = new vector<double>;
        recoJet_vertex_score = new vector<vector<double> >;
        recoJet_nConsidered = new vector<int>;
        recoJet_averageDistance = new vector<vector<double> >;
        recoJet_rmsDistance = new vector<vector<double> >;
    
        recoJet_btag_CombinedMVAV2BJetTags = new vector<double>;
        recoJet_btag_CombinedCvsLJetTags = new vector<double>;
        recoJet_btag_CombinedCvsBJetTags = new vector<double>;
        recoJet_btag_combinedInclusiveSecondaryVertexV2BJetTags = new vector<double>;
    
        muon_px = new vector<double>;
        muon_py = new vector<double>;
        muon_pz = new vector<double>;
    
        muon_eta = new vector<double>;
        muon_phi = new vector<double>;
        muon_iso = new vector<double>;
        muon_isTightMuon = new vector<bool>;
    
        muon_isLooseMuon = new vector<bool>;
    
        electron_px = new vector<double>;
        electron_py = new vector<double>;
        electron_pz = new vector<double>;
    
        electron_eta = new vector<double>;
        electron_phi = new vector<double>;
        electron_iso = new vector<double>;
    
        electron_isVeto = new vector<bool>;
        electron_isLoose = new vector<bool>;
        electron_isMedium = new vector<bool>;
        electron_isTight = new vector<bool>;
        electron_isHEEP = new vector<bool>;
    
        triggerBits = new vector<int>;
        triggerNames = new vector<string>;
   
        to_TriggerNames = new vector<string>;
        to_pt = new vector<vector<double> >;
        to_eta = new vector<vector<double> >;
        to_phi = new vector<vector<double> >;
        met = new vector<double>;
        met_x = new vector<double>;
        met_y = new vector<double>;
    }
    
    /* 
    recoJet_constVertex_x = new vector<vector<double> >;
    recoJet_constVertex_y = new vector<vector<double> >;
    recoJet_constVertex_z = new vector<vector<double> >;
    recoJet_const_pt = new vector<vector<double> >;
    recoJet_const_closestVertex_dxy = new vector<vector<double> >;
    recoJet_const_closestVertex_dz = new vector<vector<double> >;
    recoJet_const_closestVertex_d = new vector<vector<double> >;
    recoJet_const_charge = new vector<vector<int> >;
    */
    
    //---------------------------------------------------------------------------------------------------
    // InputType 2
    
    if( InputType == 2 ) {
        recoCHSJet_eta = new vector<double>;
        recoCHSJet_phi = new vector<double>;
        recoCHSJet_pt = new vector<double>;
        recoCHSJet_constVertex_x = new vector<vector<double> >;
        recoCHSJet_constVertex_y = new vector<vector<double> >;
        recoCHSJet_constVertex_z = new vector<vector<double> >;
        recoCHSJet_constVertexRef_x = new vector<vector<double> >;
        recoCHSJet_constVertexRef_y = new vector<vector<double> >;
        recoCHSJet_constVertexRef_z = new vector<vector<double> >;
        recoCHSJet_const_pt      = new vector<vector<double> >;
        recoCHSJet_const_charge  = new vector<vector<int> >;
        recoCHSJet_const_fromPV  = new vector<vector<int> >;
        recoCHSJet_const_pca0_x = new vector<vector<double> >;
        recoCHSJet_const_pca0_y = new vector<vector<double> >;
        recoCHSJet_const_pca0_z = new vector<vector<double> >;
        recoCHSJet_const_closestVertex_dxy = new vector<vector<double> >;
        recoCHSJet_const_closestVertex_dz = new vector<vector<double> >;
        recoCHSJet_const_closestVertex_d = new vector<vector<double> >;
        recoCHSJet_const_eta     = new vector<vector<double> >;
        recoCHSJet_const_phi     = new vector<vector<double> >;
        recoCHSJet_const_mass     = new vector<vector<double> >;
   
        recoNoCHSJet_eta = new vector<double>;
        recoNoCHSJet_phi = new vector<double>;
        recoNoCHSJet_pt = new vector<double>;
        recoNoCHSJet_constVertex_x = new vector<vector<double> >;
        recoNoCHSJet_constVertex_y = new vector<vector<double> >;
        recoNoCHSJet_constVertex_z = new vector<vector<double> >;
        recoNoCHSJet_constVertexRef_x = new vector<vector<double> >;
        recoNoCHSJet_constVertexRef_y = new vector<vector<double> >;
        recoNoCHSJet_constVertexRef_z = new vector<vector<double> >;
        recoNoCHSJet_const_pt      = new vector<vector<double> >;
        recoNoCHSJet_const_charge  = new vector<vector<int> >;
        recoNoCHSJet_const_fromPV  = new vector<vector<int> >;
        recoNoCHSJet_const_pca0_x = new vector<vector<double> >;
        recoNoCHSJet_const_pca0_y = new vector<vector<double> >;
        recoNoCHSJet_const_pca0_z = new vector<vector<double> >;
        recoNoCHSJet_const_closestVertex_dxy = new vector<vector<double> >;
        recoNoCHSJet_const_closestVertex_dz = new vector<vector<double> >;
        recoNoCHSJet_const_closestVertex_d = new vector<vector<double> >;
        recoNoCHSJet_const_eta     = new vector<vector<double> >;
        recoNoCHSJet_const_phi     = new vector<vector<double> >;
        recoNoCHSJet_const_mass     = new vector<vector<double> >;
    
        
    }
    
    
    // variables for mc truth analysis
    if( requireGenBranches ) {
        tmct_px = new vector<double>;
        tmct_py = new vector<double>;
        tmct_pz = new vector<double>;
        tmct_vx = new vector<double>;
        tmct_vy = new vector<double>;
        tmct_vz = new vector<double>;
        tmct_e = new vector<double>;
        tmct_id = new vector<int>;
        tmct_status = new vector<int>;
        tmct_parent = new vector<int>;
        tmct_daughters = new vector<vector<int> >;
    }
    
    
    //---------------------------------------------------------------------------------------------------------------
    // and set the branch addresses
    //---------------------------------------------------------------------------------------------------------------
    
    //---------------------------------------------------------------------------------------------------------------
    // InputType 1 and 2
    
    _inputTree->SetBranchAddress("RunNumber", &RunNumber );
    _inputTree->SetBranchAddress("EventNumber", &EventNumber );
    _inputTree->SetBranchAddress("LuminosityBlock", &LumiBlock );
    _inputTree->SetBranchAddress("GeneratorWeight", &generatorWeight );
    
    //_inputTree->SetBranchAddress("Beam_x", &beam_x );
    //_inputTree->SetBranchAddress("Beam_y", &beam_y );
    
    _inputTree->SetBranchAddress("RecoVertex_x", &vertex_x );
    _inputTree->SetBranchAddress("RecoVertex_y", &vertex_y );
    _inputTree->SetBranchAddress("RecoVertex_z", &vertex_z );
    _inputTree->SetBranchAddress("RecoVertex_ndof", &vertex_ndof );
    _inputTree->SetBranchAddress("RecoVertex_chi2", &vertex_chi2 );
    _inputTree->SetBranchAddress("RecoVertex_xError", &vertex_dx );
    _inputTree->SetBranchAddress("RecoVertex_yError", &vertex_dy );
    _inputTree->SetBranchAddress("RecoVertex_zError", &vertex_dz );
    _inputTree->SetBranchAddress("RecoVertex_nTracks", &vertex_nTracks );
    _inputTree->SetBranchAddress("RecoVertex_pt", &vertex_pt );
    _inputTree->SetBranchAddress("RecoSecVertex_x", &secVertex_x );
    _inputTree->SetBranchAddress("RecoSecVertex_y", &secVertex_y );
    _inputTree->SetBranchAddress("RecoSecVertex_z", &secVertex_z );
    _inputTree->SetBranchAddress("RecoSecVertex_ndof", &secVertex_ndof );
    _inputTree->SetBranchAddress("RecoSecVertex_chi2", &secVertex_chi2 );
    //_inputTree->SetBranchAddress("RecoSecVertex_nTracks", &secVertex_nTracks );
    _inputTree->SetBranchAddress("RecoSecVertex_pt", &secVertex_pt );
    _inputTree->SetBranchAddress("RecoSecVertex_xError", &secVertex_dx );
    _inputTree->SetBranchAddress("RecoSecVertex_yError", &secVertex_dy );
    _inputTree->SetBranchAddress("RecoSecVertex_zError", &secVertex_dz );
    
    //---------------------------------------------------------------------------------------------------------------
    // InputType 1
    
    if( InputType == 1 ) {    
        _inputTree->SetBranchAddress("RecoJet_eta", &recoJet_eta );
        _inputTree->SetBranchAddress("RecoJet_phi", &recoJet_phi );
        _inputTree->SetBranchAddress("RecoJet_pt", &recoJet_pt );
        _inputTree->SetBranchAddress("RecoJet_Vertex_x", &recoJet_vertex_x );
        _inputTree->SetBranchAddress("RecoJet_Vertex_y", &recoJet_vertex_y );
        _inputTree->SetBranchAddress("RecoJet_Vertex_z", &recoJet_vertex_z );
        _inputTree->SetBranchAddress("RecoJet_C_Vertex_x", &recoJet_C_vertex_x );
        _inputTree->SetBranchAddress("RecoJet_C_Vertex_y", &recoJet_C_vertex_y );
        _inputTree->SetBranchAddress("RecoJet_C_Vertex_z", &recoJet_C_vertex_z );
        _inputTree->SetBranchAddress("RecoJet_Vertex_Score", &recoJet_vertex_score );
        _inputTree->SetBranchAddress("RecoJet_nConsidered", &recoJet_nConsidered );
        _inputTree->SetBranchAddress("RecoJet_AverageDistanceToVertex", &recoJet_averageDistance );
        _inputTree->SetBranchAddress("RecoJet_RMSDistanceToVertex", &recoJet_rmsDistance );
        _inputTree->SetBranchAddress("TightJet_eta", &tightJet_eta );
        _inputTree->SetBranchAddress("TightJet_phi", &tightJet_phi );
        _inputTree->SetBranchAddress("TightJet_pt", &tightJet_pt );
  
        _inputTree->SetBranchAddress("RecoJet_btag_pfCombinedMVAV2BJetTags", &recoJet_btag_CombinedMVAV2BJetTags );
        _inputTree->SetBranchAddress("RecoJet_btag_pfCombinedCvsLJetTags", &recoJet_btag_CombinedCvsLJetTags );
        _inputTree->SetBranchAddress("RecoJet_btag_pfCombinedCvsBJetTags", &recoJet_btag_CombinedCvsBJetTags );
        _inputTree->SetBranchAddress("RecoJet_btag_pfCombinedInclusiveSecondaryVertexV2BJetTags", &recoJet_btag_combinedInclusiveSecondaryVertexV2BJetTags );
        _inputTree->SetBranchAddress("PUINFO_NumberOfTrueInteractions", &NumberOfTrueInteractions );
        _inputTree->SetBranchAddress("PUINFO_NumberOfObservedInteractions", &NumberOfObservedInteractions );
        _inputTree->SetBranchAddress("GenLevel_HT", &genLevel_HT );
        _inputTree->SetBranchAddress("RecoMuon_px", &muon_px );
        _inputTree->SetBranchAddress("RecoMuon_py", &muon_py );
        _inputTree->SetBranchAddress("RecoMuon_pz", &muon_pz );
    
        _inputTree->SetBranchAddress("RecoMuon_eta", &muon_eta );
        _inputTree->SetBranchAddress("RecoMuon_phi", &muon_phi );
        _inputTree->SetBranchAddress("RecoMuon_iso", &muon_iso );
        _inputTree->SetBranchAddress("RecoMuon_isTightMuon", &muon_isTightMuon );
    
        _inputTree->SetBranchAddress("RecoMuon_isLooseMuon", &muon_isLooseMuon );
    
        _inputTree->SetBranchAddress("RecoElectron_px", &electron_px );
        _inputTree->SetBranchAddress("RecoElectron_py", &electron_py );
        _inputTree->SetBranchAddress("RecoElectron_pz", &electron_pz );
    
        _inputTree->SetBranchAddress("RecoElectron_eta", &electron_eta );
        _inputTree->SetBranchAddress("RecoElectron_phi", &electron_phi );
        _inputTree->SetBranchAddress("RecoElectron_iso", &electron_iso );
    
        _inputTree->SetBranchAddress("RecoElectron_isVeto", &electron_isVeto );
        _inputTree->SetBranchAddress("RecoElectron_isLoose", &electron_isLoose );
        _inputTree->SetBranchAddress("RecoElectron_isMedium", &electron_isMedium );
        _inputTree->SetBranchAddress("RecoElectron_isTight", &electron_isTight );
        _inputTree->SetBranchAddress("RecoElectron_isHEEP", &electron_isHEEP );
    
        _inputTree->SetBranchAddress("TriggerBits", &triggerBits );
        _inputTree->SetBranchAddress("TriggerNames", &triggerNames );
    
        _inputTree->SetBranchAddress("TriggerObject_TriggerName", &to_TriggerNames );
        _inputTree->SetBranchAddress("TriggerObject_pt", &to_pt );
        _inputTree->SetBranchAddress("TriggerObject_eta", &to_eta );
        _inputTree->SetBranchAddress("TriggerObject_phi", &to_phi );
        _inputTree->SetBranchAddress("MET", &met );
        _inputTree->SetBranchAddress("MET_x", &met_x );
        _inputTree->SetBranchAddress("MET_y", &met_y );
    }
    
    //---------------------------------------------------------------------------------------------------------------
    // InputType 2
    
    if( InputType == 2 ) {
        _inputTree->SetBranchAddress("RecoCHSJet_eta", &recoCHSJet_eta );
        _inputTree->SetBranchAddress("RecoCHSJet_phi", &recoCHSJet_phi );
        _inputTree->SetBranchAddress("RecoCHSJet_pt", &recoCHSJet_pt );
        _inputTree->SetBranchAddress("RecoCHSJet_constVertex_x", &recoCHSJet_constVertex_x );
        _inputTree->SetBranchAddress("RecoCHSJet_constVertex_y", &recoCHSJet_constVertex_y );
        _inputTree->SetBranchAddress("RecoCHSJet_constVertex_z", &recoCHSJet_constVertex_z );
        _inputTree->SetBranchAddress("RecoCHSJet_constVertexRef_x", &recoCHSJet_constVertexRef_x );
        _inputTree->SetBranchAddress("RecoCHSJet_constVertexRef_y", &recoCHSJet_constVertexRef_y );
        _inputTree->SetBranchAddress("RecoCHSJet_constVertexRef_z", &recoCHSJet_constVertexRef_z );
        _inputTree->SetBranchAddress("RecoCHSJet_const_pt", &recoCHSJet_const_pt );
        _inputTree->SetBranchAddress("RecoCHSJet_const_charge", &recoCHSJet_const_charge );
        _inputTree->SetBranchAddress("RecoCHSJet_const_fromPV", &recoCHSJet_const_fromPV );
        _inputTree->SetBranchAddress("RecoCHSJet_const_pca0_x", &recoCHSJet_const_pca0_x );
        _inputTree->SetBranchAddress("RecoCHSJet_const_pca0_y", &recoCHSJet_const_pca0_y );
        _inputTree->SetBranchAddress("RecoCHSJet_const_pca0_z", &recoCHSJet_const_pca0_z );
        _inputTree->SetBranchAddress("RecoCHSJet_const_closestVertex_dxy", &recoCHSJet_const_closestVertex_dxy );
        _inputTree->SetBranchAddress("RecoCHSJet_const_closestVertex_dz", &recoCHSJet_const_closestVertex_dz );
        _inputTree->SetBranchAddress("RecoCHSJet_const_closestVertex_d", &recoCHSJet_const_closestVertex_d );
        _inputTree->SetBranchAddress("RecoCHSJet_const_eta", &recoCHSJet_const_eta );
        _inputTree->SetBranchAddress("RecoCHSJet_const_phi", &recoCHSJet_const_phi ); 
        _inputTree->SetBranchAddress("RecoCHSJet_const_mass", &recoCHSJet_const_mass );

        _inputTree->SetBranchAddress("RecoNoCHSJet_eta", &recoNoCHSJet_eta );
        _inputTree->SetBranchAddress("RecoNoCHSJet_phi", &recoNoCHSJet_phi );
        _inputTree->SetBranchAddress("RecoNoCHSJet_pt", &recoNoCHSJet_pt );
        _inputTree->SetBranchAddress("RecoNoCHSJet_constVertex_x", &recoNoCHSJet_constVertex_x );
        _inputTree->SetBranchAddress("RecoNoCHSJet_constVertex_y", &recoNoCHSJet_constVertex_y );
        _inputTree->SetBranchAddress("RecoNoCHSJet_constVertex_z", &recoNoCHSJet_constVertex_z );
        _inputTree->SetBranchAddress("RecoNoCHSJet_constVertexRef_x", &recoNoCHSJet_constVertexRef_x );
        _inputTree->SetBranchAddress("RecoNoCHSJet_constVertexRef_y", &recoNoCHSJet_constVertexRef_y );
        _inputTree->SetBranchAddress("RecoNoCHSJet_constVertexRef_z", &recoNoCHSJet_constVertexRef_z );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_pt", &recoNoCHSJet_const_pt );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_charge", &recoNoCHSJet_const_charge );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_fromPV", &recoNoCHSJet_const_fromPV );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_pca0_x", &recoNoCHSJet_const_pca0_x );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_pca0_y", &recoNoCHSJet_const_pca0_y );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_pca0_z", &recoNoCHSJet_const_pca0_z );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_closestVertex_dxy", &recoNoCHSJet_const_closestVertex_dxy );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_closestVertex_dz", &recoNoCHSJet_const_closestVertex_dz );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_closestVertex_d", &recoNoCHSJet_const_closestVertex_d );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_eta", &recoNoCHSJet_const_eta );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_phi", &recoNoCHSJet_const_phi );
        _inputTree->SetBranchAddress("RecoNoCHSJet_const_mass", &recoNoCHSJet_const_mass );
    }
    
    if( requireGenBranches ) {
        cout << "Setting tmct branch addresses" << endl;
        /*
        _inputTree->SetBranchAddress("GenLevel_px", &tmct_px );
        _inputTree->SetBranchAddress("GenLevel_py", &tmct_py );
        _inputTree->SetBranchAddress("GenLevel_pz", &tmct_pz );
        _inputTree->SetBranchAddress("GenLevel_vx", &tmct_vx );
        _inputTree->SetBranchAddress("GenLevel_vy", &tmct_vy );
        _inputTree->SetBranchAddress("GenLevel_vz", &tmct_vz );
        _inputTree->SetBranchAddress("GenLevel_E", &tmct_e );
        _inputTree->SetBranchAddress("GenLevel_PDGID", &tmct_id );
        _inputTree->SetBranchAddress("GenLevel_status", &tmct_status );
        _inputTree->SetBranchAddress("GenLevel_ParentId", &tmct_parent );
        _inputTree->SetBranchAddress("GenLevel_DaughterId", &tmct_daughters );
        */
    }
    
  
    return true;
}


//---------------------------------------------------------------------------------------------------------------
// RunEventLoop
//---------------------------------------------------------------------------------------------------------------
void LLGAnalysis::RunEventLoop( int ControlEntries ) {
  
    //---------------------------------------------------------------------------------------------------
    //cout << "Running event loop for selection " << SELECTION << endl;
    if( ControlEntries < 0 ) _NumberEntries = _inputTree -> GetEntries();
    //cout << "Will process " << _NumberEntries << " events" << endl;
    
    //---------------------------------------------------------------------------------------------------
    if( false );
    // SETUP YOUR SELECTION HERE
    else {
      cout << "Unknown selection requested. Exiting. " << endl;
      return;
    }
    
    NumberOfEvents = 0;
    vector<double> cutflowOld(50, 0.);
    for( int icut = 0; icut < 50; ++icut ){
        StatisticalError.push_back(0);
    }
    
    int itime = 0;
    int hoursEstimated = 0;
    int minutesEstimated = 0;
    time_t timeOld;
    timeOld = time(NULL);
    //---------------------------------------------------------------------------------------------------
    for( int i = 0; i < _NumberEntries; ++i ) {
    //for( int i = 0; i < 100000; ++i ) { 
        _EventPosition = i;
            
        if( (i+1)/10000 != itime ){
            int timeEstimated = (_NumberEntries-i)*difftime(time(NULL),timeOld)/10000.;
            hoursEstimated = timeEstimated/3600;
            minutesEstimated = (timeEstimated%3600)/60;
            ++itime;
            timeOld = time(NULL);
        }
        
        
        cout << "NOW RUNNING EVENT " << setw(8) << i << " | TIME TO FINISH: " << setw(2) << hoursEstimated << " hours " << setw(2) << minutesEstimated << " minutes." << "\r"; fflush(stdout);
        //cout << "NOW RUNNING EVENT " << i << endl;
        //cout << "====================" << endl;
    
        _inputTree->GetEntry(i);
        
        //---------------------------------------------------------------------------------------------------
        //if( applyGenHTLowerCut && genLevel_HT <= 1400 ) continue;
        //if( applyGenHTUpperCut && genLevel_HT > 1400 ) continue;

        //---------------------------------------------------------------------------------------------------
        // handle the weights
        evtWeight = lumiWeight;
        //cout << evtWeight << endl;
        evtWeight *= generatorWeight*1.0L;
        //cout << setprecision(25) << evtWeight << endl;
        pileupWeight = 1.; 
        
        if( applyPileupWeights ) {
          int bin = hPU_weights->GetXaxis()->FindBin( NumberOfTrueInteractions );
          pileupWeight = hPU_weights->GetBinContent( bin );
        }
        evtWeight *= pileupWeight;
        //cout << evtWeight << endl;
        NumberOfEvents += evtWeight;
        
        //---------------------------------------------------------------------------------------------------
        if( InputType == 1 ) {
            RunObjectID(); 
        }
        
        
        
        
        //---------------------------------------------------------------------------------------------------
        // CALL YOUR SELECTION HERE
        
        //cout << "Eu posso te ver  " << endl;
        //cout << "MET = " << sqrt( met_x->at(SYSMET)*met_x->at(SYSMET) + met_y->at(SYSMET)*met_y->at(SYSMET) ) << endl;
        //cout << "met = " << met->at(SYSMET) << endl;
        //cout << "HT = " << genLevel_HT << endl;
        //cout << "evtWeight = " << evtWeight << endl;
        //cout << " " << endl;
        //---------------------------------------------------------------------------------------------------
        int icut = 0;
        for ( map<string,double>::iterator it = _cutFlow.begin(); it != _cutFlow.end(); ++it ){
            if( cutflowOld.at(icut) != it->second ){
                StatisticalError.at(icut) += evtWeight*evtWeight;
                cutflowOld.at(icut) = it->second;
            }
            ++icut;
        }
        
            
    }
    //---------------------------------------------------------------------------------------------------
    int icut = 0;
    for ( map<string,double>::iterator it = _cutFlow.begin(); it != _cutFlow.end(); ++it ){
        StatisticalError.at(icut) = sqrt(StatisticalError.at(icut));
        ++icut;
    }
    
    
    return;

} 


//---------------------------------------------------------------------------------------------------------------
// FinishRun
//---------------------------------------------------------------------------------------------------------------
void LLGAnalysis::FinishRun() {
    
    gErrorIgnoreLevel = kWarning;
    //---------------------------------------------------------------------------------------------------
    // crate eps, png and pdf in the end
    if( Get_Image_in_EPS ) _plotFormats.push_back(".eps");
    if( Get_Image_in_PNG ) _plotFormats.push_back(".png");
    if( Get_Image_in_PDF ) _plotFormats.push_back(".pdf");
      
    //---------------------------------------------------------------------------------------------------
    TCanvas c("","");
    for( map<string,TH1D>::iterator itr_h = _histograms1D.begin(); itr_h != _histograms1D.end(); ++itr_h ) {
        (*itr_h).second.Draw( (_histograms1DDrawOptions.at((*itr_h).first)).c_str() );
        for( vector<string>::iterator itr_f = _plotFormats.begin(); itr_f != _plotFormats.end(); ++itr_f ) {
            string thisPlotName = _outputDirectory + (*itr_h).first + (*itr_f);
            c.Print( thisPlotName.c_str() );
        }
    }
    
    for( map<string,TH2D>::iterator itr_h = _histograms2D.begin(); itr_h != _histograms2D.end(); ++itr_h ) {
        (*itr_h).second.Draw( (_histograms2DDrawOptions.at((*itr_h).first)).c_str()  );
        if( (*itr_h).first.find( "SV2Jets") != string::npos && (*itr_h).first.find("VertexScore") != string::npos ) {
          c.SetLogx(1);
          c.SetLogy(1);
        }
        if( (*itr_h).first == "HT" ) {
          c.SetLogz(1);
        }
        if( (*itr_h).first == "NJets" ) {
          c.SetLogz(1);
        }
        for( vector<string>::iterator itr_f = _plotFormats.begin(); itr_f != _plotFormats.end(); ++itr_f ) {
            string thisPlotName = _outputDirectory + (*itr_h).first + (*itr_f);
            c.Print( thisPlotName.c_str() );
        }
        c.SetLogx(0);
        c.SetLogy(0);
        c.SetLogz(0);
    }
    
    
    //---------------------------------------------------------------------------------------------------
    
    
    for( map<string,TH1D>::iterator itr_h = _histograms1D.begin(); itr_h != _histograms1D.end(); ++itr_h ) {
        (*itr_h).second.Sumw2();
    }
        
    //---------------------------------------------------------------------------------------------------
    // FINISH YOUR SELECTION HERE
    
    
    //---------------------------------------------------------------------------------------------------
    /* 
    MakeEfficiencyPlot( _histograms1D.at("MET_HLT_PFMET170_NoiseCleaned_v1"), _histograms1D.at("MET_allEvents"), &c, "HLT_PFMET170_NoiseCleaned_v1" ); 
    MakeEfficiencyPlot( _histograms1D.at("jet1_pt_HLT_PFJet260_v1"), _histograms1D.at("jet1_pt_allEvents"), &c, "HLT_PFJet260_v1" ); 
    */
    
     
    //---------------------------------------------------------------------------------------------------
    //cout << "-----------------------------------------------------------------------------------" << endl;
    double luminosity = applyEventWeights ? TARGET_LUMI : PROC_NTOT/PROC_XSEC;
    //cout << "Luminosity: " << luminosity << " pb-¹" << endl;
    string pileupState = applyPileupWeights ? "ON" : "OFF";
    /*
    cout << "Pileup Weights: " << pileupState << endl;
    cout << "Luminosity Weight: " << lumiWeight << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Effective number of events in the Ntuple: " << setprecision(16) << NumberOfEvents << endl;
    cout << "Effective number of events generated: " << setprecision(16) << PROC_NTOT*lumiWeight << endl;
    cout << "Triggers Acceptance: " << setprecision(6) << 100*NumberOfEvents/(PROC_NTOT*lumiWeight) << " %" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout.width(20); cout << left << "Cutflow" << " " << setw(20) << setprecision(16) << "Selected Events"
    << " " << setw(20) << setprecision(12) << "Stat. Error" << setw(15) << setprecision(6) << "Efficiency (%)" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    */
    int icut = 0;
    /*
    for( map<string,double>::iterator itr = _cutFlow.begin(); itr != _cutFlow.end(); ++itr ) {
        cout.width(20); cout << left << (*itr).first << " " << setw(20) << setprecision(16) << (*itr).second 
        << " " << setw(20) << setprecision(12) << StatisticalError.at(icut) 
        << setw(15) << setprecision(6) << (*itr).second*100./(PROC_NTOT*lumiWeight) << endl;
        ++icut;
    }
    */
   
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    _CutflowFile << "Luminosity: " << luminosity << " pb-¹" << endl;
    _CutflowFile << "Luminosity Weight: " << lumiWeight << endl;
    _CutflowFile << "Pileup Weights: " << pileupState << endl;
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    _CutflowFile << "Number of events in the Ntuple: " << setprecision(12) << _NumberEntries << endl;
    //_CutflowFile << "Effective number of events in the Ntuple: " << setprecision(16) << NumberOfEvents << endl;
    _CutflowFile << "Effective number of events generated: " << setprecision(16) << PROC_NTOT*lumiWeight << endl;
    //_CutflowFile << "Triggers Acceptance: " << setprecision(6) << 100*NumberOfEvents/(PROC_NTOT*lumiWeight) << " %" << endl;
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    _CutflowFile.width(20); _CutflowFile << left << " Cutflow" << " " << setw(20) << setprecision(16) << "Selected Events"
    << " " << setw(20) << setprecision(12) << "Stat. Error" << setw(15) << setprecision(6) << "Efficiency (%)" << endl;
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    icut = 0;
    for( map<string,double>::iterator itr = _cutFlow.begin(); itr != _cutFlow.end(); ++itr ) {
        _CutflowFile.width(20); _CutflowFile << left << "|" + (*itr).first << " " << setw(20) << setprecision(16) << (*itr).second 
        << " " << setw(20) << setprecision(12) << StatisticalError.at(icut) 
        << setw(15) << setprecision(6) << (*itr).second*100./(PROC_NTOT*lumiWeight) << endl;
        ++icut;
    }
 
    
    //---------------------------------------------------------------------------------------------------
    if( Get_Histograms ) {
        string HistogramsFileName = _outputDirectory + "Histograms.root";
        TFile *fHistOutput = new TFile( HistogramsFileName.c_str(), "RECREATE" );
        for( map<string,TH1D>::iterator itr_h = _histograms1D.begin(); itr_h != _histograms1D.end(); ++itr_h ) {
            (*itr_h).second.Write();
        }
        for( map<string,TH2D>::iterator itr_h = _histograms2D.begin(); itr_h != _histograms2D.end(); ++itr_h ) {
            (*itr_h).second.Write();
        }
        fHistOutput->Close();
    }
    
    
    //---------------------------------------------------------------------------------------------------
    if( Get_Tree ) {
        _outputFile->cd();
        _outputTree->Write();
        _outputFile->Close();
    }
    
    //---------------------------------------------------------------------------------------------------
    _end = time(NULL);
    int time_elapsed = difftime(_end,_begin);
    int hours = time_elapsed/3600;
    int minutes = (time_elapsed%3600)/60;
    int seconds = (time_elapsed%3600)%60;
    //cout << "-----------------------------------------------------------------------------------" << endl;
    //cout << "Time to process the selection on " << datasetName << ": " << endl;
    //cout << hours << " hours " << minutes << " minutes " << seconds << " seconds." << endl;
    //cout << "-----------------------------------------------------------------------------------" << endl;
    
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    _CutflowFile << "Time to process the selection: " << hours << " hours " << minutes << " minutes " << seconds << " seconds." << endl;
    _CutflowFile << "-----------------------------------------------------------------------------------" << endl;
    
    
    //---------------------------------------------------------------------------------------------------
    delete _inputTree;
    delete hPU_weights;
    //delete tightJet_pt;
    //delete tightJet_eta;
    //delete tightJet_phi;
    
    delete vertex_x;
    delete vertex_y;
    delete vertex_z;
    delete vertex_ndof;
    delete vertex_chi2;
    delete vertex_dx;
    delete vertex_dy;
    delete vertex_dz;
    delete vertex_nTracks;
    delete vertex_pt;
    delete secVertex_x;
    delete secVertex_y;
    delete secVertex_z;
    delete secVertex_ndof;
    delete secVertex_chi2;
    delete secVertex_pt;
    delete secVertex_dx;
    delete secVertex_dy;
    delete secVertex_dz;
    
    delete recoJet_pt;
    delete recoJet_phi;
    delete recoJet_eta;
    delete recoJet_btag_combinedInclusiveSecondaryVertexV2BJetTags;
    delete recoJet_btag_CombinedMVAV2BJetTags;
    delete recoJet_btag_CombinedCvsLJetTags;
    delete recoJet_btag_CombinedCvsBJetTags;
    delete recoJet_isLeptonLike;
    delete recoJet_vertex_x;
    delete recoJet_vertex_y;
    delete recoJet_vertex_z;
    delete recoJet_vertex_score;
    delete recoJet_nConsidered;
    delete recoJet_averageDistance;
    delete recoJet_rmsDistance;
    delete tightJet_eta;
    delete tightJet_phi;
    delete tightJet_pt;
    delete muon_px;
    delete muon_py;
    delete muon_pz;
    delete muon_phi;
    delete muon_eta;
    delete muon_iso;
    delete muon_isTightMuon;
    delete muon_isLooseMuon;
    delete electron_px;
    delete electron_py;
    delete electron_pz;
    delete electron_phi;
    delete electron_eta;
    delete electron_iso;
    delete electron_isVeto;
    delete electron_isLoose;
    delete electron_isMedium;
    delete electron_isTight;
    delete electron_isHEEP;
    delete triggerBits;
    delete triggerNames;
    /*
    delete recoJet_constVertex_x;
    delete recoJet_constVertex_y;
    delete recoJet_constVertex_z;
    delete recoJet_const_pt;
    delete recoJet_const_closestVertex_dxy;
    delete recoJet_const_closestVertex_dz;
    delete recoJet_const_closestVertex_d;
    delete recoJet_const_charge;
    */
    
    delete to_TriggerNames;
    delete to_pt;
    delete to_eta;
    delete to_phi;
    delete met;
    delete met_x;
    delete met_y;
    
    
    delete recoCHSJet_eta;
    delete recoCHSJet_phi;
    delete recoCHSJet_pt;
    delete recoCHSJet_constVertex_x;
    delete recoCHSJet_constVertex_y;
    delete recoCHSJet_constVertex_z;
    delete recoCHSJet_constVertexRef_x;
    delete recoCHSJet_constVertexRef_y;
    delete recoCHSJet_constVertexRef_z;
    delete recoCHSJet_const_pt;
    delete recoCHSJet_const_charge;
    delete recoCHSJet_const_fromPV;
    delete recoCHSJet_const_pca0_x;
    delete recoCHSJet_const_pca0_y;
    delete recoCHSJet_const_pca0_z;
    delete recoCHSJet_const_closestVertex_dxy;
    delete recoCHSJet_const_closestVertex_dz;
    delete recoCHSJet_const_closestVertex_d;
    delete recoCHSJet_const_eta;
    delete recoCHSJet_const_phi;
    delete recoCHSJet_const_mass;
   
    delete recoNoCHSJet_eta;
    delete recoNoCHSJet_phi;
    delete recoNoCHSJet_pt;
    delete recoNoCHSJet_constVertex_x;
    delete recoNoCHSJet_constVertex_y;
    delete recoNoCHSJet_constVertex_z;
    delete recoNoCHSJet_constVertexRef_x;
    delete recoNoCHSJet_constVertexRef_y;
    delete recoNoCHSJet_constVertexRef_z;
    delete recoNoCHSJet_const_pt;
    delete recoNoCHSJet_const_charge;
    delete recoNoCHSJet_const_fromPV;
    delete recoNoCHSJet_const_pca0_x;
    delete recoNoCHSJet_const_pca0_y;
    delete recoNoCHSJet_const_pca0_z;
    delete recoNoCHSJet_const_closestVertex_dxy;
    delete recoNoCHSJet_const_closestVertex_dz;
    delete recoNoCHSJet_const_closestVertex_d;
    delete recoNoCHSJet_const_eta;
    delete recoNoCHSJet_const_phi;
    delete recoNoCHSJet_const_mass;
    
    delete tmct_px;
    delete tmct_py;
    delete tmct_pz;
    delete tmct_vx;
    delete tmct_vy;
    delete tmct_vz;
    delete tmct_e;
    delete tmct_id;
    delete tmct_status;
    delete tmct_parent;
    delete tmct_daughters;

}


