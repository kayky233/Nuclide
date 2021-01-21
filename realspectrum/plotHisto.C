{
  
 TFile*  inputFile = TFile::Open("mytotalspecsubbackuniform.root");
 //TFile*  inputFile = TFile::Open("myoutbackgroundsec.root");
 TH1F *hh[4];
 hh[0]=new TH1F();
 hh[0]=(TH1F *)inputFile->Get("Na22-TC");
 hh[1]=new TH1F();
 hh[1]=(TH1F *)inputFile->Get("Cs137-TC");

 hh[2]=new TH1F();
 //hh[0]->Add(hh[1],-1);
double sum511=0;
for(int ch1=400;ch1<550;ch1++){	sum511=sum511+hh[0]->GetBinContent(ch1);		}
double sum1274=0;
for(int ch1=1100;ch1<1200;ch1++){	sum1274=sum1274+hh[0]->GetBinContent(ch1);		}
cout<<"sum1274/sum511= "<<sum1274/sum511<<endl;

 TCanvas*myc=new TCanvas("myc","myc",1200,400);
 myc->Divide(1,2);
 myc->cd(1);hh[0]->Draw();
 myc->cd(2);hh[1]->Draw();
/*
gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile f = TFile("rdecay02.root");
  TCanvas* c1 = new TCanvas("c1", "  ");
  
  c1->SetLogy(0);
  c1->cd();
  c1->Update();
  
  ///TH1D* hist1 = (TH1D*)f.Get("H11");
  ///hist1->SetLineColor(kRed); 
  ///hist1->Draw("HIST");
  
  ///TH1D* hist2 = (TH1D*)f.Get("H12");
  ///hist2->Draw("HIST");
     
  ///TH1D* hist3 = (TH1D*)f.Get("H13");
  ///hist3->SetLineColor(kRed);   
  ///hist3->Draw("HIST");
  
  ///TH1D* hist4 = (TH1D*)f.Get("H14");
  ///hist4->Draw("HIST");
  
  ///TH1D* hist5 = (TH1D*)f.Get("H15");
  ///hist5->Draw("HIST");
  
  TH1D* hist6 = (TH1D*)f.Get("H16");
  hist6->Draw("HIST");        */
}  
