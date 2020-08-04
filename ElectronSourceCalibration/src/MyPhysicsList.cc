#include "MyPhysicsList.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmStandardPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPhysicsList::MyPhysicsList()
: G4VModularPhysicsList(){
  SetVerboseLevel(0);
  // EM physics
  RegisterPhysics(new G4EmPenelopePhysics());
  RegisterPhysics(new G4EmLowEPPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPhysicsList::~MyPhysicsList()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
