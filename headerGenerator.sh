#!/bin/sh
Classname=$1
UpperClassname=$(echo $1 | tr '[a-z]' '[A-Z]')
Header=$(echo "#include " '"'$Classname.hpp'"')
cp class_files_templates/template.cpp src/$Classname.cpp
cp class_files_templates/template.hpp includes/$Classname.hpp

sed -i '' 's/Classname/'$Classname'/g' src/$Classname.cpp

sed -i '' 's/Classname/'$Classname'/g' includes/$Classname.hpp
sed -i '' 's/CLASSNAME/'$UpperClassname'/g' includes/$Classname.hpp

