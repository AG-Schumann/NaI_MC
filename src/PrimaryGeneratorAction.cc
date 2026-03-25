#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"

namespace NaI {

// Producing Particles using /gps in macros
PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction() {
    fParticleGPS = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGPS->GeneratePrimaryVertex(anEvent);
}

} // namespace NaI
