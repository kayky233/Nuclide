//#ifndef _ _CINT_ _
//#include "RooGlobalFunc.h"
//#endif
//#include "RooRealVar.h"
//#include "RooDataSet.h"
//#include "RooGaussian.h"
//#include "RooBreitWigner.h"
//#include "RooPolynomial.h"
//#include "RooAddPdf.h"
//#include "RooFitResult.h"
//#include "RooRealIntegral.h"
#include "TCanvas.h"
//#include "RooPlot.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "THStack.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TF2.h"
#include "TF1.h"
#include "iostream"
#include "fstream"
//#include "RooCBShape.h"
#include "TMath.h"
//#include "RooFit.h"
//#include "RooMath.h"
// using namespace RooFit;
 using namespace std;

 //void txt(Double_t x0=0.3,Double_t y0=0.3,TString txts="",Int_t iColor=2,Double_t fSize=0.06,Bool_t IsNDC=kTRUE);
 void txt(Double_t x0=0.3,Double_t y0=0.3,TString txts="",Int_t iColor=2,Double_t fSize=0.04,Bool_t IsNDC=kTRUE);


//void readdat( char* filename="cs137csi.dat"){
//void readdat( char* filename="cs137-csi-ele.dat"){
void readdat( char* filename="cs137-csi-full-myCsI.dat"){
//void readdat( char* filename="cs137-csi-full.dat"){
//void readdat( char* filename="cs137-full-csi-002mm.dat"){
//void readdat( char* filename="cs137-cs-i-002mm.dat"){
	TH1F *spec;
//	 spec = new TH1F("Geant4 Co60","Geant4 Co60",2048,0,2048);
	 spec = new TH1F("Geant4 Cs137","Geant4 Cs137",2048,0,2048);
//	 spec = new TH1F("Geant4 Na22","Geant4 Na22",2048,0,2048);
	 //spec = new TH1F("Geant4 Ba133","Geant4 Ba133",2048,0,2048);
	ofstream fout,fmix;
	fstream fin;int tempdata;
//TFile outputFile ("Geant4-Ba133.root","RECREATE");
//	fout.open("det9.dat",ios_base::out);
	fin.open(filename,ios_base::in);
	//fin.open("detsmall3.dat",ios_base::in);
while (!fin.eof()){

		fin>>tempdata;
		
if(tempdata>0&&tempdata<2048)			spec->AddBinContent(tempdata);
	//	cout<<"careful! ***** file out is "<<tempdata<<endl;
		}



for(int i=1;i<13;i++)
{
spec->SetBinContent(i,0);


}	

//
spec->SetFillColor(kRed);
spec->SetYTitle("");
//spec->SetYTitle("Counts");
spec->SetXTitle("Channel");
spec->SetLineColor(kRed);

//spec->Write();
//TCanvas*myc=new TCanvas("myc","myc",1200,400);

//spec.Draw();
//spec->Draw();
//myc->Print(Form("Background-sec9670.png"));
 TFile*  inputFile = TFile::Open("mytotalspecsubbackuniform.root");
 //TFile*  inputFile = TFile::Open("myoutbackgroundsec.root");
 TH1F *hh[4];
 hh[0]=new TH1F();
// hh[0]=(TH1F *)inputFile->Get("Na22-TC");
hh[0]=(TH1F *)inputFile->Get("Cs137-TC");
//hh[0]=(TH1F *)inputFile->Get("Co60-TC");
 //hh[0]=(TH1F *)inputFile->Get("Ba133-TC");
 //hh[0]->Add(hh[1],-1);

hh[0]->SetYTitle("");
 TCanvas*myc=new TCanvas("myc","myc",1200,400);
 myc->Divide(1,2);
 myc->cd(1);hh[0]->Draw();
 myc->cd(2);spec->Draw();

double sum511=0,sum511exp=0;
for(int ch1=400;ch1<550;ch1++){	sum511=sum511+spec->GetBinContent(ch1);	sum511exp=sum511exp+hh[0]->GetBinContent(ch1);	}
double sumex=0,sumg4=0;
for(int ch1=550;ch1<800;ch1++){	sumg4=sumg4+spec->GetBinContent(ch1);sumex=sumex+hh[0]->GetBinContent(ch1);		}
//cout<<"sum1274exp/sum511exp= "<<sum1274exp/sum511exp<<endl;
//cout<<"sum1274/sum511= "<<sum1274/sum511<<endl;

double g4avecompton=0;
double exavecompton=0;

for(int ch1=339;ch1<364;ch1++)
	{
	exavecompton=exavecompton+hh[0]->GetBinContent(ch1)/(384-358);
	}



for(int ch1=358;ch1<383;ch1++)
	{
	g4avecompton=g4avecompton+spec->GetBinContent(ch1)/(383-358);
	}

double maxpeakvalue=0;

for(int ch1=610;ch1<625;ch1++)
	{

//	g4avecompton=g4avecompton+spec->GetBinContent(ch1)/(383-358);
	if (maxpeakvalue<hh[0]->GetBinContent(ch1))
	{   maxpeakvalue=hh[0]->GetBinContent(ch1);}
	}


double exmaxedgevalue=0;
double g4maxedgevalue=0;

for(int ch1=400;ch1<500;ch1++)
	{

//	g4avecompton=g4avecompton+spec->GetBinContent(ch1)/(383-358);
	if (exmaxedgevalue<hh[0]->GetBinContent(ch1))
	{   exmaxedgevalue=hh[0]->GetBinContent(ch1);}
	if (g4maxedgevalue<spec->GetBinContent(ch1))
	{   g4maxedgevalue=spec->GetBinContent(ch1);}


	}

//exmaxedgevalue=hh[0]->GetBinContent(453);

cout<<"Experimental Sum Peak 662keV/Average compton= "<<sumex/exavecompton<<endl;
cout<<"Experimental Peak 662keV/Average compton= "<<maxpeakvalue/exavecompton<<endl;
cout<<"Experimental Sum Peak 662keV/compton edge= "<<sumex/exmaxedgevalue*1.021<<endl;
cout<<"Geant4 simulation Sum Peak 662keV/Average compton= "<<sumg4/g4avecompton<<endl;
cout<<"Geant4 simulation Peak 662keV/Average compton= "<<spec->GetBinContent(662)/g4avecompton<<endl;
cout<<"Geant4 simulation Sum Peak 662keV/compton edge= "<<sumg4/g4maxedgevalue<<endl;

TFile *outputFile=new TFile("CsI-1cm1cm1cm-cs137-full-myCsI.root","RECREATE");
spec->Write();


}
//oooooooooooooooooooooooooooooooooooooooo
void txt(Double_t x0,Double_t y0,TString txts,Int_t iColor,Double_t fSize, Bool_t IsNDC){
        TLatex *ltx  = new TLatex();
        ltx -> SetNDC(IsNDC);
        if(!(x0>=0 &&x0<=1&&y0>=0 &&y0<=1)) ltx -> SetNDC(kFALSE);
        ltx->SetTextColor(iColor);
        ltx->SetTextFont(22);
        ltx->SetTextSize(fSize);
        ltx->DrawLatex(x0,y0,txts.Data());
       // ltx->DrawLatex(x0,y0,txts);
//        ltx->DrawLatex(x0,y0,"Energy resolutoin= #%");
//	cout<<"txt "<<txts.Data()<<endl;
}

