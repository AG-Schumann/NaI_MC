#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"
#include "RunAction.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Types.hh"
#include "G4RandomTools.hh"
#include <ctime>


// Physik-Liste: FTFP_BERT is a Standard
// #include "FTFP_BERT.hh"

int main(int argc, char** argv) {
    G4String initFile = "init.mac"; // Default values
    G4String macroFile = "";
    G4String outputFile = "NaI_Simulation.root";
    G4int nEvents = 1000; 

    // parse Arguments
    for (int i=1; i < argc; i++){
	G4String arg = argv[i];
	if (arg == "-p" && i+1 < argc) initFile = argv[++i];
	else if (arg == "-m" && i+1 < argc) macroFile = argv[++i];
	else if (arg == "-o" && i+1 < argc) outputFile = argv[++i];
	else if (arg == "-n" && i+1 < argc) nEvents = std::atoi(argv[++i]);
    }

    // Get the SEED based on system time
    long seed  = time(NULL);
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4Random::setTheSeed(seed);

    G4cout << "***************************************************" << G4endl;
    G4cout << "*** Simulation startet mit Seed: " << seed << G4endl;
    G4cout << "***************************************************" << G4endl;

    // Output name to RunManager
    NaI::RunAction::SetOutputFileName(outputFile);

    G4UIExecutive* ui = nullptr;
    // If no init or macroFile, strat GUI; Not really necessary, but backup that the code does not break down
    if (macroFile == "" && initFile == "") {
	ui = new G4UIExecutive(argc, argv);
    }

    //RunManager
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    runManager->SetUserInitialization(new NaI::DetectorConstruction());

    // Physics List
    runManager->SetUserInitialization(new NaI::PhysicsList());
//    G4VModularPhysicsList* physicsList = new FTFP_BERT;
//    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new NaI::ActionInitialization());

    // Visualisation Manager
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // Interface-Manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Execution of input varibales
    if (initFile != "") {
	UImanager->ApplyCommand("/control/execute " + initFile);
    }

    if (macroFile != "") {
	UImanager->ApplyCommand("/control/execute " + macroFile);
    }

    if (nEvents > 0) {
	UImanager->ApplyCommand("/run/beamOn " + std::to_string(nEvents));
    }


    // start GUI if wanted
    if (ui) {
	if (initFile == "") UImanager->ApplyCommand("/control/execute init_vis.mac");
	ui->SessionStart();
	delete ui;
    }

    // free memory
    delete visManager;
    delete runManager;

    return 0;
}
