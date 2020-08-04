#include "MyEventAction.hh"
#include "MyRunAction.hh"
#include "MyAnalysis.hh"
#include "MyDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyEventAction::MyEventAction(const MyDetectorConstruction* det)
 : G4UserEventAction(),
   fNumOfLayers(det->GetNumOfLayers()),
   fDetConstruction(det)
{
    fEdep = new G4double[fNumOfLayers + 5];
}


MyEventAction::~MyEventAction()
{
    delete fEdep;
}


void MyEventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // initialisation per event
  for(G4int i = 0; i < fNumOfLayers; i++){
      fEdep[i] = 0.;
  }
}


void MyEventAction::EndOfEventAction(const G4Event* event)
{

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  for(G4int i = 0; i < fNumOfLayers; i++){
      fDetConstruction->fEdep[i] += fEdep[i];
//    analysisManager->FillH1(i, fEdep[i]);
//    analysisManager->FillNtupleDColumn(i, fEdep[i]);
  }

//  analysisManager->AddNtupleRow();

}

void MyEventAction::AddE(G4int iLayer, G4double de) {
  fEdep[iLayer] += de;
}
