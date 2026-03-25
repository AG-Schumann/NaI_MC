#ifndef NaIHolderConstruction_h
#define NaIHolderConstruction_h 1

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

namespace NaI {

class HolderConstruction {
  public:
    HolderConstruction();
    ~HolderConstruction();

    void ConstructHolder(G4LogicalVolume* motherLogic);

  private:
    G4bool fCheckOverlaps;
};

}
#endif
