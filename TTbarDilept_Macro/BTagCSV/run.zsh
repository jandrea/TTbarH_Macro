#!/bin/env zsh

root -l -b runBTagCSV.C
cd hist
hadd -f bkg.root output_TT.root output_TTW.root output_TTZ.root output_TbarsChan.root \
output_TbartChan.root output_TbartW.root output_TsChan.root output_TtChan.root \
output_TtW.root output_WW.root output_WZ.root output_Wjets.root output_ZZ.root \
output_Zjets.root
cp output_tZq.root sig.root
cd ..

