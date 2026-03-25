#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

namespace NaI {

RunAction::RunAction() : G4UserRunAction() {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("root");

    analysisManager->CreateNtuple("Hits", "Event info");
    analysisManager->CreateNtupleDColumn("x_pri");     // [mm]
    analysisManager->CreateNtupleDColumn("y_pri");     // [mm]
    analysisManager->CreateNtupleDColumn("z_pri");     // [mm]
    analysisManager->CreateNtupleDColumn("dx_pri");    // Impuls direction x
    analysisManager->CreateNtupleDColumn("dy_pri");    // Impuls direction y
    analysisManager->CreateNtupleDColumn("dz_pri");    // Impuls direction z
    analysisManager->CreateNtupleDColumn("E_pri");     // primary Energy in keV
    analysisManager->CreateNtupleDColumn("edep");  // Energy deposited in Crystal  [keV]
    analysisManager->FinishNtuple();
}

RunAction::~RunAction() {}

G4String RunAction::fFileName = "NaI_Simulation.root"; //Default name

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile(fFileName);
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

} // namespace NaI
