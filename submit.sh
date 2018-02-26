#!/bin/sh

#each job will be run as ./run.exe <job#> <njobs> <otherParamtersString>
MainCFile="run.C"
inputFiles="fileList.txt ppRef_Feb26_Pythia.root trkCorr_Hydjet_Feb6.root"
njobs=50
otherParameters="fileList.txt 56"


#do not edit anything below unless you know what you are doing
g++ $MainCFile $(root-config --cflags --libs) -Wall -O2 -o "run.exe"

#grid certificate
#gets unique user ID for this system, change to your own
#userID=$(quota -u $USER | grep uid | sed 's/.*uid //' | cut -d')' -f1) 
#echo $userID
voms-proxy-init -voms cms
cp /tmp/x509up_u2150 .

#make a tar of all needed input files
tar -zcvf inputs.tar.gz x509up_u2150 run.exe $inputFiles 
rm  x509up_u2150 

#make subdir
subdir="CondorJob__$(date +"%Y_%m_%d__%H_%M_%S")"
mkdir $subdir
mkdir $subdir/Logs
echo $PWD/$subdir

#copy stuff into subdir

mv inputs.tar.gz $subdir/
cp run.exe run.sh $inputFiles $subdir/
cp fileListTest.txt $subdir/

#change submit file to pick up subdir
cat submit_template.condor | sed "s@SED_PWDHERE@$PWD/$subdir@g" | sed "s@SED_njobs@$njobs@g" | sed "s@SED_otherParams@$otherParameters@g" > $subdir/run.condor 

cat $subdir/run.condor
