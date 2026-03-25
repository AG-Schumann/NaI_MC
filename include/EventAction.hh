#ifndef NaIEventAction_h
#define NaIEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <map>

namespace NaI {

class EventAction : public G4UserEventAction {
  public:
    EventAction();
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*) override;
    virtual void EndOfEventAction(const G4Event*) override;

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    std::map<G4int, G4double> fGammaTracks;
    G4double fEdep;
};

} // namespace NaI

#endif
