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
    
    _MET = sqrt( met_x->at(SYSMET)*met_x->at(SYSMET) + met_y->at(SYSMET)*met_y->at(SYSMET) );
    
    double HPx = 0;
    double HPy = 0;
    for( unsigned int iJet = 0; iJet < tightJet_pt->size(); ++iJet ) {
        TLorentzVector Jet;
        Jet.SetPtEtaPhiE(tightJet_pt->at(iJet), tightJet_eta->at(iJet), tightJet_phi->at(iJet), 0);
        HPx += Jet.Px();
        HPy += Jet.Py();
    }
    _MHT = sqrt(HPx*HPx + HPy*HPy);
    
    //----------------------------------------------------------------------------------------------------
    _Trigger = false;
    for( unsigned int iTrig = 0; iTrig < triggerNames->size(); ++iTrig ) {
        if( triggerNames->at(iTrig).find("HLT_PFMET170_HBHECleaned") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMET120_PFMHT120_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMET110_PFMHT110_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMET100_PFMHT100_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMET90_PFMHT90_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
        if( triggerNames->at(iTrig).find("HLT_PFMETNoMu90_PFMHTNoMu90_IDTight") != std::string::npos && triggerBits->at(iTrig) == 1 ) _Trigger = true;
    }
    
    //----------------------------------------------------------------------------------------------------
    if( ExtraVariables ){
        
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
        
        if( _LeadingJetPV < 0 ){
            _LeadingJetPV_Pt = 0;
        }else{
            _LeadingJetPV_Pt = recoJet_pt->at(_LeadingJetPV).at(SYSJET);
        }
        
        if( _SubLeadingJetPV < 0 ){
            _SubLeadingJetPV_Pt = 0;
        }else{
            _SubLeadingJetPV_Pt = recoJet_pt->at(_SubLeadingJetPV).at(SYSJET);
        }
        

        _SV2Jets.clear();
        _SV1Jet.clear();
    
        for( unsigned int iSV = 0; iSV < secVertex_x->size(); ++iSV ) {
            if( _idJetsToSV.at(iSV).size() == 2 ) _SV2Jets.push_back( iSV );
            if( _idJetsToSV.at(iSV).size() == 1 ) _SV1Jet.push_back( iSV );
        }
    
    
    }
    
    
}
