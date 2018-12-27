#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TColor.h>
#include <math.h>
#include <THnSparse.h>
#include <map>
#include <string>
#include <vector>
#include <TRandom3.h>
#include "THnSparse.h"
#include "TF1.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include <iomanip>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <TMVA/Factory.h>
#include <TMVA/Reader.h>
#include <TMVA/Tools.h>


#ifdef __MAKECINT__
#pragma link C++ class std::vector<std::vector<double> >+;
#pragma link C++ class std::vector<std::vector<float> >+;
#pragma link C++ class std::vector<std::vector<unsigned int > >+;
#pragma link C++ class std::vector<std::vector<int> >+;
#endif


using namespace std;

class LLGAnalysis {
    public:
        static LLGAnalysis* GetInstance( char* configFileName );
        ~LLGAnalysis() {}
        
        vector<double> CalculateVertex( vector<double> x, vector<double> y, vector<double> z, vector<double> weight, vector<int> charge, vector<double> distance, unsigned int &nConsidered, double &weightednConsidered, vector<double> &error ); 
        
        vector<double> CalculateVertexCurved( vector<double>* x_vertex, vector<double>* y_vertex, vector<double>* z_vertex, vector<double>* x_secvertex, vector<double>* y_secvertex, vector<double>* z_secvertex, vector<double> x_ref, vector<double> y_ref, vector<double> z_ref, vector<double> weight, vector<int> charge, vector<double> eta, vector<double> phi, vector<double> mass, vector<double> distance, unsigned int &nConsidered, double &weightednConsidered, vector<double> &error ); 
        
        double MVA_SV2Jets( int iSV, int jetId, int jetID );
        double MVA_SV1Jet( int iSV, int jetID );
        
        bool Init();
        void RunEventLoop( int nEventsMax = -1);
        void FinishRun();
    
    private:
        static LLGAnalysis* _instance;

        void RunObjectID();

        void makeHist( string nametitle, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax, string xtitle, string ytitle, string ztitle, string drawOption = "", double xAxisOffset = 1., double yAxisOffset = 1.2, double zAxisOffset = 1. ); 
        void makeHist( string nametitle, int nbins, double xmin, double xmax, string xtitle, string ytitle, string drawOption = "", double xAxisOffset = 1., double yAxisOffset = 1.2 );
        void setStyle(double ytoff = 1.0, bool marker = true, double left_margin = 0.15); 
        void MakeEfficiencyPlot( TH1D hpass, TH1D htotal, string triggerName = "");
        //void FillEfficiencyHistograms();

        vector<double> CalculatePCA( vector<double> *refPoint, vector<double> *momentum, vector<double> *vertex );

        
        // INSERT YOUR SELECTION HERE


    private:
        LLGAnalysis() {}
        LLGAnalysis( char* configFileName );
        
        map<string, double>     _cutFlow;
        map<string, TH1D>       _histograms1D;
        map<string, TH2D>       _histograms2D;
        map<string, string>     _histograms1DDrawOptions;
        map<string, string>     _histograms2DDrawOptions;
        vector<string>          _inputFileNames;
        string                  _inputTreeName;
        TChain                  *_inputTree;
        TChain                  *_metaTree;
        string                  _outputFileName;
        string                  _outputDirectory;
        TFile                   *_outputFile;
        TTree                   *_outputTree;
        vector<string>           _plotFormats;
        ofstream                _passedLogFile;
        string                  _LogFileName;
        ofstream                _CutflowFile;
        string                  _CutflowFileName;
        int                     _NumberEntries;
        int                     _EventPosition;
        
        //---------------------------------------------------------------------------------------------------
        
        double JET_PT_CUT_SV;
        double JET_PT_CUT_PV;
        double SUBJET_PT_CUT_PV;
        double JET_ETA_CUT;
        double MUON_PT_CUT;
        double ELECTRON_PT_CUT;
        double MET_CUT;
        double MHT_CUT;
        double LEADING_SV_JET_CUT;
        double MJJ_CUT;
        double MVA_CUT_SV_750_80;
        double MVA_CUT_SV_1000_100;
        
        string SELECTION;
        string metadataFileName;
        string datasetName;
        int InputType;
        bool requireGenBranches;
        string GenFileName;
        
        // the total number of events per sample (take it from DAS!)
        double PROC_NTOT;
        // the total cross section for the process in pb
        double PROC_XSEC;
        // the target luminosity in fb-1
        double TARGET_LUMI;

