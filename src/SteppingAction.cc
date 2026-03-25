#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

namespace NaI {

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(), fEventAction(eventAction) {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track  = step->GetTrack();
    G4double edepStep = step->GetTotalEnergyDeposit();
    if (edepStep <=0.) return;

    // Checking volume
    if (step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "Crystal") {

        G4int pid = track->GetParentID();
        auto particle = track->GetDefinition();

	// Ignore beta decays
	if (particle == G4Electron::Electron() && pid ==1) return;

	// Ignore alphas
	if (particle->GetPDGCharge()>1.1) return;

	fEventAction->AddEdep(edepStep);
        }

//    auto particle = track->GetDefinition();

//    if (particle == G4Gamma::Gamma() || particle == G4Electron::Electron() || particle == G4Positron::Positron()){
//	G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
//                                  ->GetVolume()->GetLogicalVolume();

//	if (volume->GetName() == "Crystal") {
//	    G4double edepStep = step->GetTotalEnergyDeposit();

//            if (edepStep > 0.) {
//            	fEventAction->AddEdep(edepStep);
//	    }
//        }

}

} // namespace NaI
