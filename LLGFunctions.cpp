#include "LLGAnalysis.h"

//---------------------------------------------------------------------------------------------------------------
// MVA_SV1Jet
//--------------------------------------------------------------------------------------------------------------- 
double LLGAnalysis::MVA_SV1Jet( int iSV, int jetID ) {
   
   float x1,x2,x3,x4,x5,x6,x7;
  
   // Building the reader
   TMVA::Reader *reader = new TMVA::Reader("Silent");
   
   // Insering data
   reader->AddVariable("Chi2", &x1);
   reader->AddVariable("Ndof", &x2);
   reader->AddVariable("Score", &x3);
   reader->AddVariable("NumConst", &x4);
   reader->AddVariable("SVPt", &x5);
   reader->AddVariable("SVError", &x6);
   reader->AddVariable("MaxJetPt", &x7);
  
   // Choosing the multivariate method to use 
   reader->BookMVA("MVA","Configuration/MVA_weights/TMVAClassification_BDT_60_3_0.5_v1.weights.xml");
  

   x1  = secVertex_chi2->at(iSV);
   
   x2  = secVertex_ndof->at(iSV);
   
   x3 = recoJet_vertex_score->at(jetID).at(Track);
      
   x4 = recoJet_nConsidered->at(jetID);
      
   x5 = secVertex_pt->at(iSV);
   
   x6 = 10*sqrt(secVertex_dx->at(iSV)*secVertex_dx->at(iSV) + secVertex_dy->at(iSV)*secVertex_dy->at(iSV) + secVertex_dz->at(iSV)*secVertex_dz->at(iSV));
     
   x7  = recoJet_pt->at(jetID).at(SYSJET);
      
   double mva = reader->EvaluateMVA("MVA");
       
   return mva;
}

//---------------------------------------------------------------------------------------------------------------
// MVA_SV2Jets
//--------------------------------------------------------------------------------------------------------------- 
double LLGAnalysis::MVA_SV2Jets( int iSV, int jetId, int jetID ) {
   
   float x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12;
  
   // Building the reader
   TMVA::Reader *reader = new TMVA::Reader("Silent");
   
   // Insering data
   reader->AddVariable("MJJ", &x1);
   reader->AddVariable("Chi2", &x2);
   reader->AddVariable("Ndof", &x3);
   reader->AddVariable("DPhiJJ", &x4);
   reader->AddVariable("DEtaJJ", &x5);
   reader->AddVariable("DRJJ", &x6);
   reader->AddVariable("Score", &x7);
   reader->AddVariable("NumConst", &x8);
   reader->AddVariable("SVPt", &x9);
   reader->AddVariable("SVError", &x10);
   reader->AddVariable("MinJetPt", &x11);
   reader->AddVariable("MaxJetPt", &x12);
  
   // Choosing the multivariate method to use 
   reader->BookMVA("MVA","Configuration/MVA_weights/TMVAClassification_BDT_60_3_0.5_v3.weights.xml");
  

   x1  = sqrt( 2 * (recoJet_pt->at(jetId).at(SYSJET)) * (recoJet_pt->at(jetID).at(SYSJET)) * ( cosh(recoJet_eta->at(jetId) - recoJet_eta->at(jetID)) - cos(recoJet_phi->at(jetId) - recoJet_phi->at(jetID)) ) );
   
   x2  = secVertex_chi2->at(iSV);
   
   x3  = secVertex_ndof->at(iSV);
   
   x4  = abs(recoJet_phi->at(jetId) - recoJet_phi->at(jetID)); 
   if( x4 > M_PI ) x4 = 2*M_PI - x4;
   
   x5  = abs(recoJet_eta->at(jetId) - recoJet_eta->at(jetID));
   
   x6  = sqrt( x4*x4 + x5*x5 );
   
   x7 = recoJet_vertex_score->at(jetId).at(Track) + recoJet_vertex_score->at(jetID).at(Track);
      
   x8 = recoJet_nConsidered->at(jetId) + recoJet_nConsidered->at(jetID);
      
   x9 = secVertex_pt->at(iSV);
   
   x10 = 10*sqrt(secVertex_dx->at(iSV)*secVertex_dx->at(iSV) + secVertex_dy->at(iSV)*secVertex_dy->at(iSV) + secVertex_dz->at(iSV)*secVertex_dz->at(iSV));
   
   double MaxJetPt, MinJetPt;
   if( recoJet_pt->at(jetId).at(SYSJET) >= recoJet_pt->at(jetID).at(SYSJET) ){
       MaxJetPt = recoJet_pt->at(jetId).at(SYSJET);
       MinJetPt = recoJet_pt->at(jetID).at(SYSJET);
   }else{
       MaxJetPt = recoJet_pt->at(jetID).at(SYSJET);
       MinJetPt = recoJet_pt->at(jetId).at(SYSJET);
   }
   
   x11  = MinJetPt;
   
   x12  = MaxJetPt;
      
   double mva = reader->EvaluateMVA("MVA");
       
   return mva;
}


