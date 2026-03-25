#ifndef NaIActionInitialization_h
#define NaIActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace NaI {

class ActionInitialization : public G4VUserActionInitialization {
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const override;

    virtual void Build() const override;
};

} // namespace NaI

#endif
