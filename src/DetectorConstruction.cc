#include "DetectorConstruction.hh"
#include "HolderConstruction.hh"
#include "LeadConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UnionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

namespace NaI {

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), fLogicCrystal(nullptr), fLogicGlas(nullptr), fLogicVacuum(nullptr), fLogicCasing(nullptr) {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4bool checkOverlaps = true;

    // A seperate Logic Volume "Containter" is used, for turning the total Assembly afterwards


    // Materials
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* nai_mat   = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4Material* ss_mat    = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* al_mat    = nist->FindOrBuildMaterial("G4_Al");
    G4Material* pmt_mat   = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
    G4Material* pe_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material* vac_mat = new G4Material("Vacuum", 7., 14.007 * g / mole, 1.e-12 * g / cm3);

    G4cout << "Density NaI: " << nai_mat->GetDensity() / (g/cm3) << " g/cm³" << G4endl;
    G4cout << "Density Air: " << world_mat->GetDensity() / (g/cm3) << " g/cm³" << G4endl;
    G4cout << "Density SS: " << ss_mat->GetDensity() / (g/cm3) << " g/cm³" << G4endl;
    G4cout << "Density Al: " << al_mat->GetDensity() / (g/cm3) << " g/cm³" << G4endl;
    G4cout << "Density PE: " << pe_mat->GetDensity() / (g/cm3) << " g/cm³" << G4endl;

    // Dimensions (3" x 3")
    G4double crystalRadius = 1.5 * 25.4 * mm;
    G4double crystalHeight = 3.0 * 25.4 * mm;
    G4double glasHeight    = 1. * mm;
    G4double casingThick   = 0.5 * mm;
    G4double pmttubeHeight = 150. * mm;
    G4double pmtRadius = 58/2. * mm;
    G4double pmtconeHeight = 10. * mm;
    G4double contRadius = 200 * mm;
    G4double contHeight = 600 * mm;

    // World
    G4double worldSize = 1000 * mm;
    G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);

    // Lead Shielding outside the Container
    LeadConstruction* leadMaker = new LeadConstruction();
    leadMaker->ConstructLead(logicWorld);


    //Containter
    G4Tubs* solidContainer = new G4Tubs("Containter", 0, contRadius, contHeight/2., 0, 360*deg);
    G4LogicalVolume* logicContainer = new G4LogicalVolume(solidContainer, world_mat, "Containter");

    HolderConstruction* holderMaker = new HolderConstruction();
    holderMaker->ConstructHolder(logicContainer);

    // NaI Crystal
    G4Tubs* solidCrystal = new G4Tubs("Crystal", 0, crystalRadius, crystalHeight/2., 0, 360*deg);
    fLogicCrystal = new G4LogicalVolume(solidCrystal, nai_mat, "Crystal");

    // Glass
    G4Tubs* solidGlas = new G4Tubs("Glas", 0 , crystalRadius, glasHeight/2., 0, 360*deg);
    fLogicGlas = new G4LogicalVolume(solidGlas, pmt_mat, "Glas");

    // Vacuum
    G4Tubs* VacTub = new G4Tubs("VacTub", 0, pmtRadius, pmttubeHeight/2., 0, 360*deg);
    G4Cons* VacCon = new G4Cons("VacCon", 0, crystalRadius, 0, pmtRadius,  pmtconeHeight/2., 0, 360*deg);

    G4RotationMatrix* noRot = new G4RotationMatrix();
    G4double zOffset = pmttubeHeight/2. + pmtconeHeight/2.;
    G4ThreeVector trans(0, 0, zOffset);

    G4UnionSolid* solidVacuum = new G4UnionSolid("Vacuum", VacCon, VacTub, noRot, trans);
    fLogicVacuum = new G4LogicalVolume(solidVacuum, vac_mat, "Vacuum");
    //Center pmtconeHeight/2.

    //Stainless Steel Casing
    G4Tubs* crystalBottom = new G4Tubs("crystalBottom", 0, crystalRadius+casingThick, casingThick/2., 0, 360*deg);
    G4Tubs* crystalTub = new G4Tubs("crystalTub", crystalRadius, crystalRadius+casingThick, (crystalHeight+glasHeight)/2., 0, 360*deg);
    G4Cons* casingCon = new G4Cons("casingCon", crystalRadius, crystalRadius+casingThick, pmtRadius, pmtRadius+casingThick,  pmtconeHeight/2., 0, 360*deg);
    G4Tubs* pmtTub = new G4Tubs("pmtTub", pmtRadius, pmtRadius+casingThick, (pmttubeHeight)/2, 0, 360*deg);
    G4Tubs* pmtTop = new G4Tubs("pmtTop", 0 , pmtRadius+casingThick, casingThick/2., 0, 360*deg);

    //Adding from the crystal to pmt,
    zOffset = -(crystalHeight+glasHeight+casingThick)/2.;
    trans = G4ThreeVector(0, 0, zOffset);
    G4UnionSolid* union1 = new G4UnionSolid("Union1", crystalTub, crystalBottom, noRot, trans);

    zOffset = (crystalHeight+glasHeight+casingThick)/2. + pmtconeHeight/2.;
    trans = G4ThreeVector(0, 0, zOffset);
    G4UnionSolid* union2 = new G4UnionSolid("Union2", union1, casingCon, noRot, trans);

    zOffset = (crystalHeight+glasHeight+casingThick)/2. + pmtconeHeight + (pmttubeHeight+casingThick)/2.;
    trans = G4ThreeVector(0, 0, zOffset);
    G4UnionSolid* union3 = new G4UnionSolid("Union3", union2, pmtTub, noRot, trans);

    zOffset = (crystalHeight+glasHeight+casingThick)/2. + pmtconeHeight + pmttubeHeight + casingThick/2.;
    trans = G4ThreeVector(0, 0, zOffset);
    G4UnionSolid* solidCasing = new G4UnionSolid("Casing", union3, pmtTop, noRot, trans);

    fLogicCasing = new G4LogicalVolume(solidCasing, al_mat, "Casing");
    //Center in (crystalHeight+glasHeight+casingThick)/2.



    // Positioning in Container
    zOffset = casingThick + crystalHeight/2.;
    new G4PVPlacement(0, G4ThreeVector(0, 0, zOffset), fLogicCrystal, "Crystal", logicContainer, false, 0, checkOverlaps);
    zOffset = casingThick + crystalHeight + glasHeight/2.;
    new G4PVPlacement(0, G4ThreeVector(0, 0, zOffset), fLogicGlas, "Glas", logicContainer, false, 0, checkOverlaps);
    zOffset = casingThick + crystalHeight + glasHeight + pmtconeHeight/2.;
    new G4PVPlacement(0, G4ThreeVector(0, 0, zOffset), fLogicVacuum, "Vacuum", logicContainer, false, 0, checkOverlaps);
    zOffset = (crystalHeight+glasHeight)/2 + casingThick;
    new G4PVPlacement(0, G4ThreeVector(0, 0, zOffset), fLogicCasing, "Casing", logicContainer, false, 0, checkOverlaps);

    // Turning the hole Container around the y-axis
    G4RotationMatrix* rotDet = new G4RotationMatrix();
    //rotate 90deg around x to put on baseplate, around y to keep baseplate on the back
    rotDet->rotateX(-90.*deg);

    new G4PVPlacement(rotDet,
			G4ThreeVector(0, 0, 0),
			logicContainer, "Container", logicWorld, false, 0, false);


    // Visualisation
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
    fLogicVacuum->SetVisAttributes(G4VisAttributes::GetInvisible());
    logicContainer->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4VisAttributes* crystalVis = new G4VisAttributes(G4Color(0.0, 1.0, 1.0, 0.5));
    crystalVis->SetForceSolid(true);

    fLogicCrystal->SetVisAttributes(crystalVis);

    G4VisAttributes* casingVis = new G4VisAttributes(G4Color(0.3, 0.3, 0.3, 0.5));
    casingVis->SetForceSolid(true);
    fLogicCasing->SetVisAttributes(casingVis);


    return physWorld;
}

} // namespace NaI
