#include "MyRunAction.hh"
#include "MyAnalysis.hh"
#include "MyDetectorConstruction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <string>
MyRunAction::MyRunAction(const MyDetectorConstruction* Det)
 : G4UserRunAction(),
   fNumOfLayers(Det->GetNumOfLayers()),
   fDetConstruction(Det)
{
    auto analysisManager = G4AnalysisManager::Instance();
    // Create directories
//    analysisManager->SetHistoDirectoryName("histograms");
//    analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(0);
//    analysisManager->SetNtupleMerging(true);
//    analysisManager->CreateNtuple("ESC", "Edep density");
    for(G4int i = 0; i < fNumOfLayers; i++){
        analysisManager->CreateH1("E"+std::to_string(i),"Edep in layer #" + std::to_string(i), 100, 0., 5*keV);
//        analysisManager->CreateNtupleDColumn("E"+std::to_string(i));

    }
//    analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyRunAction::~MyRunAction()
{
    delete G4AnalysisManager::Instance();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyRunAction::BeginOfRunAction(const G4Run* /*run*/)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyRunAction::EndOfRunAction(const G4Run* /*run*/)
{
//    auto analysisManager = G4AnalysisManager::Instance();
//    if ( analysisManager->GetH1(1) ) {
//      G4cout << G4endl << " ----> print histograms statistic " << G4endl;
//      if(isMaster)
//          for(G4int i = 0; i < fNumOfLayers; i++){
//            G4cout << " Layer #" << i << "  "
//           << G4BestUnit(analysisManager->GetH1(i)->mean(), "Energy")
//           << " +- "
//           << G4BestUnit(analysisManager->GetH1(i)->rms(),  "Energy") << G4endl;
//          }
//    }
              for(G4int i = 0; i < fNumOfLayers; i++){
//                G4cout << " Layer #" << i << "  "
//               << G4BestUnit(fDetConstruction->fEdep[i], "Energy") << G4endl;
                  G4cout << fDetConstruction->fEdep[i] / MeV << G4endl;
              }

}