//---------------------------------------------------------------------------------------------------------------
// CalculateVertex
//--------------------------------------------------------------------------------------------------------------- 
vector<double> LLGAnalysis::CalculateVertex( vector<double> x, vector<double> y, vector<double> z, vector<double> weight, vector<int> charge, vector<double> distance, unsigned int &nConsidered, double &weightednConsidered, vector<double> &error ) {
   
   nConsidered = 0;
   vector<double> diff_x;
   vector<double> diff_y;
   vector<double> diff_z;
   vector<double> score;
   
   for( unsigned int i = 0; i < x.size(); ++i ) {
      if( charge.at(i) == 0 ) continue;
      nConsidered += 1;
      bool knownPoint = false;
      int iKnown = -1;
      for( unsigned int i2 = 0; i2 < diff_x.size(); ++i2 ) {
        if( fabs( diff_x.at(i2) - x.at(i) ) < 1.e-10 && fabs( diff_y.at(i2) - y.at(i) ) < 1.e-10 && fabs( diff_z.at(i2) - z.at(i) ) < 1.e-10 ) {
            knownPoint = true;
            iKnown = i2;
        }
      }
    
      if( knownPoint ) {
        score.at(iKnown) += weight.at(i)/distance.at(i);
      }
      else {
        diff_x.push_back( x.at(i) );
        diff_y.push_back( y.at(i) );
        diff_z.push_back( z.at(i) );
        score.push_back( weight.at(i)/distance.at(i) );
      }
   }
    
   double scoreMax = 0.;
   vector<double> mean(3, -10000.);
   for( unsigned int i = 0; i < diff_x.size(); ++i ) {
        if ( score.at(i) > scoreMax ) {
            scoreMax = score.at(i);
            mean.at(0) = diff_x.at(i);
            mean.at(1) = diff_y.at(i);
            mean.at(2) = diff_z.at(i);
        }
    }
    return mean;
}

