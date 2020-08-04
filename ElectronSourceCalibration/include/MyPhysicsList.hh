#include "G4VModularPhysicsList.hh"


class MyPhysicsList: public G4VModularPhysicsList
{
public:
  MyPhysicsList();
  virtual ~MyPhysicsList();

  virtual void SetCuts();
};
