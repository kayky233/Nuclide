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
/// \file electromagnetic/TestEm1/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
// $Id: EventAction.cc 76293 2013-11-08 13:11:23Z gcosmo $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
#include "G4Event.hh"
#include "RunAction.hh"

#include "Run.hh"
#include "HistoManager.hh"
#include <fstream>
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction*tRun)
:G4UserEventAction(),theRun(tRun),
 fEdep1(0.) ,TESTNUM(0)
{ } 
double EventAction::GaussRand()
{
    static double v1, v2, mys;
    static int phase  = 0;
    double x;

    if (0 == phase)
    {
        do 
        {
            double u1 = (double)rand()/RAND_MAX;
            double u2 = (double)rand()/RAND_MAX;

            v1 = 2 * u1 - 1;
            v2 = 2 * u2 - 1;
            mys = v1 * v1 + v2 * v2;
        } while ( 1 <= mys || 0 == mys);
        x = v1 * sqrt(-2 * log(mys) / mys);
    }
    else
    {
        x = v2 * sqrt(-2 * log(mys) / mys);
    }
    phase = 1 - phase;

    return x; 
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep1 = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::AddEdep( G4double edep)
{


  
   fEdep1 += edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*aEvent)
{
fstream dataFile1,dataFile2;

//dataFile.open("gamma11.dat",ios::app|ios::out);dataFile1.open("detspec090522.dat",ios::app|ios::out);dataFile1.open("lalaspec.dat",ios::app|ios::out);
G4double enso=11.7;
dataFile1.open("cs137-csi-full-myCsI.dat",ios::app|ios::out);
//	G4double sigma=sqrt(0.0001528*fEdep1*fEdep1+2.915*fEdep1+44.68)/2.35482;
	//G4double sigma=sqrt(0.00005987*fEdep1*fEdep1+0.51094465*fEdep1)/2.35482;
//	G4double sigma=sqrt(3.43*fEdep1+30)/2.35482;
	//G4double sigma=sqrt(0.0001084*fEdep1*fEdep1+2.952*fEdep1+48.23)/2.35482;
	//G4double depositenergy=GaussRand()*sigma+fEdep1;
	G4int depositenergy=floor(GaussRand()*enso*sqrt(661.65*fEdep1)/2.35482/100+fEdep1);
	if (depositenergy>15&&depositenergy<2048)
	{
	dataFile1<<depositenergy<<endl;
	//dataFile1<<int((depositenergy-12.19)/1.021)<<endl;
	//dataFile1<<int((depositenergy-4.899)/1.098)<<endl;
//	 	dataFile1<<depositenergy<<endl;
	}

G4int eventID= aEvent->GetEventID();
if (eventID%100000==0) G4cout<<" Now run out of "<< eventID<<endl;	

}//{
//	for (int i=0;i<1024;i++)	dataFile1<<Spectrum[i]<<endl;
//}
//G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

 // pulse height in detector
 //   
/* if (fEdep2 > 0.) {
   fWeight2 /= fEdep2;
   analysisManager->FillH1(1, fEdep2, fWeight2);
 }
*/   
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


