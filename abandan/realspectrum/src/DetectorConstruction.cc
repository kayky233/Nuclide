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
/// \file hadronic/Hadr03/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// $Id: DetectorConstruction.cc 70755 2013-06-05 12:17:48Z ihrivnac $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4UserLimits.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fAlcaseMater(0), fLogicAlCase(0),fLogicAlCaseendcap(0),
 fDetectorMater(0), fLogicDetector(0), 
 fWorldMater(0), fPhysiWorld(0),
 fDetectorMessenger(0)
{
  //fTargetLength      = 1*cm; 
  //fTargetRadius      = 0.5*cm;
//total length is 18cm
  fDetectorLength    = 18.*cm; 
  fDetectorRadius    = 7./2*cm;//total geometry
  fAlcaseThickness   = 5.*mm;
  fAlcaseRadius      = 35.*mm;
	//AlCase's length is equal to detector and it packs the crystall just right
  //fWorldLength = std::max(fTargetLength,fDetectorLength);
  fWorldLength = fDetectorLength+fAlcaseThickness*2+5*cm;
  fWorldRadius = fDetectorRadius + 10.*mm;//10mm is extended
      
  DefineMaterials();
    
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
// build materials
//
//  fDetectorMater = new G4Material("Germanium", 32, 72.61*g/mole, 5.323*g/cm3);
//Elements
G4double a,z,density;
G4int  ncomponents,natoms;
G4Element* Tl = new G4Element("Thallium", "Tl", z=81., a=204.383*g/mole);
G4Element* C = new G4Element("Carbon", "C", z=6., a=12.01*g/mole);
G4Element* H = new G4Element("Hydrogen", "H", z=1., a=1.01*g/mole);
G4Element* La = new G4Element("Lanthanum", "La", z=57.,a=138.90547*g/mole);
G4Element* Br = new G4Element("Bromium", "Br", z=35., a=79.904*g/mole);
G4Element* Ce = new G4Element("Cerium", "Tl", z=58., a=140.116*g/mole);
G4Element* F = new G4Element("Fluorine", "F", z=9., a=18.9984*g/mole);
G4Element*elNa= new G4Element("Sodium"  ,"elNa", z=11., a= 22.98977*g/mole);
G4Element* elI = new G4Element("Iodine" ,"elI", z=53., a= 126.90447*g/mole);
G4Element* elCs = new G4Element("Cesium","elCs",z=55., a= 132.905*g/mole);
G4Element *elS=  new G4Element("Sulfur", "S", z=16. , a=32.0661*g/mole);
G4Element *elBa=  new G4Element("Barium", "Ba", z=56. , a=137.327*g/mole);
G4Element* elSi = new G4Element("Silicon" , "Si", z=14., a= 28.09*g/mole);
G4Element* elY  = new G4Element("Yttrium" , "Y" , z=39., a= 88.91*g/mole);
G4Element* elLu = new G4Element("Lutetium", "Lu", z=71., a= 175.0*g/mole);

G4NistManager* man = G4NistManager::Instance();  
//Air
G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
Fe = man->FindOrBuildMaterial("G4_Fe");
Glass = man->FindOrBuildMaterial("G4_Pyrex_Glass");
G4Material* Si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
G4Material* Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
G4Material* Pb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
G4Material* CsI = G4NistManager::Instance()->FindOrBuildMaterial("G4_CESIUM_IODIDE");
//LaBr3
G4Material* LaBr3 = new G4Material("LaBr3", density = 5.07*g/cm3, ncomponents=2);
LaBr3->AddElement(La, natoms=1);
LaBr3->AddElement(Br, natoms=3);

//LaBr3_Ce
G4Material* LaBr3_Ce = new G4Material("LaBr3_Ce", density = 5.08*g/cm3, ncomponents=2);
LaBr3_Ce->AddMaterial(LaBr3, 99.5*perCent);
LaBr3_Ce->AddElement(Ce, 0.5*perCent);

G4Element* N  = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
G4Element* O  = new G4Element("Oxygen",   "O", 8, 16.00*g/mole);
//
G4double fractionmass;      
G4Material* Air20 = new G4Material("Air", 1.205*mg/cm3, ncomponents=2,
kStateGas, 293.*kelvin, 1.*atmosphere);
Air20->AddElement(N, fractionmass=0.7);
Air20->AddElement(O, fractionmass=0.3);
//
G4double density1 = 0.001*g/cm3; G4double a1 = 14.007*g/mole;
vacuum = new G4Material ("vacuum", z=7., a1 , density1); 
//fWorldMater = Air20;
//
G4Material* myCsI = new G4Material("myCsI", density = 4.51*g/cm3, ncomponents=2);
myCsI->AddElement(elI, natoms=1);
myCsI->AddElement(elCs, natoms=1);


//
G4Material* LYSO = new G4Material("LYSO", density= 7.15*g/cm3, ncomponents=4);  //LYSO,Lutetium Yttrium Orthosilicate     
LYSO->AddElement(O ,  natoms=5);
LYSO->AddElement(elSi,  natoms=1);
LYSO->AddElement(elLu,  natoms=1.8);
LYSO->AddElement(elY,   natoms=0.2);
//
//GAGG Define
G4Element* elGd = new G4Element("Gadolinium", "Gd" , z= 64., a= 157.252*g/mole);
G4Element* elAl  = new G4Element("Aluminium"  , "Al" , z= 13., a=26.9815*g/mole);
G4Element* elGa  = new G4Element("Gallium"  , "Ga" , z= 74., a= 183.85*g/mole);
GAGG = new G4Material("GAGG", density=6.63*g/cm3, ncomponents=4); //GAGG 6.63g/cm3 
GAGG->AddElement(elGd ,natoms=3 );    
GAGG->AddElement(elAl ,natoms=2 );
GAGG->AddElement(elGa ,natoms=3 );
GAGG->AddElement(O ,natoms=12 );

   
//NaI = new G4Material("NaI", 3.67*g/cm3, ncomponents=2);
//NaI->AddElement(elNa, natoms=1);
//NaI->AddElement(elI, natoms=1);  
BaSO4 = new G4Material("BaSO4", density= 4.5*g/cm3, ncomponents=3);
BaSO4->AddElement(elBa ,  natoms=1);
BaSO4->AddElement(elS ,  natoms=1);
BaSO4->AddElement(O ,  natoms=4);

fAlcaseMater=Al; 
fShieldMater=Fe; 
// or use G4 materials data base
//
//  fTargetMater = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
fWorldMater = Air;
 fDetectorMater =CsI;// NaI;//GAGG;///GAGG;//LYSO;//  NaI;//   GAGG ;            

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
G4VisAttributes* transgrey=new G4VisAttributes(G4Colour(0.64,0.7,0.7,0.5));
transgrey->SetForceSolid(true);
G4VisAttributes* transblue=new G4VisAttributes(G4Colour(0.01,0.98,0.9,0.3));
transblue->SetForceSolid(true);
G4VisAttributes* transyellow=new G4VisAttributes(G4Colour(0.8,0.9,0.1,0.9));
transblue->SetForceSolid(true);
G4VisAttributes* transgreen=new G4VisAttributes(G4Colour(0.2,0.98,0.1,0.9));
transblue->SetForceSolid(true);
// define the basic pixel unit of crystal
G4double halfcrystal=3.*mm;
                                       
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  // World
  //
  // (re) compute World dimensions if necessary
 // fWorldLength = fDetectorLength+fAlcaseThickness*2+worldextend;
  //fWorldRadius = fTargetRadius + fDetectorThickness;
    
  G4Tubs*
  sWorld = new G4Tubs("World",                                 //name
                 0.,fWorldRadius, 0.5*fWorldLength, 0.,twopi); //dimensions  
                   
  G4LogicalVolume*
  lWorld = new G4LogicalVolume(sWorld,                  //shape
                             fWorldMater,               //material
                             "World");                  //name

  fPhysiWorld = new G4PVPlacement(0,                    //no rotation
                            G4ThreeVector(),            //at (0,0,0)
                            lWorld,                     //logical volume
                            "World",                    //name
                            0,                          //mother volume
                            false,                      //no boolean operation
                            0);                         //copy number
  // Detector
  //
  G4Tubs* 
  sDetector = new G4Tubs("Detector",  
                fDetectorRadius-3*mm,  fDetectorRadius, 0.5*fDetectorLength, 0.,twopi);


  fLogicDetector = new G4LogicalVolume(sDetector,       //shape
                             fShieldMater,            //material
                             "Detector");               //name
                               
           new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0,0,0),             //at (0,0,0)
                           fLogicDetector,              //logical volume
                           "Detector",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number

