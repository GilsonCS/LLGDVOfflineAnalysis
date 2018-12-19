#!/bin/bash

if [ ! -e _${1}.cpp ]; then 
  echo "#include \"LLGAnalysis.h\"" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "namespace ${1}{" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Define the output variables" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    //int variable1Name;   [example]" >> _${1}.cpp
  echo "}" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "void LLGAnalysis::Setup${1}() {" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Setup the cutflow">> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //_cutFlow.insert(pair<string,double>("CutName", 0) );   [example]'>> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Setup the histograms" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //makeHist( "histogramName", 40, 0., 40., "xlabel", "ylabel" );   [example]' >> _${1}.cpp
  echo '    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Setup the branches" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    //_outputTree->Branch(\"variable1NameInTheTree\", &${1}::variable1Name );  [example]" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Open the passedLogFile" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    _passedLogFile.open( _LogFileName.c_str(), ios::out );' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return;">> _${1}.cpp
  echo "}">> _${1}.cpp
  echo  >> _${1}.cpp
  echo "void LLGAnalysis::${1}Selection() {">> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Write your analysis code here" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Fill the histograms" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //_histograms1D.at("histogram1DName").Fill( var1, evtWeight );         [Example]' >> _${1}.cpp
  echo '    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );   [Example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Apply the cut" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //if( !(CutCondition) ) return;              [Example]' >> _${1}.cpp
  echo '    //_cutFlow.at("CutName") += evtWeight;       [Example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Fill the passedLogFile" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    _passedLogFile << _EventPosition << setw(10) << RunNumber << setw(10) << LumiBlock << setw(10) << EventNumber << endl;' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Fill the output tree" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //_outputTree->Fill();' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return;">> _${1}.cpp
  echo "}">> _${1}.cpp
  echo  >> _${1}.cpp
  echo "void LLGAnalysis::Finish${1}() {" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Make efficiency plots" >> _${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return;">> _${1}.cpp
  echo "}">> _${1}.cpp
else
  echo "SOURCE FILE ALREADY EXISTS. NOT CREATING A NEW SOURCE FILE FOR Region ${1}"
fi




if ! grep -q "Setup${1}()" LLGAnalysis.h; then
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void Setup'${1}'();' LLGAnalysis.h
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void '${1}'Selection();' LLGAnalysis.h
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void Finish'${1}'();' LLGAnalysis.h
else
  echo "Setup${1} ALREADY KNOW TO LLGAnalysis.h. LEAVING FILE UNCHANGED"
fi

if ! grep -q "Setup${1}()" LLGAnalysis.cpp; then
  sed -i '/SETUP YOUR SELECTION HERE/ i\    else if( SELECTION == "'${1}'" ) Setup'${1}'();' LLGAnalysis.cpp
  sed -i '/CALL YOUR SELECTION HERE/ i\        if( SELECTION == "'${1}'" ) '${1}'Selection();' LLGAnalysis.cpp
  sed -i '/FINISH YOUR SELECTION HERE/ i\    if( SELECTION == "'${1}'" ) Finish'${1}'();' LLGAnalysis.cpp
else
  echo "Setup${1} ALREADY KNOW TO LLGAnalysis.cpp. LEAVING FILE UNCHANGED"
fi


if ! grep -q "_${1}.o" Makefile; then 
  sed -i 's/ObjectID.o/ObjectID.o _'${1}'.o/' Makefile
else
  echo "_${1}.o ALREADY KNOWN TO Makefile. LEAVING FILE UNCHANGED"
fi




