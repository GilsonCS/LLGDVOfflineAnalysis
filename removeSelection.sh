#!/bin/bash

if grep -q "Setup${1}()" LLGAnalysis.h; then
  sed -ie '/void Setup'${1}'();/d' LLGAnalysis.h
  sed -ie '/void '${1}'Selection();/d' LLGAnalysis.h
  sed -ie '/void Finish'${1}'();/d' LLGAnalysis.h
else
  echo "Setup${1} DOESN'T EXIST IN LLGAnalysis.h. LEAVING FILE UNCHANGED"
fi

if grep -q "Setup${1}()" LLGAnalysis.cpp; then
  sed -ie '/if( SELECTION == "'${1}'" ) Setup'${1}'();/d' LLGAnalysis.cpp
  sed -ie '/if( SELECTION == "'${1}'" ) '${1}'Selection();/d' LLGAnalysis.cpp
  sed -ie '/if( SELECTION == "'${1}'" ) Finish'${1}'();/d' LLGAnalysis.cpp
else
  echo "Setup${1} DOESN'T EXIST IN LLGAnalysis.cpp. LEAVING FILE UNCHANGED"
fi


if grep -q "cutflow${1}.o" Makefile; then 
  sed -ie 's/ cutflow'${1}'.o / /' Makefile
else
  echo "cutflow${1}.o DOESN'T EXIST IN Makefile. LEAVING FILE UNCHANGED"
fi

rm cutflow${1}.o