        //for pileup reweighting
        string PUFILE;
        TH1D *hPU_weights;
        string PUTYPE;
        // variables for systematics
        int SYSJET;
        int SYSMET;
        string SYSPILEUP;
        string RUNSYS;
         
        bool applyEventWeights;
        long double evtWeight;
        double lumiWeight;
        bool applyPileupWeights;
        double pileupWeight;
        long double NumberOfEvents;
        vector<long double> StatisticalError;
        
        bool applyGenHTLowerCut;
        bool applyGenHTUpperCut;
        double GENLEVEL_HT_CUT;
        
        int Track;
        bool ExtraVariables;
        
        bool Get_Histograms;    
        bool Get_Tree;            
        bool Get_Image_in_EPS;    
        bool Get_Image_in_PNG;    
        bool Get_Image_in_PDF;
        
        time_t _begin;
        time_t _end;
        
        
        //---------------------------------------------------------------------------------------------------
        // metadata

        double _SumOfWeights;
        
        //---------------------------------------------------------------------------------------------------
        // variables of the InputType 1 and 2
        //---------------------------------------------------------------------------------------------------
        
        int EventNumber;
        int RunNumber;
        int LumiBlock;
        double generatorWeight;
        
        double beam_x;
        double beam_y;
        
        vector<double> *vertex_x;
        vector<double> *vertex_y;
        vector<double> *vertex_z; 
        vector<double> *vertex_ndof;
        vector<double> *vertex_chi2;
        vector<double> *vertex_dx;
        vector<double> *vertex_dy;
        vector<double> *vertex_dz;
        vector<double> *vertex_nTracks; 
        vector<double> *vertex_pt; 
        vector<double> *secVertex_x;
        vector<double> *secVertex_y; 
        vector<double> *secVertex_z;
        vector<double> *secVertex_ndof;
        vector<double> *secVertex_chi2;
        vector<int> *secVertex_nTracks;
        vector<double> *secVertex_pt;
        vector<double> *secVertex_dx;
        vector<double> *secVertex_dy; 
        vector<double> *secVertex_dz; 
        
        //---------------------------------------------------------------------------------------------------
        // variables only of the InputType 1
        
        vector<double> *recoJet_eta;
        vector<double> *recoJet_phi;
        vector<vector<double> > *recoJet_pt; 
        vector<double> *recoJet_vertex_x;
        vector<double> *recoJet_vertex_y;
        vector<double> *recoJet_vertex_z;
        vector<double> *recoJet_C_vertex_x;
        vector<double> *recoJet_C_vertex_y;
        vector<double> *recoJet_C_vertex_z;
        vector<vector<double> > *recoJet_vertex_score;
        vector<int> *recoJet_nConsidered; 
        vector<vector<double> > *recoJet_averageDistance;;
        vector<vector<double> > *recoJet_rmsDistance;
        
        vector<double> *tightJet_eta;
        vector<double> *tightJet_phi;
        vector<double> *tightJet_pt;
        
        vector<double> *recoJet_btag_CombinedMVAV2BJetTags;
        vector<double> *recoJet_btag_CombinedCvsLJetTags;
        vector<double> *recoJet_btag_CombinedCvsBJetTags;
        vector<double> *recoJet_btag_combinedInclusiveSecondaryVertexV2BJetTags;
        float NumberOfTrueInteractions;
        int NumberOfObservedInteractions;
        double genLevel_HT;
        vector<double> *muon_px; 
        vector<double> *muon_py; 
        vector<double> *muon_pz;
            
        vector<double> *muon_eta;
        vector<double> *muon_phi; 
        vector<double> *muon_iso;
        vector<bool>   *muon_isTightMuon;
        
        vector<bool>   *muon_isLooseMuon;
        
        vector<double> *electron_px; 
        vector<double> *electron_py; 
        vector<double> *electron_pz; 
        
        vector<double> *electron_eta;
        vector<double> *electron_phi; 
        vector<double> *electron_iso;
        
        vector<bool> *electron_isVeto;
        vector<bool> *electron_isLoose;
        vector<bool> *electron_isMedium;
        vector<bool> *electron_isTight;
        vector<bool> *electron_isHEEP;
        
        vector<int> *triggerBits; 
        vector<string> *triggerNames; 
        
        vector<string> *to_TriggerNames;
        vector<vector<double> > *to_pt;
        vector<vector<double> > *to_eta;
        vector<vector<double> > *to_phi;
        vector<double> *met;
        vector<double> *met_x;
        vector<double> *met_y;
        
        
        //---------------------------------------------------------------------------------------------------
        // variables only of the InputType 2
        