//---------------------------------------------------------------------------------------------------------------
// CalculateVertexCurved
//--------------------------------------------------------------------------------------------------------------- 
vector<double> LLGAnalysis::CalculateVertexCurved( vector<double>* x_vertex, vector<double>* y_vertex, vector<double>* z_vertex, vector<double>* x_secvertex, vector<double>* y_secvertex, vector<double>* z_secvertex, vector<double> x_ref, vector<double> y_ref, vector<double> z_ref, vector<double> weight, vector<int> charge, vector<double> eta, vector<double> phi, vector<double> mass, vector<double> distance, unsigned int &nConsidered, double &weightednConsidered, vector<double> &error ) {
   
   nConsidered = 0;
   vector<double> diff_x;
   vector<double> diff_y;
   vector<double> diff_z;
   vector<double> score;
   vector<double> x;
   vector<double> y;
   vector<double> z;
   double c = 299792458;
   
   for( unsigned int i = 0; i < x_ref.size(); ++i ) {
      if( charge.at(i) == 0 ) continue;
      double dMin = 100000.; 
      double x_temp;
      double y_temp;
      double z_temp;
      TLorentzVector particleP4;
      particleP4.SetPtEtaPhiM( weight.at(i), eta.at(i), phi.at(i), mass.at(i) );
      double px = particleP4.Px();
      double py = particleP4.Py();
      double pz = particleP4.Pz();
      double gamma = particleP4.E()/mass.at(i);
      double omega = 3.415*1.e8*charge.at(i)/gamma/mass.at(i);
      double a_B = 1000*c/(omega*gamma*mass.at(i));
      
      //cout << "mass = " << mass.at(i) << endl;
                
      for( unsigned int j =0; j < x_vertex->size(); ++j ){
        double pv_x = x_vertex->at(j); 
        double pv_y = y_vertex->at(j);
        double pv_z = z_vertex->at(j);
                
        // A*t_min^3 + B*t_min^2 + C*t_min^1 + D = 0
        double D = ((pv_x-x_ref.at(i))*px + (pv_y-y_ref.at(i))*py + (pv_z-z_ref.at(i))*pz)*a_B*omega;
        double C = -((pv_x-x_ref.at(i))*py - (pv_y-y_ref.at(i))*px)*a_B*pow(omega,2) - pow(particleP4.P(),2)*pow(a_B,2)*pow(omega,2);
        double B = 0;
        double A = -(pow(px,2)+pow(py,2))*pow(a_B,2)*pow(omega,4)/2;        
        double W = cbrt(-108.*D*pow(A,2) + 36.*C*B*A + 12.*sqrt(3)*A*sqrt(27.*pow(A,2)*pow(D,2)-18.*A*B*C*D+4*A*pow(C,3)+4*pow(B,3)*D-pow(B,2)*pow(C,2)) - 8.*pow(B,3));
        
        double t_min = W/(6*A) - 2*(3*A*C-pow(B,2))/(3*A*W) - B/(3*A);
        
        double dx_min = pv_x - (x_ref.at(i) + a_B*omega*px*t_min - a_B*pow(omega,2)*py*pow(t_min,2)/2);             
        double dy_min = pv_y - (y_ref.at(i) + a_B*omega*py*t_min + a_B*pow(omega,2)*px*pow(t_min,2)/2);
        double dz_min = pv_z - (z_ref.at(i) + a_B*omega*pz*t_min);             
        double d = sqrt(dx_min*dx_min + dy_min*dy_min + dz_min*dz_min);
        if(d < dMin){
          dMin = d;
          x_temp = pv_x;
          y_temp = pv_y;
          z_temp = pv_z;
        }
      } 
      for( unsigned int j =0; j < x_secvertex->size(); ++j ){
        double pv_x = x_secvertex->at(j); 
        double pv_y = y_secvertex->at(j);
        double pv_z = z_secvertex->at(j);
                
        // A*t_min^3 + B*t_min^2 + C*t_min^1 + D = 0
        double D = ((pv_x-x_ref.at(i))*px + (pv_y-y_ref.at(i))*py + (pv_z-z_ref.at(i))*pz)*a_B*omega;
        double C = -((pv_x-x_ref.at(i))*py - (pv_y-y_ref.at(i))*px)*a_B*pow(omega,2) - pow(particleP4.P(),2)*pow(a_B,2)*pow(omega,2);
        double B = 0;
        double A = -(pow(px,2)+pow(py,2))*pow(a_B,2)*pow(omega,4)/2;        
        double W = cbrt(-108.*D*pow(A,2) + 36.*C*B*A + 12.*sqrt(3)*A*sqrt(27.*pow(A,2)*pow(D,2)-18.*A*B*C*D+4*A*pow(C,3)+4*pow(B,3)*D-pow(B,2)*pow(C,2)) - 8.*pow(B,3));
        
        double t_min = W/(6*A) - 2*(3*A*C-pow(B,2))/(3*A*W) - B/(3*A);
        
        double dx_min = pv_x - (x_ref.at(i) + a_B*omega*px*t_min - a_B*pow(omega,2)*py*pow(t_min,2)/2);             
        double dy_min = pv_y - (y_ref.at(i) + a_B*omega*py*t_min + a_B*pow(omega,2)*px*pow(t_min,2)/2);
        double dz_min = pv_z - (z_ref.at(i) + a_B*omega*pz*t_min);             
        double d = sqrt(dx_min*dx_min + dy_min*dy_min + dz_min*dz_min);
        if(d < dMin){
          dMin = d;
          x_temp = pv_x;
          y_temp = pv_y;
          z_temp = pv_z;
        }
      } 
      
      x.push_back( x_temp );
      y.push_back( y_temp );
      z.push_back( z_temp );
      //cout << "distance in " << i << " = " << distance.at(i) << endl;
      //cout << "distance_new in " << i << " = " << dMin << endl; 
       
      nConsidered += 1;
      bool knownPoint = false;
      int iKnown = -1;
      for( unsigned int i2 = 0; i2 < diff_x.size(); ++i2 ) {
        if( fabs( diff_x.at(i2) - x.at(i) ) < 1.e-10 && fabs( diff_y.at(i2) - y.at(i) ) < 1.e-10 && fabs( diff_z.at(i2) - z.at(i) ) < 1.e-10 ) {
            knownPoint = true;
            iKnown = i2;
        }
      }
    
      if( knownPoint ) {
        score.at(iKnown) += weight.at(i)/dMin;
      }
      else {
        diff_x.push_back( x.at(i) );
        diff_y.push_back( y.at(i) );
        diff_z.push_back( z.at(i) );
        score.push_back( weight.at(i)/dMin );
      }
   }
    
   double scoreMax = 0.;
   vector<double> mean(3, -10000.);
   for( unsigned int i = 0; i < diff_x.size(); ++i ) {
        if ( score.at(i) > scoreMax ) {
            scoreMax = score.at(i);
            mean.at(0) = diff_x.at(i);
            mean.at(1) = diff_y.at(i);
            mean.at(2) = diff_z.at(i);
        }
    }
    return mean;
}

