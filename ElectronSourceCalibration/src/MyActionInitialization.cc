#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MyTrackingAction.hh"
#include "MySteppingAction.hh"
#include "G4MTRunManager.hh"
#include "MyDetectorConstruction.hh"

MyActionInitialization::MyActionInitialization
                            (MyDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}


MyActionInitialization::~MyActionInitialization()
{}


void MyActionInitialization::BuildForMaster() const
{
  SetUserAction(new MyRunAction(fDetConstruction));
}


void MyActionInitialization::Build() const
{
  SetUserAction(new MyPrimaryGeneratorAction);
  SetUserAction(new MyRunAction(fDetConstruction));
  MyEventAction* fEventAction= new MyEventAction(fDetConstruction);
  SetUserAction(fEventAction);
  SetUserAction(new MyTrackingAction);
  SetUserAction(new MySteppingAction(fEventAction));
}
