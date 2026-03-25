#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"

namespace NaI {

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());

    SetUserAction(new RunAction());

    EventAction* eventAction = new EventAction();
    SetUserAction(eventAction);

    SetUserAction(new SteppingAction(eventAction));

    SetUserAction(new StackingAction());
}

} // namespace NaI
