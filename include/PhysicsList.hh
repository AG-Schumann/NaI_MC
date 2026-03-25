#ifndef NaIPhysicsList_h
#define NaIPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

namespace NaI {

class PhysicsList : public G4VModularPhysicsList {
  public:
    PhysicsList();
    virtual ~PhysicsList();

    virtual void SetCuts() override;
};

} // namespace NaI

#endif
