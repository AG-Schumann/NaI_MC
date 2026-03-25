#include "EventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4SystemOfUnits.hh"

namespace NaI {

EventAction::EventAction() : G4UserEventAction(), fEdep(0.) {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {
    fEdep = 0.; // new Event, new Energy
}

void EventAction::EndOfEventAction(const G4Event* event) {
    auto analysisManager = G4AnalysisManager::Instance();

    // Nur wenn Energie deponiert wurde (durch den Filter in SteppingAction), schreiben wir eine Zeile
    if (fEdep <= 0.) return;

    // 1. Primär-Informationen (Position & Richtung)
    G4double px=0, py=0, pz=0, dx=0, dy=0, dz=0, Epri=0;
    
    G4PrimaryVertex* vertex = event->GetPrimaryVertex();
    if (vertex) {
        px = vertex->GetX0() / mm;
        py = vertex->GetY0() / mm;
        pz = vertex->GetZ0() / mm;

        G4PrimaryParticle* primary = vertex->GetPrimary();
        if (primary) {
            G4ThreeVector dir = primary->GetMomentumDirection();
            dx = dir.x();
            dy = dir.y();
            dz = dir.z();
            Epri = primary->GetKineticEnergy() / keV;
        }
    }

    // 2. Ntuple füllen (Eine Zeile pro Event)
    
    // Spalten 0-2: Position
    analysisManager->FillNtupleDColumn(0, px);
    analysisManager->FillNtupleDColumn(1, py);
    analysisManager->FillNtupleDColumn(2, pz);
    
    // Spalten 3-5: Richtung (Direction)
    analysisManager->FillNtupleDColumn(3, dx);
    analysisManager->FillNtupleDColumn(4, dy);
    analysisManager->FillNtupleDColumn(5, dz);
    
    // Spalte 6: Die gefilterte Summen-Energie (Gamma + Röntgen + Sekundärelektronen)
    analysisManager->FillNtupleDColumn(7, fEdep / keV);

    // Spalte 7: Primärenergie des Ions/Teilchens
    analysisManager->FillNtupleDColumn(6, Epri);

    // Jetzt schreiben wir die Zeile fest
    analysisManager->AddNtupleRow();
}

} // namespace NaI
