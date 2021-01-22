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
/// \file hadronic/Hadr03/Hadr03.cc
/// \brief Main program of the hadronic/Hadr03 example
//
//
// $Id: rdecay02.cc 88647 2015-03-03 11:06:49Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"

#ifdef G4VIS_USE
 #include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#include "FTFP_BERT.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
int main(int argc,char** argv) {
#ifdef G4UI_USE
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
#endif 
  //choose the Random engine
//  G4Random::setTheEngine(new CLHEP::RanecuEngine);
//ooooooooooooooRandomize the Runoooooooooooooooooooooooo//

CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
time_t systime =time(NULL);
G4long seed=(long)systime;
G4Random::setTheSeed(seed);
G4cout<<seed<<"______________"<<G4endl;

//*******************************************************//

  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4RunManager* runManager = new G4RunManager;
  G4int nThreads = G4Threading::G4GetNumberOfCores();
  if (argc==3) nThreads = G4UIcommand::ConvertToInt(argv[2]);
  //runManager->SetNumberOfThreads(1);
  runManager->SetNumberOfThreads(nThreads);
#else
  //my Verbose output class
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);
  G4RunManager* runManager = new G4RunManager;
#endif

//  G4RunManager* runManager = new G4RunManager;
  // set mandatory initialization classes
  DetectorConstruction* det= new DetectorConstruction;
  runManager->SetUserInitialization(det);
  // 先不做物理定义
 //  PhysicsList* phys = new PhysicsList;
  // 自己定义physiclist
  auto phys = new FTFP_BERT;
  //G4VModularPhysicsList* phys=factory.GetReferencePhysList(“”);
  runManager->SetUserInitialization(phys);
  
  runManager->SetUserInitialization(new ActionInitialization(det));    
     #ifdef G4VIS_USE
  // Visualization manager construction
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif


  // get the pointer to the User Interface manager 
    G4UImanager* UI = G4UImanager::GetUIpointer();  

  if ( argc != 1 ) {
    // execute an argument macro file if exist
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);
	G4cout<<"complete!"<<G4endl;
  }
  else {
#ifdef G4UI_USE
#ifdef G4VIS_USE
    UI->ApplyCommand("/control/execute init_vis.mac"); 
#else
   // UI->ApplyCommand("/control/execute init.mac"); 
#endif
    //if (ui->IsGUI()) {
  //       UI->ApplyCommand("/control/execute gui.mac");
    }     
    // start interactive session
    ui->SessionStart();
    // 先不delete ui，保留
    delete ui;
#endif
  }
//
//
/*  if (argc!=1)   // batch mode  
    {
     G4String command = "/control/execute ";
     //G4String fileName = argv[1];
     G4String fileName = "vis.mac";
     UI->ApplyCommand(command+fileName);
    }
    
  else           //define visualization and UI terminal for interactive mode
    { 
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
      UI->ApplyCommand("/control/execute init_vis.mac"); 

#endif    
     
#ifdef G4UI_USE
     G4UIExecutive * ui = new G4UIExecutive(argc,argv);      
     ui->SessionStart()i;
     delete ui;
#endif
//
*/          
#ifdef G4VIS_USE 
     delete visManager;
#endif     
  // job termination 
  //
   delete runManager;

  // return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
