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
/// \file hadronic/Hadr03/src/SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
// $Id: SteppingAction.cc 71404 2013-06-14 16:56:38Z maire $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4Alpha.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <typeinfo>
using namespace std;                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
G4Track* theTrack = aStep->GetTrack();                                      //获取径迹
//G4ParticleDefinition* particleType = theTrack->GetDefinition();   
//G4int parentid =  theTrack->GetParentID();
//if(particleType == G4Gamma::GammaDefinition()&&parentid<5)                               //


G4String particlename=aStep->GetTrack()->GetDefinition()->GetParticleName() ;
//G4cout<<"aaaa "<<aStep->GetTrack()->GetDefinition()->GetParticleName()<<G4endl ;
//if(particlename =="Pt192"||particlename =="Os192")
//if(particlename =="Th229")
//{theTrack->SetTrackStatus(fStopAndKill);}                               //
//G4cout<<"aaaa "<<aStep->GetTrack()->GetDefinition()->GetParticleName()<<G4endl ;
//{G4cout<<"Hello World!"<<G4endl;}
//G4cout<<"aaaa "<<typeid(aStep->GetTrack()->GetDefinition()->GetParticleName()).name()<<G4endl ;
/*
  G4Track* theTrack = aStep->GetTrack();                          		//获取径迹
 	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector steppos;steppos=preStepPoint->GetPosition();
if(steppos.z()>0.01) theTrack->SetTrackStatus(fStopAndKill);
*/

  

  //which volume ?
  //
  G4LogicalVolume* lVolume = aStep->GetPreStepPoint()->GetTouchableHandle()
                             ->GetVolume()->GetLogicalVolume();
  //if (lVolume == fDetector->GetLogicDetector()) iVol = 1;

  const G4StepPoint* prePoint = aStep->GetPreStepPoint();
 G4String matname=prePoint->GetMaterial()->GetName(); 
 
  if (matname == "G4_CESIUM_IODIDE")

{


 // energy deposit
  //
  G4double edepStep = aStep->GetTotalEnergyDeposit()/keV;
  if (edepStep <= 0.) return;
  fEventAction->AddEdep( edepStep);
}  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
