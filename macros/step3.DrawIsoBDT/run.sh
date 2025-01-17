#!/usr/bin/env sh
tmpjson="hi.json"
for phoEtaIdx in {0..1}; do
    echo processing to photon eta $phoEtaIdx
for jetEtaIdx in {0..2}; do
for phoPtBin in {0..20}; do


cat > $tmpjson <<EOF
{
    "phoEtaBin": $phoEtaIdx,
    "jetEtaBin": $jetEtaIdx,
    "phoPtBin":  $phoPtBin,
    "rebinOption":1,
    "data":"../makehisto_data.root",
    "bkg": "../makehisto_QCD.root",
    "sig": "../makehisto_sig.root",
    "out_template": "disabled"
}
EOF

root -b > logs/job_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin}  <<EOF
.L Draw_IsovsBDT.C+
Draw_IsovsBDT("$tmpjson")
EOF
done; done; done

/bin/rm $tmpjson
hadd -f isovsbdt_template.root iso_*.root
/bin/rm  iso_*.root
