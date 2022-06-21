#!/usr/bin/env sh
input=$1
mydir=`echo $input | cut -d'.' -f1 | rev | cut -d'/' -f1 | rev`
if [ "$1" == "" ]; then
    echo "you need to input a text file"
    exit
fi

mkdir -p $mydir ; cd $mydir
idx=0
for file in `cat $input`;
do
    #../dev/exe.test.xPhotonRunner $file $idx > log_$1 2>&1
    /home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/bin/exe.xPhotonRunner $file $idx
    #/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/dev/exe.test.xPhotonRunner $file $idx
    #../dev/exe.test.xElectronsRunner $file $idx > log_$1 2>&1
    let "idx=idx+1"
done

hadd ../${mydir}.root *.root