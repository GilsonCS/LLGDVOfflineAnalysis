#!/bin/bash

if grep -q "Setup${1}()" LLGAnalysis.h; then
  sed -i '/void Setup'${1}'();/d' LLGAnalysis.h
  sed -i '/void '${1}'Selection();/d' LLGAnalysis.h
  sed -i '/void Finish'${1}'();/d' LLGAnalysis.h
else
  echo "Setup${1} DOESN'T EXIST IN LLGAnalysis.h. LEAVING FILE UNCHANGED"
fi

if grep -q "Setup${1}()" LLGAnalysis.cpp; then
  sed -i '/if( SELECTION == "'${1}'" ) Setup'${1}'();/d' LLGAnalysis.cpp
  sed -i '/if( SELECTION == "'${1}'" ) '${1}'Selection();/d' LLGAnalysis.cpp
  sed -i '/if( SELECTION == "'${1}'" ) Finish'${1}'();/d' LLGAnalysis.cpp
else
  echo "Setup${1} DOESN'T EXIST IN LLGAnalysis.cpp. LEAVING FILE UNCHANGED"
fi


if grep -q "_${1}.o" Makefile; then 
  sed -i 's/ _'${1}'.o / /' Makefile
else
  echo "_${1}.o DOESN'T EXIST IN Makefile. LEAVING FILE UNCHANGED"
fi

rm _${1}.o