//---------------------------------------------------------------------------------------------------------------
// MakeEfficiencyPlot
//--------------------------------------------------------------------------------------------------------------- 
void LLGAnalysis::MakeEfficiencyPlot( TH1D hpass, TH1D htotal, string triggerName ) {
    TCanvas c("","");
    TGraphAsymmErrors geff;
    geff.BayesDivide( &hpass, &htotal );
    geff.GetXaxis()->SetTitle( hpass.GetXaxis()->GetTitle() );
    string ytitle = "#varepsilon (" + triggerName + ")";
    geff.GetYaxis()->SetTitle( ytitle.c_str() );
    string efftitle = _outputDirectory + "efficiency_" + triggerName;
    geff.SetNameTitle(efftitle.c_str(), efftitle.c_str());
    geff.SetMarkerColor(kBlue);
    geff.Draw("APZ"); 
    for( vector<string>::iterator itr_f = _plotFormats.begin(); itr_f != _plotFormats.end(); ++itr_f ) {
        string thisPlotName = efftitle + (*itr_f);
        c.Print( thisPlotName.c_str() );
    }

}


//---------------------------------------------------------------------------------------------------------------
// makeHist
//--------------------------------------------------------------------------------------------------------------- 
void LLGAnalysis::makeHist( string nametitle, int nbinsx, double xmin, double xmax, int nbinsy, double ymin, double ymax, string xtitle, string ytitle, string ztitle, string drawOption, double xAxisOffset, double yAxisOffset, double zAxisOffset ) {

    TH2D hist(nametitle.c_str(), nametitle.c_str(), nbinsx, xmin, xmax, nbinsy, ymin, ymax );
    hist.GetXaxis()->SetTitle( xtitle.c_str() );
    hist.GetYaxis()->SetTitle( ytitle.c_str() );
    hist.GetZaxis()->SetTitle( ztitle.c_str() );
    hist.GetXaxis()->SetTitleOffset( xAxisOffset );
    hist.GetYaxis()->SetTitleOffset( yAxisOffset );
    hist.GetZaxis()->SetTitleOffset( zAxisOffset );
    _histograms2D.insert( pair<string, TH2D>( nametitle, hist ) );
    _histograms2DDrawOptions.insert( pair<string,string>( nametitle, drawOption ) );

}

void LLGAnalysis::makeHist( string nametitle, int nbins, double xmin, double xmax, string xtitle, string ytitle, string drawOption, double xAxisOffset, double yAxisOffset ) {

    TH1D hist(nametitle.c_str(), nametitle.c_str(), nbins, xmin, xmax );
    hist.GetXaxis()->SetTitle( xtitle.c_str() );
    hist.GetYaxis()->SetTitle( ytitle.c_str() );
    hist.GetYaxis()->SetTitleOffset( yAxisOffset );
    hist.GetXaxis()->SetTitleOffset( xAxisOffset );
    _histograms1D.insert( pair<string, TH1D>( nametitle, hist ) );
    _histograms1DDrawOptions.insert( pair<string,string>( nametitle, drawOption ) );
}


//---------------------------------------------------------------------------------------------------------------
// FillEfficiencyHistograms
//---------------------------------------------------------------------------------------------------------------
/*
void LLGAnalysis::FillEfficiencyHistograms() {
        
    // don' fill these histograms with weights as they are used for the efficiency plots!
    
    _histograms1D.at("MET_allEvents").Fill( met->at(SYSMET) );
    int leadingJet = -1;
    double leadingJetPt = 0.;
    for( unsigned int iJet = 0; iJet < recoJet_pt->size(); ++iJet ) {
        if( recoJet_pt->at(iJet).at(SYSJET) > leadingJetPt ) {
            leadingJetPt = recoJet_pt->at(iJet).at(SYSJET);
            leadingJet = iJet;
        }
    }
    // don' fill these histograms with weights as they are used for the efficiency plots!
    if( leadingJet >= 0 ) _histograms1D.at("jet1_pt_allEvents").Fill( recoJet_pt->at(leadingJet).at(SYSJET) );


    for( unsigned int iTrig = 0; iTrig < triggerNames->size(); ++iTrig ) {
            
        // don' fill these histograms with weights as they are used for the efficiency plots!
        if( triggerNames->at(iTrig) == "HLT_PFMET170_NoiseCleaned_v1" && triggerBits->at(iTrig) == 1 ) {
            _histograms1D.at("MET_HLT_PFMET170_NoiseCleaned_v1").Fill( met->at(SYSMET) );
        }
        if( triggerNames->at(iTrig) == "HLT_PFJet260_v1" && triggerBits->at(iTrig) == 1 ) {
            _histograms1D.at("jet1_pt_HLT_PFJet260_v1" ).Fill( recoJet_pt->at(leadingJet).at(SYSJET) );
        }
    }
}
*/

