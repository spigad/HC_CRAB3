{
// based on a style file from BaBar
//

cout << "Welcome!" << endl;
gStyle->SetPalette(1);
gStyle->SetOptTitle(0);
gStyle->SetOptStat(111111);
gStyle->SetOptStat(0);
gStyle->SetOptFit(111111);
gStyle->SetOptFit(0);


//..BABAR style from RooLogon.C in workdir
TStyle *atlasStyle= new TStyle("ATLAS","Atlas style");

// use plain black on white colors
 Int_t icol=0;
atlasStyle->SetFrameBorderMode(icol);
atlasStyle->SetCanvasBorderMode(icol);
atlasStyle->SetPadBorderMode(icol);
atlasStyle->SetPadColor(icol);
atlasStyle->SetCanvasColor(icol);
atlasStyle->SetStatColor(icol);
//atlasStyle->SetFillColor(icol);

// set the paper & margin sizes
atlasStyle->SetPaperSize(20,26);
atlasStyle->SetPadTopMargin(0.05);
//atlasStyle->SetPadRightMargin(0.05);
atlasStyle->SetPadRightMargin(0.16);
atlasStyle->SetPadBottomMargin(0.16);
atlasStyle->SetPadLeftMargin(0.12);

// use large fonts
//Int_t font=72;
Int_t font=42;
Double_t tsize=0.05;
atlasStyle->SetTextFont(font);


atlasStyle->SetTextSize(tsize);
atlasStyle->SetLabelFont(font,"x");
atlasStyle->SetTitleFont(font,"x");
atlasStyle->SetLabelFont(font,"y");
atlasStyle->SetTitleFont(font,"y");
atlasStyle->SetLabelFont(font,"z");
atlasStyle->SetTitleFont(font,"z");

atlasStyle->SetLabelSize(tsize,"x");
atlasStyle->SetTitleSize(tsize,"x");
atlasStyle->SetLabelSize(tsize,"y");
atlasStyle->SetTitleSize(tsize,"y");
atlasStyle->SetLabelSize(tsize,"z");
atlasStyle->SetTitleSize(tsize,"z");


//use bold lines and markers
atlasStyle->SetMarkerStyle(20);
atlasStyle->SetMarkerSize(1.2);
atlasStyle->SetHistLineWidth(2.);
atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

//get rid of X error bars and y error bar caps
//atlasStyle->SetErrorX(0.001);

//do not display any of the standard histogram decorations
atlasStyle->SetOptTitle(0);
atlasStyle->SetOptStat(111111);
atlasStyle->SetOptStat(0);
atlasStyle->SetOptStat(1);
atlasStyle->SetOptFit(111111);
atlasStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
atlasStyle->SetPadTickX(1);
atlasStyle->SetPadTickY(1);
atlasStyle->SetPalette(1);
// gROOT->SetStyle("Plain");
gROOT->SetStyle("ATLAS");

//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);
// gStyle->SetOptTitle(0);
// // gStyle->SetFillColor(0);
// // gStyle->SetCanvasColor(0);
// // gStyle->SetPadColor(0);
// gStyle->SetCanvasDefH(600);
// gStyle->SetCanvasDefW(600);
// gStyle->SetTextFont(12);
// gStyle->SetLabelFont(12, "xyz");
// gStyle->SetTitleFont(12,"xyz");
// gStyle->SetStatX(0.9);
// gStyle->SetStatY(0.9);
// gStyle->SetStatBorderSize(1);
// gStyle->SetCanvasBorderSize(1);
// gStyle->SetPadBorderSize(1);
// gStyle->SetTitleOffset(1.2,"y");
// gStyle->SetStatFont(12);
// gStyle->SetOptStat("emruo");
}
