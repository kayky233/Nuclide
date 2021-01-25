//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file hadronic/Hadr03/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
// $Id: RunAction.cc 70756 2013-06-05 12:20:06Z ihrivnac $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Timer.hh"

#include "Randomize.hh"
#include <iomanip>
#include <fstream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim), fRun(0), fHistoManager(0)
{
 // Book predefined histograms
 fHistoManager = new HistoManager(); 
timer=new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
 delete fHistoManager;
 delete timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RunAction::GenerateRun()
{ 
  fRun = new Run(fDetector); 
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*aRun)
{ G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();   
//Spectrum[1024]={0};

  // save Rndm status
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  if (isMaster) G4Random::showEngineStatus();
  
  // keep run condition
  if (fPrimary) { 
    G4ParticleDefinition* particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }
             
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*aRun)
{
timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " and Time runs" << *timer << G4endl;
/*  if (isMaster) fRun->EndOfRun();    
  
  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }
      
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
if(aRun->GetRunID()==0)
{
G4cout<<"啊啊啊啊啊0"<<endl;
	fstream datafile1;
//	datafile1.open("detspec.dat");
datafile1.open("0905detspec.dat",ios::app|ios::out);

for(int i=0;i<2048;i++) datafile1<<Spectrum[i]<<endl;
}	
*/

/*
if(aRun->GetRunID()==1)
{
G4cout<<"啊啊啊啊啊1"<<endl;
	fstream datafile1;
//	datafile1.open("detspec.dat");
datafile1.open("detCo57.dat",ios::app|ios::out);
for(int i=0;i<1024;i++) {tempc=Spectrum[i]-temspec0[i]; datafile1<<tempc<<endl;temspec1[i]=Spectrum[i];}
}
if(aRun->GetRunID()==2)
{
G4cout<<"啊啊啊啊啊2"<<endl;
	fstream datafile1;
//	datafile1.open("detspec.dat");
datafile1.open("detK40.dat",ios::app|ios::out);
for(int i=0;i<1024;i++) {tempc=Spectrum[i]-temspec1[i]; datafile1<<tempc<<endl;temspec2[i]=Spectrum[i];}
}
if(aRun->GetRunID()==3)
{
G4cout<<"啊啊啊啊啊3"<<endl;
	fstream datafile1;
//	datafile1.open("detspec.dat");
datafile1.open("detU238.dat",ios::app|ios::out);
for(int i=0;i<1024;i++) {tempc=Spectrum[i]-temspec2[i]; datafile1<<tempc<<endl;temspec3[i]=Spectrum[i];}
}
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