//---------------------------------------------------------------------------------------------------------------
// CalculatePCA
//--------------------------------------------------------------------------------------------------------------- 
vector<double> LLGAnalysis::CalculatePCA( vector<double> *refPoint, vector<double> *momentum, vector<double> *vertex ) {
  
  // normalize momentum vector
  double norm = sqrt( momentum->at(0)*momentum->at(0) + momentum->at(1)*momentum->at(1) + momentum->at(2)*momentum->at(2) );
  double px_e = momentum->at(0)/norm;
  double py_e = momentum->at(1)/norm;
  double pz_e = momentum->at(2)/norm;

  double or_x = refPoint->at(0);
  double or_y = refPoint->at(1);
  double or_z = refPoint->at(2);
            
  double upv_x = vertex->at(0);
  double upv_y = vertex->at(1);
  double upv_z = vertex->at(2);

//  std::cout << "calculating pca for origin : " << or_x << " " << or_y << " " << or_z << " with momentum : " << norm*px_e << " " << norm*py_e << " " << norm*pz_e << endl;
//  std::cout << "checking pca for " << vertex->at(0) << " " << vertex->at(1) << " " << vertex->at(2) << endl;


  double tmin = - ( px_e*(or_x-upv_x) + py_e*(or_y-upv_y) + pz_e*(or_z-upv_z) );
  double dx_min = upv_x - or_x - tmin*px_e;
  double dy_min = upv_y - or_y - tmin*py_e;
  double dz_min = upv_z - or_z - tmin*pz_e;

  vector<double> retVec;
  retVec.push_back( or_x + tmin*px_e );
  retVec.push_back( or_y + tmin*py_e );
  retVec.push_back( or_z + tmin*pz_e );
  retVec.push_back( dx_min );
  retVec.push_back( dy_min );
  retVec.push_back( dz_min );

  return retVec;

}


//---------------------------------------------------------------------------------------------------------------
// setStyle
//--------------------------------------------------------------------------------------------------------------- 
void LLGAnalysis::setStyle( double ytoff, bool marker, double left_margin ) {
// use plain black on white colors
Int_t icol=0;
gStyle->SetFrameBorderMode(icol);
gStyle->SetCanvasBorderMode(icol);
gStyle->SetPadBorderMode(icol);
gStyle->SetPadColor(icol);
gStyle->SetCanvasColor(icol);
gStyle->SetStatColor(icol);
gStyle->SetTitleFillColor(icol);
// set the paper & margin sizes
gStyle->SetPaperSize(20,26);
gStyle->SetPadTopMargin(0.10);
gStyle->SetPadRightMargin(0.15);
gStyle->SetPadBottomMargin(0.16);
gStyle->SetPadLeftMargin(0.15);
// use large fonts
Int_t font=62;
Double_t tsize=0.04;
gStyle->SetTextFont(font);
gStyle->SetTextSize(tsize);
gStyle->SetLabelFont(font,"x");
gStyle->SetTitleFont(font,"x");
gStyle->SetLabelFont(font,"y");
gStyle->SetTitleFont(font,"y");
gStyle->SetLabelFont(font,"z");
gStyle->SetTitleFont(font,"z");
gStyle->SetLabelSize(tsize,"x");
gStyle->SetTitleSize(tsize,"x");
gStyle->SetLabelSize(tsize,"y");
gStyle->SetTitleSize(tsize,"y");
gStyle->SetLabelSize(tsize,"z");
gStyle->SetTitleSize(tsize,"z");
gStyle->SetTitleBorderSize(0);
//use bold lines and markers
if ( marker ) {
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.2);
}
gStyle->SetHistLineWidth(Width_t(3.));
// postscript dashes
gStyle->SetLineStyleString(2,"[12 12]");
gStyle->SetOptStat(0);
gStyle->SetOptFit(1111);
// put tick marks on top and RHS of plots
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);
// DLA overrides
gStyle->SetPadLeftMargin(left_margin);
gStyle->SetPadBottomMargin(0.13);
gStyle->SetTitleYOffset(ytoff);
gStyle->SetTitleXOffset(1.0);
gStyle->SetOptTitle(0);
//gStyle->SetStatStyle(0);
//gStyle->SetStatFontSize();
gStyle->SetStatW(0.17);

}



