#ifndef NaISteppingAction_h
#define NaISteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

namespace NaI {

class EventAction;

class SteppingAction : public G4UserSteppingAction {
  public:
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* fEventAction;
};

} // namespace NaI

#endif
