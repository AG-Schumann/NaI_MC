cmake_minimum_required(VERSION 3.16...3.27)
project(NaI_Sim)

# 1. Geant4 Paket finden
find_package(Geant4 REQUIRED ui_all vis_all)

# 2. Geant4 Build-Einstellungen laden
include(${Geant4_USE_FILE})

# 3. Header-Verzeichnisse definieren
# Wir fügen das 'include' Verzeichnis hinzu, damit die .cc Dateien 
# ihre Header finden können.
include_directories(include ${Geant4_INCLUDE_DIRS})

# 4. Quelldateien auflisten (mit Pfad zu src/)
set(SOURCES
    NaI.cc
    src/DetectorConstruction.cc
    src/ActionInitialization.cc
    src/PrimaryGeneratorAction.cc
    src/RunAction.cc
    src/EventAction.cc
    src/SteppingAction.cc
    src/HolderConstruction.cc
    src/PhysicsList.cc
    src/StackingAction.cc
    src/LeadConstruction.cc
)

# 5. Headerdateien auflisten (mit Pfad zu include/)
set(HEADERS
    include/DetectorConstruction.hh
    include/ActionInitialization.hh
    include/PrimaryGeneratorAction.hh
    include/RunAction.hh
    include/EventAction.hh
    include/SteppingAction.hh
    include/HolderConstruction.hh
    include/PhysicsList.hh
    include/StackingAction.hh
    include/LeadConstruction.hh
)

# 6. Das Executable erstellen
add_executable(NaI_MC ${SOURCES} ${HEADERS})

# 7. Mit Geant4 Bibliotheken verlinken
target_link_libraries(NaI_MC ${Geant4_LIBRARIES})

# 8. Makro-Dateien in den Build-Ordner kopieren
set(SCRIPTS
    init_vis.mac
    run.mac
)

foreach(_script ${SCRIPTS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/${_script}
        ${PROJECT_BINARY_DIR}/${_script}
        COPYONLY
    )
endforeach()
