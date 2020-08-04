#include "G4UserEventAction.hh"
#include "globals.hh"
class MyDetectorConstruction;

class MyEventAction : public G4UserEventAction
{
  public:
    MyEventAction(const MyDetectorConstruction* );
    virtual ~MyEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    void AddE(G4int de, G4double dl);

  private:
    G4double*  fEdep;
    const G4int fNumOfLayers;
    const MyDetectorConstruction* fDetConstruction;

};




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


