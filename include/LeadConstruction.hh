#ifndef NaILeadConstruction_h
#define NaILeadConstruction_h 1

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

namespace NaI {

class LeadConstruction {
  public:
    LeadConstruction();
    ~LeadConstruction();

    void ConstructLead(G4LogicalVolume* motherLogic);

  private:
    G4LogicalVolume* fLogicStandard;
    G4LogicalVolume* fLogicHalf;

    G4bool fCheckOverlaps;
};

}
#endif
