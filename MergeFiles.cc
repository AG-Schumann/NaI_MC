#include <iostream>
#include "TFileMerger.h"
#include "TString.h"
#include "G4SystemOfUnits.hh" // Falls du Einheiten brauchst, sonst weglassen

int main() {
    // Erstelle den Merger
    TFileMerger merger(false); // false = überschreibt die Zieldatei nicht automatisch
    
    // Name der Ausgabedatei
    merger.OutputFile("NaI_Simulation.root");
    
    // Suche nach Dateien NaI_Simulation_t0.root, t1.root ...
    // Hier kannst du die Anzahl deiner Kerne anpassen oder eine Schleife nutzen
    // Einfacher ist es, die Wildcard-Funktion von TFileMerger zu nutzen:
    
    std::cout << "Suche Teil-Dateien zum Zusammenfügen..." << std::endl;
    
    // Wir fügen die Dateien manuell hinzu (Beispiel für 4 Threads)
    // In einer echten Umgebung könnte man das per Dateisystem-Abfrage automatisieren
    for (int i = 0; i < 64; ++i) { // Geht bis zu 64 Threads durch
        TString fileName = TString::Format("NaI_Simulation_t%d.root", i);
        
        // Prüfen, ob Datei existiert
        FILE* file = fopen(fileName.Data(), "r");
        if (file) {
            fclose(file);
            merger.AddFile(fileName);
            std::cout << "Hinzugefügt: " << fileName << std::endl;
        }
    }

    // Zusammenführen starten
    bool success = merger.PartialMerge(TFileMerger::kAll | TFileMerger::kIncremental);

    if (success) {
        std::cout << "Erfolgreich zusammengeführt in NaI_Simulation.root" << std::endl;
    } else {
        std::cerr << "Fehler beim Zusammenführen!" << std::endl;
    }

    return 0;
}
