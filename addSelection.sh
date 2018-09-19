#!/bin/bash

if [ ! -e cutflow${1}.cpp ]; then 
  echo "#include \"LLGAnalysis.h\"" >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "namespace ${1}{" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Define the output variables" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    //int variable1Name;   [example]" >> cutflow${1}.cpp
  echo "}" >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "void LLGAnalysis::Setup${1}() {" >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Setup the cutflow">> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //_cutFlow.insert(pair<string,double>("CutName", 0) );   [example]'>> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Setup the histograms" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //makeHist( "histogramName", 40, 0., 40., "xlabel", "ylabel" );   [example]' >> cutflow${1}.cpp
  echo '    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Setup the branches" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    //_outputTree->Branch(\"variable1NameInTheTree\", &${1}::variable1Name );  [example]" >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Open the passedLogFile" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //_passedLogFile.open( _LogFileName.c_str(), ios::out );' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    return;">> cutflow${1}.cpp
  echo "}">> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "void LLGAnalysis::${1}Selection() {">> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Write your analysis code here" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Fill the histograms" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //_histograms1D.at("histogram1DName").Fill( var1, evtWeight );         [Example]' >> cutflow${1}.cpp
  echo '    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );   [Example]' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Apply the cut" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //if( !(CutCondition) ) return;              [Example]' >> cutflow${1}.cpp
  echo '    //_cutFlow.at("CutName") += evtWeight;       [Example]' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Fill the passedLogFile" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //_passedLogFile << _EventPosition << setw(10) << RunNumber << setw(10) << LumiBlock << setw(10) << EventNumber << endl;' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Fill the output tree" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //_outputTree->Fill();' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    return;">> cutflow${1}.cpp
  echo "}">> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "void LLGAnalysis::Finish${1}() {" >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo "    // Make efficiency plots" >> cutflow${1}.cpp
  echo "    //--------------------------------------------------------------------------" >> cutflow${1}.cpp
  echo '    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]' >> cutflow${1}.cpp
  echo  >> cutflow${1}.cpp
  echo "    return;">> cutflow${1}.cpp
  echo "}">> cutflow${1}.cpp
else
  echo "SOURCE FILE ALREADY EXISTS. NOT CREATING A NEW SOURCE FILE FOR Region ${1}"
fi




if ! grep -q "Setup${1}()" LLGAnalysis.h; then
  sed -ie '/INSERT YOUR SELECTION HERE/ i\        void Setup'${1}'();' LLGAnalysis.h
  sed -ie '/INSERT YOUR SELECTION HERE/ i\        void '${1}'Selection();' LLGAnalysis.h
  sed -ie '/INSERT YOUR SELECTION HERE/ i\        void Finish'${1}'();' LLGAnalysis.h
else
  echo "Setup${1} ALREADY KNOW TO LLGAnalysis.h. LEAVING FILE UNCHANGED"
fi

if ! grep -q "Setup${1}()" LLGAnalysis.cpp; then
  sed -ie '/SETUP YOUR SELECTION HERE/ i\    else if( SELECTION == "'${1}'" ) Setup'${1}'();' LLGAnalysis.cpp
  sed -ie '/CALL YOUR SELECTION HERE/ i\        if( SELECTION == "'${1}'" ) '${1}'Selection();' LLGAnalysis.cpp
  sed -ie '/FINISH YOUR SELECTION HERE/ i\    if( SELECTION == "'${1}'" ) Finish'${1}'();' LLGAnalysis.cpp
else
  echo "Setup${1} ALREADY KNOW TO LLGAnalysis.cpp. LEAVING FILE UNCHANGED"
fi


if ! grep -q "cutflow${1}.o" Makefile; then 
  sed -ie 's/ObjectID.o/ObjectID.o cutflow'${1}'.o/' Makefile
else
  echo "cutflow${1}.o ALREADY KNOWN TO Makefile. LEAVING FILE UNCHANGED"
fi

mkdir ${1}


