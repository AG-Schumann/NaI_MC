#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

namespace NaI {

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    SetVerboseLevel(1);

    // Standard Zerfall (für Teilchen wie Myonen etc.)
    RegisterPhysics(new G4DecayPhysics());

    // Radioaktiver Zerfall von Kern-Isotopen
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // Elektromagnetische Physik (Photoeffekt, Compton, etc.)
    RegisterPhysics(new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts() {
    // Standard-Cuts für die Produktion von Sekundärteilchen (1 mm)
    G4VModularPhysicsList::SetCuts();
}

} // namespace NaI
