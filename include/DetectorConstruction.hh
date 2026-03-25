#ifndef NaIDetectorConstruction_h
#define NaIDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace NaI {

class DetectorConstruction : public G4VUserDetectorConstruction {
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;

  private:
    // Logic Volume
    G4LogicalVolume* fLogicCrystal;
    G4LogicalVolume* fLogicGlas;
    G4LogicalVolume* fLogicVacuum;
    G4LogicalVolume* fLogicCasing;

    G4bool fCheckOverlaps;
};

} // namespace NaI

#endif
