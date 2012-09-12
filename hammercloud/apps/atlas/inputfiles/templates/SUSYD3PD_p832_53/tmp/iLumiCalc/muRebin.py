#!/usr/bin/python

import ROOT
import sys
import time

print 'Example usage: ./muRebin.py ilumicalc_histograms_EF_e20_medium_177682-179804.root avgintperbx'

if len(sys.argv) > 2:
  in_name = sys.argv[1]
  hist_name = sys.argv[2]
  print 'Filename '+in_name
  print 'Histo name '+hist_name  
elif len(sys.argv) > 1:

  in_name = sys.argv[1]
  print 'Filename '+in_name
  print 'No histo name given'
  hist_name = False
else:
  in_name = "data11_7TeV.periodA.root"
  hist_name = "readyMuDist"
  print 'No file or histo name given, using default '+in_name+' '+hist_name


out_name = in_name.split('.')
out_name.insert(-1, "rebinned")
out_name = '.'.join(out_name)

in_file = ROOT.TFile(in_name, "READ")
for key in in_file.GetListOfKeys():
  if not hist_name:
    hist = key.ReadObj()
    break
  if key.GetName() == hist_name:
    hist = key.ReadObj()

hist.Sumw2()
hist.Rebin(10)

out_file = ROOT.TFile(out_name, "RECREATE")
mu_data = ROOT.TH1D("mu_data", "<#mu> Data", 25, 0.0, 25.0)
mu_data.Add(hist)
out_file.Write()
