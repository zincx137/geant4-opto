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
// 
/// \file B4aEventAction.cc
/// \brief Implementation of the B4aEventAction class

#include "B4aEventAction.hh"
#include "B4RunAction.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aEventAction::B4aEventAction()
 : G4UserEventAction()
{
    //The kNCubes numbers are hard wired!!! Need to change with the geometry of the detector
    fEdep = new G4double [kNCubes + 10];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aEventAction::~B4aEventAction()
{
    delete fEdep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aEventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  // initialisation per event
  // nCopy 0 is world.
    for(G4int i = 0; i <= kNCubes; i++)
        fEdep[i] = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aEventAction::EndOfEventAction(const G4Event* event)
{
  // Accumulate statistics
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(1, fEdep[1]);
  analysisManager->FillH1(2, fEdep[2]);
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(1, fEdep[1]);
  analysisManager->FillNtupleDColumn(2, fEdep[2]);

  analysisManager->AddNtupleRow();  
  
  // Print per event (modulo n)
  //
//  auto eventID = event->GetEventID();
//  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
//  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
//    G4cout << "---> End of event: " << eventID << G4endl;

//    G4cout
//       << "   Absorber: total energy: " << std::setw(7)
//                                        << G4BestUnit(fEnergyAbs,"Energy")
//       << "       total track length: " << std::setw(7)
//                                        << G4BestUnit(fTrackLAbs,"Length")
//       << G4endl
//       << "        Gap: total energy: " << std::setw(7)
//                                        << G4BestUnit(fEnergyGap,"Energy")
//       << "       total track length: " << std::setw(7)
//                                        << G4BestUnit(fTrackLGap,"Length")
//       << G4endl;
//  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
