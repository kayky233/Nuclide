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
/// \file electromagnetic/TestEm11/src/Run.cc
/// \brief Implementation of the Run class
//
// $Id: Run.cc 71376 2013-06-14 07:44:50Z maire $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4ProcessTable.hh"
#include "G4RadioactiveDecay.hh"
#include "G4TwoVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::Run(DetectorConstruction* det)
: G4Run(),
  fDetector(det), fParticle(0), fEkin(0.)
{
  fEdepDetect = fEdepDetect2 = 0.;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::~Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::SetPrimary(G4ParticleDefinition* particle, G4double energy)
{ 
  fParticle = particle;
  fEkin = energy;
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void Run::EndOfRun() 
{
  G4int prec = 5, wid = prec + 2;  
  G4int dfprec = G4cout.precision(prec);
  
  // run condition
  //   
  G4String Particle = fParticle->GetParticleName();    
  G4cout << "\n The run is " << numberOfEvent << " "<< Particle << " of "
         << G4BestUnit(fEkin,"Energy") << " through : ";
          
  G4cout << "\n Detector : Length = " 
         << G4BestUnit(fDetector->GetDetectorLength(),"Length")
         << " Radius = " 
         << G4BestUnit(fDetector->GetDetectorRadius(),"Length")  
         << " Material = " 
         << fDetector->GetDetectorMaterial()->GetName() << G4endl;

  if (numberOfEvent == 0) { G4cout.precision(dfprec);   return;}
  
  G4cout.precision(dfprec);   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
