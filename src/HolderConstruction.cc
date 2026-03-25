#include "HolderConstruction.hh"

#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SystemOfUnits.hh"

namespace NaI {

HolderConstruction::HolderConstruction() {}
HolderConstruction::~HolderConstruction() {}

void HolderConstruction::ConstructHolder(G4LogicalVolume* motherLogic) {

    // Material
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* pe_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    // Dimensions
    // All Dimensions and Offsets are taken as the PMT stands on the Crystal Base with the Baseplate in the Back -> Just imagine a bit
    G4double plateThick = 10.0 * mm;
    G4double plateSizeBaseX  = 140.0 * mm;
    G4double plateSizeBaseZ  = 260 *mm;
    G4double plateSizeLX = 100 *mm;
    G4double plateSizeLY = 120 *mm;
    G4double plateSizeSX = 80 *mm;
    G4double plateSizeSY = 110 *mm;

    // zOffset from the Pmt front to middle of plates
    G4double zOffset1 = 35 *mm;
    G4double zOffset2 = 155 *mm;
    G4double zOffset3 = 210 *mm;

    // yOffset middle of PMT to top of Baseplate
    G4double yOffset = 70 * mm;

    //Dimensions for Cutouts from Detector Constructor
    G4double crystalRadius = 1.5 * 25.4 * mm;
    G4double pmtRadius = 58/2. * mm;
    G4double casingThick   = 0.5 * mm;
    G4double RbigHole = crystalRadius + casingThick;
    G4double RsmallHole = pmtRadius + casingThick;

    //Baseplate
    G4Box* solidBaseplate = new G4Box("BasePlate", plateSizeBaseX/2., plateThick/2., plateSizeBaseZ/2.);

    //Large Plate
    G4Box* solidplate1 = new G4Box("Plate1", plateSizeLX/2., plateSizeLY/2., plateThick/2.);
    G4Tubs* solidHoleL = new G4Tubs("HoleL", 0, RbigHole, plateThick, 0, 360*deg);
    G4ThreeVector holePosL(0,yOffset-plateSizeLY/2., 0);
    G4SubtractionSolid* solidPlateL = new G4SubtractionSolid("PlateL", solidplate1, solidHoleL, 0, holePosL);

    //Small Plate
    G4Box* solidplate2 = new G4Box("Plate2", plateSizeSX/2., plateSizeSY/2., plateThick/2.);
    G4Tubs* solidHoleS = new G4Tubs("HoleS", 0, RsmallHole, plateThick, 0 , 360*deg);
    G4ThreeVector holePosS(0, yOffset-plateSizeSY/2., 0);
    G4SubtractionSolid* solidPlateS = new G4SubtractionSolid("PlateS", solidplate2, solidHoleS, 0, holePosS);

    //Unionsolid of all Parts, Baseplate is the center
    G4ThreeVector PosLow( 0, (plateThick+plateSizeLY)/2., -plateSizeBaseZ/2.+zOffset1);
    G4UnionSolid* union1 = new G4UnionSolid("Union1", solidBaseplate, solidPlateL, 0, PosLow);

    G4ThreeVector PosMid( 0, (plateThick+plateSizeSY)/2., -plateSizeBaseZ/2.+zOffset2);
    G4UnionSolid* union2 = new G4UnionSolid("Union2", union1, solidPlateS, 0, PosMid);

    G4ThreeVector PosTop( 0, (plateThick+plateSizeSY)/2., -plateSizeBaseZ/2.+zOffset3);
    G4UnionSolid* solidHolder = new G4UnionSolid("solidHolder", union2, solidPlateS, 0, PosTop);


    G4LogicalVolume* logicHolder = new G4LogicalVolume(solidHolder, pe_mat, "Holder");


    // Viualisation
    G4VisAttributes* vis = new G4VisAttributes(G4Color(0.9, 0.9, 0.9, 0.6));
    vis->SetForceSolid(true);
    logicHolder->SetVisAttributes(vis);

    // Placing in the Container
    new G4PVPlacement(0, G4ThreeVector(0,-(yOffset+plateThick/2.),plateSizeBaseZ/2), logicHolder, "Holder", motherLogic, false, 0, true);

}

}