        vector<double> *recoCHSJet_eta;
        vector<double> *recoCHSJet_phi;
        vector<double> *recoCHSJet_pt;
        vector<vector<double> >* recoCHSJet_constVertex_x; 
        vector<vector<double> >* recoCHSJet_constVertex_y; 
        vector<vector<double> >* recoCHSJet_constVertex_z; 
        vector<vector<double> >* recoCHSJet_constVertexRef_x; 
        vector<vector<double> >* recoCHSJet_constVertexRef_y;
        vector<vector<double> >* recoCHSJet_constVertexRef_z; 
        vector<vector<double> >* recoCHSJet_const_pt; 
        vector<vector<int> >*    recoCHSJet_const_charge;
        vector<vector<int> >*    recoCHSJet_const_fromPV;  
        vector<vector<double> >* recoCHSJet_const_pca0_x; 
        vector<vector<double> >* recoCHSJet_const_pca0_y; 
        vector<vector<double> >* recoCHSJet_const_pca0_z; 
        vector<vector<double> >* recoCHSJet_const_closestVertex_dxy; 
        vector<vector<double> >* recoCHSJet_const_closestVertex_dz; 
        vector<vector<double> >* recoCHSJet_const_closestVertex_d; 
        vector<vector<double> >* recoCHSJet_const_eta;     
        vector<vector<double> >* recoCHSJet_const_phi;  
        vector<vector<double> >* recoCHSJet_const_mass; 
        
        vector<double> *recoNoCHSJet_eta;
        vector<double> *recoNoCHSJet_phi;
        vector<double> *recoNoCHSJet_pt;
        vector<vector<double> >* recoNoCHSJet_constVertex_x; 
        vector<vector<double> >* recoNoCHSJet_constVertex_y; 
        vector<vector<double> >* recoNoCHSJet_constVertex_z; 
        vector<vector<double> >* recoNoCHSJet_constVertexRef_x; 
        vector<vector<double> >* recoNoCHSJet_constVertexRef_y; 
        vector<vector<double> >* recoNoCHSJet_constVertexRef_z;
        vector<vector<double> >* recoNoCHSJet_const_pt;      
        vector<vector<int> >*    recoNoCHSJet_const_charge;  
        vector<vector<int> >*    recoNoCHSJet_const_fromPV;  
        vector<vector<double> >* recoNoCHSJet_const_pca0_x; 
        vector<vector<double> >* recoNoCHSJet_const_pca0_y; 
        vector<vector<double> >* recoNoCHSJet_const_pca0_z; 
        vector<vector<double> >* recoNoCHSJet_const_closestVertex_dxy; 
        vector<vector<double> >* recoNoCHSJet_const_closestVertex_dz; 
        vector<vector<double> >* recoNoCHSJet_const_closestVertex_d; 
        vector<vector<double> >* recoNoCHSJet_const_eta;     
        vector<vector<double> >* recoNoCHSJet_const_phi; 
        vector<vector<double> >* recoNoCHSJet_const_mass;
   
        //---------------------------------------------------------------------------------------------------
        vector<double> *tmct_px; 
        vector<double> *tmct_py; 
        vector<double> *tmct_pz; 
        vector<double> *tmct_vx; 
        vector<double> *tmct_vy; 
        vector<double> *tmct_vz; 
        vector<double> *tmct_e; 
        vector<int> *tmct_id; 
        vector<int> *tmct_status; 
        vector<int> *tmct_parent; 
        vector<vector<int> > *tmct_daughters; 
        
    
        //---------------------------------------------------------------------------------------------------       
        // ObjectID variables
        
        vector<int> vetoElectrons;
        vector<int> looseElectrons;
        vector<int> mediumElectrons;
        vector<int> tightElectrons;
        vector<int> heepElectrons;
        vector<int> vetoMuons;
        vector<int> tightMuons;
        vector<int> selectedJets;
        vector<bool> *recoJet_isLeptonLike;
        
        //----------------------------------------------------------------------------------------------------
        
        bool _Trigger;
        double _MET;
        double _MHT;
        
        vector<vector<int> > _idJetsToPV;
        vector<vector<int> > _idJetsToSV;
        int _LeadingPV;
        int _LeadingJetPV;
        int _SubLeadingJetPV;
        double _LeadingJetPV_Pt;
        double _SubLeadingJetPV_Pt;
        
        vector<int> _SV2Jets;
        vector<int> _SV1Jet;
        

};
