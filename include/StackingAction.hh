#ifndef NaIStackingAction_h
#define NaIStackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

namespace NaI {

class StackingAction : public G4UserStackingAction {
  public:
    StackingAction();
    virtual ~StackingAction();

    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack) override;
};

} // namespace NaI

#endif
