#ifndef NaIPrimaryGeneratorAction_h
#define NaIPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

namespace NaI {

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*) override;

  private:
    G4GeneralParticleSource* fParticleGPS;
};

} // namespace NaI

#endif