//vacuum room
G4Tubs* 
  stube = new G4Tubs("stube",  
                0, fDetectorRadius-5*mm, 0.5*12*cm, 0.,twopi);


  fLogictube = new G4LogicalVolume(stube,       //shape
                             vacuum,            //material
                             "ltube");               //name
                               
   /*        new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0,0,-2.2*cm),             //at (0,0,0)
                           fLogictube,              //logical volume
                           "ltube",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number

*/
  // Glass window
  //
  G4Tubs* 
  sGlass = new G4Tubs("AlCase",  
               0,  fDetectorRadius-5*mm, 2.*mm/2, 0.,twopi);


  fLogicGlass = new G4LogicalVolume(sGlass,       //shape
                             Fe,            //glass material
                             "glass");               //name
                               
           new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0,0,4*cm-1*mm),             //at (0,0,0)
                           fLogicGlass ,              //logical volume
                           "glassplace",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number


  G4Box* 
  scontainer = new G4Box("scontainer3",  
               halfcrystal,halfcrystal,halfcrystal);

fLogicCrystal= new G4LogicalVolume(scontainer,       //shape
                            fDetectorMater ,            //glass material
                             "flcontainer3");               //name
  

         new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0,0,5*cm),             //at (0,0,0)
                          fLogicCrystal,              //logical volume
                           "container3place",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                          0);                          //copy number







  G4Tubs*   sAlCaseendcap = new G4Tubs("AlCaseendcap",0, fDetectorRadius-5*mm,fAlcaseThickness/2 ,0.,twopi);
  G4Tubs*   sAlCaseendcapr = new G4Tubs("AlCaseendcapr",0, fDetectorRadius-5*mm,1*mm ,0.,twopi);


  fLogicAlCaseendcap= new G4LogicalVolume(sAlCaseendcap,       //shape
                             fAlcaseMater,            //material
                             "AlCaseendcap");               //name
   fLogicAlCaseendcapr= new G4LogicalVolume(sAlCaseendcapr,       //shape
                             Fe,            //material
                             "AlCaseendcap");               //name
                            
           new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0,0,-0.5*fDetectorLength-fAlcaseThickness/2 )        , 
                           fLogicAlCaseendcap ,              //logical volume
                           "AlCaseendcap",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number
           new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0,0,7.0*cm),//0.5*fDetectorLength+0.1*mm-2*cm )         ,
                           fLogicAlCaseendcapr ,              //logical volume
                           "AlCaseendcap",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           1);                          //copy number

