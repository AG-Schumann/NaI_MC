#include "StackingAction.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

namespace NaI {

StackingAction::StackingAction() : G4UserStackingAction() {}
StackingAction::~StackingAction() {}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* aTrack) {
    // Checking if particle is a Secondary
    if (aTrack->GetParentID() > 0) {
        // New particle, new event
        return fWaiting; 
    }
    
    return fUrgent;
}

} // namespace NaI
