#include "LLGAnalysis.h"

void LLGAnalysis::RunObjectID() {
    
    recoJet_isLeptonLike = new vector<bool>;
    vetoElectrons.clear();
    looseElectrons.clear();
    mediumElectrons.clear();
    tightElectrons.clear();
    heepElectrons.clear();
    vetoMuons.clear();
    tightMuons.clear();
    selectedJets.clear();
    recoJet_isLeptonLike->clear();
    
    //----------------------------------------------------------------------------------------------------
    // first the muons 
    for( unsigned int im = 0; im < muon_px->size(); ++im ) {
        double pt = sqrt(muon_px->at(im)*muon_px->at(im) + muon_py->at(im)*muon_py->at(im));
        if( muon_iso->size() > 0 ) {
          if( muon_iso->at(im) > 0.2 ) continue;
        }
        if( pt < MUON_PT_CUT ) continue;
        
        vetoMuons.push_back(im);
        if( muon_isTightMuon->at(im) ) tightMuons.push_back(im);
    }
    
    //----------------------------------------------------------------------------------------------------
    // now the electrons
    for( unsigned int ie = 0; ie < electron_px->size(); ++ie ) {
        double pt = sqrt(electron_px->at(ie)*electron_px->at(ie) + electron_py->at(ie)*electron_py->at(ie));
        if( pt < ELECTRON_PT_CUT ) continue;
        if( electron_isVeto->at(ie) )   vetoElectrons.push_back(ie);
        if( electron_isLoose->at(ie) )  looseElectrons.push_back(ie);
        if( electron_isMedium->at(ie) ) mediumElectrons.push_back(ie);
        if( electron_isTight->at(ie) )  tightElectrons.push_back(ie);
        if( electron_isHEEP->at(ie) )   heepElectrons.push_back(ie);
    }
    
    //----------------------------------------------------------------------------------------------------
    // and the jets
    // first, identify lepton-like jets:
    for( unsigned int iJet = 0; iJet < recoJet_pt->size(); ++iJet ) {
      double jeta = recoJet_eta->at(iJet);
      double jphi = recoJet_phi->at(iJet);
      double drMin = 10000;
      
      // remove jets overlapping with electrons
      for( unsigned int ivetoEle = 0; ivetoEle < vetoElectrons.size(); ++ivetoEle ) {
        int iEle = vetoElectrons.at(ivetoEle);
        double eeta = electron_eta->at(iEle);
        double ephi = electron_phi->at(iEle);
        double deta = fabs(eeta - jeta);
        double dphi = fabs( ephi - jphi );
        if( dphi > M_PI ) dphi = 2*M_PI - dphi;
        double dr = sqrt( deta*deta + dphi*dphi );
        if( dr < drMin ) drMin = dr;
      }
      
      //remove jets overlapping with muons:
      for( unsigned int ivetoMuon = 0; ivetoMuon < vetoMuons.size(); ++ivetoMuon ) {
        int iMuon = vetoMuons.at(ivetoMuon);
        double eeta = muon_eta->at(iMuon);
        double ephi = muon_phi->at(iMuon);
        double deta = fabs(eeta - jeta);
        double dphi = fabs( ephi - jphi );
        if( dphi > M_PI ) dphi = 2*M_PI - dphi;
        double dr = sqrt( deta*deta + dphi*dphi );
        if( dr < drMin ) drMin = dr;
      }

      // and fill the recoJet variable:
      recoJet_isLeptonLike->push_back( (drMin < 0.4 ) ? true : false );
    }

    // now fill the signal jets:
    for( unsigned int iJet = 0; iJet < recoJet_pt->size(); ++iJet ) {
        if( recoJet_isLeptonLike->at(iJet) ) continue;
        if( fabs(recoJet_eta->at(iJet)) > JET_ETA_CUT ) continue;
        //if( j.pt() < 10. ) continue;
        selectedJets.push_back(iJet);
    }
    
    
    //----------------------------------------------------------------------------------------------------
    if( ExtraVariables ){
        
        _MET = sqrt( met_x->at(SYSMET)*met_x->at(SYSMET) + met_y->at(SYSMET)*met_y->at(SYSMET) );
                
        _LeadingPV = 0;
        double leadingVertexPt = 0.;
        // now assign jets to the vertices:
        _idJetsToPV.clear();
        _idJetsToSV.clear();
        for( unsigned int iVtx = 0; iVtx < vertex_x->size(); ++iVtx ) {
            vector<int> idx;
            _idJetsToPV.push_back( idx );
        }
        for( unsigned int iVtx = 0; iVtx < secVertex_x->size(); ++iVtx ) {
            vector<int> idx;
            _idJetsToSV.push_back( idx );
        }
    
        for( unsigned int iselJet = 0; iselJet < selectedJets.size(); ++iselJet ) {
            int iJet = selectedJets.at(iselJet);
            vector<double> position(3,0.);
            if( Track == 0 ){
                position.at(0) = recoJet_vertex_x->at(iJet);
                position.at(1) = recoJet_vertex_y->at(iJet);
                position.at(2) = recoJet_vertex_z->at(iJet);
            }else if( Track == 1 ){
                position.at(0) = recoJet_C_vertex_x->at(iJet);
                position.at(1) = recoJet_C_vertex_y->at(iJet);
                position.at(2) = recoJet_C_vertex_z->at(iJet);
            }
            int nMatch = 0;
        
            for( unsigned int iVtx = 0; iVtx < vertex_x->size(); ++iVtx ) {
                if( fabs(position.at(0) - vertex_x->at(iVtx) ) < 1.e-10 &&
                    fabs(position.at(1) - vertex_y->at(iVtx) ) < 1.e-10 &&
                    fabs(position.at(2) - vertex_z->at(iVtx) ) < 1.e-10 ) {
                    if( recoJet_pt->at(iJet).at(SYSJET) < 30 ) continue;
                    _idJetsToPV.at(iVtx).push_back( iJet );
                    if( recoJet_pt->at(iJet).at(SYSJET) > leadingVertexPt ) {
                        _LeadingPV = iVtx;
                    }
                    nMatch += 1;
                }
            }
            for( unsigned int iVtx = 0; iVtx < secVertex_x->size(); ++iVtx ) {
                if( fabs(position.at(0) - secVertex_x->at(iVtx) ) < 1.e-10 &&
                    fabs(position.at(1) - secVertex_y->at(iVtx) ) < 1.e-10 &&
                    fabs(position.at(2) - secVertex_z->at(iVtx) ) < 1.e-10 ) {
                
                    _idJetsToSV.at(iVtx).push_back( iJet );
                    nMatch += 1;

                }
            }
            if( nMatch > 1 ) {
                cout << "WARNING! ASSOCIATED JET TO MORE THAN 1 VERTEX ?!" << endl;
            }
        }
    
        
        double ptLeadingJetPV = 0.;
        double ptSubLeadingJetPV = 0;
        _LeadingJetPV = -1;
        _SubLeadingJetPV = -1;

        for( unsigned int iiJet = 0; iiJet < _idJetsToPV.at(_LeadingPV).size(); ++iiJet ) {
            int iJet = _idJetsToPV.at(_LeadingPV).at(iiJet);
              
            if( recoJet_pt->at(iJet).at(SYSJET) > ptLeadingJetPV ) {
                ptSubLeadingJetPV = ptLeadingJetPV;
                _SubLeadingJetPV = _LeadingJetPV;
                ptLeadingJetPV = recoJet_pt->at(iJet).at(SYSJET);
                _LeadingJetPV = iJet;
            } else if ( recoJet_pt->at(iJet).at(SYSJET) > ptSubLeadingJetPV ) {
                ptSubLeadingJetPV = recoJet_pt->at(iJet).at(SYSJET);
                _SubLeadingJetPV = iJet;
            }
        }
        

        _SV2Jets.clear();
        _SV1Jet.clear();
    
        for( unsigned int iSV = 0; iSV < secVertex_x->size(); ++iSV ) {
            if( _idJetsToSV.at(iSV).size() == 2 ) _SV2Jets.push_back( iSV );
            if( _idJetsToSV.at(iSV).size() == 1 ) _SV1Jet.push_back( iSV );
        }
    
    
        _SV2Jets_X.clear();
        _SV2Jets_Y.clear();
        _SV2Jets_Z.clear();
        _SV2Jets_DS.clear(); //[cm]
        _SV2Jets_Pt.clear();
        _SV2Jets_Chi2.clear();
        _SV2Jets_Ndof.clear();
        _SV2Jets_MJJ.clear();
        _SV2Jets_DEtaJJ.clear();
        _SV2Jets_DPhiJJ.clear();
        _SV2Jets_DRJJ.clear();
        _SV2Jets_MinJetPt.clear();
        _SV2Jets_MaxJetPt.clear();
        _SV2Jets_Score.clear();
        _SV2Jets_NumConst.clear();
        
        for( unsigned int iiSV = 0; iiSV < _SV2Jets.size(); ++iiSV ) {
            int iSV = _SV2Jets.at(iiSV);
            int Jet1 = _idJetsToSV.at(iSV).at(0);
            int Jet2 = _idJetsToSV.at(iSV).at(1);
            double MaxJetPt;
            double MinJetPt;
            double DEta;
            double DPhi;
            if( recoJet_pt->at(Jet1).at(SYSJET) >= recoJet_pt->at(Jet2).at(SYSJET) ){
                MaxJetPt = recoJet_pt->at(Jet1).at(SYSJET);
                MinJetPt = recoJet_pt->at(Jet2).at(SYSJET);
            }else{
                MaxJetPt = recoJet_pt->at(Jet2).at(SYSJET);
                MinJetPt = recoJet_pt->at(Jet1).at(SYSJET);
            }
            DEta = abs(recoJet_eta->at(Jet2) - recoJet_eta->at(Jet1));
            DPhi = abs(recoJet_phi->at(Jet2) - recoJet_phi->at(Jet1));
            if( DPhi > M_PI ) DPhi = 2*M_PI-DPhi;
    
            _SV2Jets_X.push_back( secVertex_x->at(iSV) );
            _SV2Jets_Y.push_back( secVertex_y->at(iSV) );
            _SV2Jets_Z.push_back( secVertex_z->at(iSV) );
            _SV2Jets_DS.push_back( 10*sqrt(secVertex_dx->at(iSV)*secVertex_dx->at(iSV) + secVertex_dy->at(iSV)*secVertex_dy->at(iSV) + secVertex_dz->at(iSV)*secVertex_dz->at(iSV)) ); //[cm]
            _SV2Jets_Pt.push_back( secVertex_pt->at(iSV) );
            _SV2Jets_Chi2.push_back( secVertex_chi2->at(iSV) );
            _SV2Jets_Ndof.push_back( secVertex_ndof->at(iSV) );
            _SV2Jets_MJJ.push_back( sqrt( 2*recoJet_pt->at(Jet1).at(SYSJET)*recoJet_pt->at(Jet2).at(SYSJET)*(cosh(recoJet_eta->at(Jet1) - recoJet_eta->at(Jet2)) - cos(recoJet_phi->at(Jet1) - recoJet_phi->at(Jet2)) )) );
            _SV2Jets_DEtaJJ.push_back( DEta );
            _SV2Jets_DPhiJJ.push_back( DPhi );
            _SV2Jets_DRJJ.push_back( sqrt( DEta*DEta + DPhi*DPhi ) );
            _SV2Jets_MinJetPt.push_back( MinJetPt );
            _SV2Jets_MaxJetPt.push_back( MaxJetPt );
            _SV2Jets_Score.push_back( log(recoJet_vertex_score->at(Jet1).at(Track)) + log(recoJet_vertex_score->at(Jet2).at(Track)) );
            _SV2Jets_NumConst.push_back( recoJet_nConsidered->at(Jet1) + recoJet_nConsidered->at(Jet2) );
        }
    
        
        _SV1Jet_X.clear();
        _SV1Jet_Y.clear();
        _SV1Jet_Z.clear();
        _SV1Jet_DS.clear(); //[cm]
        _SV1Jet_Pt.clear();
        _SV1Jet_Chi2.clear();
        _SV1Jet_Ndof.clear();
        _SV1Jet_JetPt.clear();
        _SV1Jet_Score.clear();
        _SV1Jet_NumConst.clear();
        for( unsigned int iiSV = 0; iiSV < _SV1Jet.size(); ++iiSV ) {
            int iSV = _SV1Jet.at(iiSV);
            int Jet = _idJetsToSV.at(iSV).at(0);
            
            _SV1Jet_X.push_back( secVertex_x->at(iSV) );
            _SV1Jet_Y.push_back( secVertex_y->at(iSV) );
            _SV1Jet_Z.push_back( secVertex_z->at(iSV) );
            _SV1Jet_DS.push_back( 10*sqrt(secVertex_dx->at(iSV)*secVertex_dx->at(iSV) + secVertex_dy->at(iSV)*secVertex_dy->at(iSV) + secVertex_dz->at(iSV)*secVertex_dz->at(iSV)) ); //[cm]
            _SV1Jet_Pt.push_back( secVertex_pt->at(iSV) );
            _SV1Jet_Chi2.push_back( secVertex_chi2->at(iSV) );
            _SV1Jet_Ndof.push_back( secVertex_ndof->at(iSV) );
            _SV1Jet_JetPt.push_back( recoJet_pt->at(Jet).at(SYSJET) );
            _SV1Jet_Score.push_back( log(recoJet_vertex_score->at(Jet).at(Track)) );
            _SV1Jet_NumConst.push_back( recoJet_nConsidered->at(Jet) );
        }
    
    }
    
}