//source geometry
double halfsource=2*mm;
  G4Sphere* 
  ssource = new G4Sphere("ssource",  
               0*mm,6.*mm,0*deg,360*deg,0*deg,180*deg);


 //fLogicsource = new G4LogicalVolume(ssource,Fe,"lsource");        
  fLogicsource = new G4LogicalVolume(ssource,fAlcaseMater,"lsource");        
        

    new G4PVPlacement(0,                         //no rotation
                           G4ThreeVector(0.,0.,6*cm),             //at (0,0,0)
                           fLogicsource ,              //logical volume
                           "sourceplace",                  //name
                           lWorld,                      //mother  volume
                           false,                       //no boolean operation
                           0);                          //copy number


 // PrintParameters();
  fLogicDetector->SetVisAttributes(transgrey);
/*  fLogicsource->SetVisAttributes(transgrey);
  fLogicAlCaseendcap->SetVisAttributes(transgrey);
  fLogicAlCaseendcapr->SetVisAttributes(transgrey);
  fLogicGlass->SetVisAttributes(transgreen);
  fLogictube->SetVisAttributes(transblue);
  fLogicbaso4->SetVisAttributes(transblue);
  fLogicCrystal->SetVisAttributes(transyellow);
*/
//  fLogicCrystal->SetVisAttributes(transyellow);
  //always return the root volume
  //
  //
  
fLogicCrystal->SetUserLimits(new G4UserLimits(0.01*um));

  return fPhysiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintParameters()
{
  G4cout << "\n Detector : Length = " << G4BestUnit(fDetectorLength,"Length")
         << " Tickness = " << G4BestUnit(fDetectorRadius,"Length")  
         << " Material = " << fDetectorMater->GetName() << G4endl;          
  G4cout << "\n"  << fDetectorMater << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fDetectorMater = pttoMaterial;
    if(fLogicDetector) { fLogicDetector->SetMaterial(fDetectorMater); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetDetectorMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorRadius(G4double value)
{
  fDetectorRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorLength(G4double value)
{
  fDetectorLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorLength()
{
  return fDetectorLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorRadius()
{
  return fDetectorRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::GetDetectorMaterial()
{
  return fDetectorMater;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicDetector()
{

//return  fLogiccontainer3 ;
return  fLogicDetector ;
//return fLogicCrystalO;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
