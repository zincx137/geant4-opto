#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class MyDetectorConstruction;

class MyRunAction : public G4UserRunAction
{
  public:
    MyRunAction(const MyDetectorConstruction*);
    virtual ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    const G4int fNumOfLayers;
    const MyDetectorConstruction* fDetConstruction;
};
