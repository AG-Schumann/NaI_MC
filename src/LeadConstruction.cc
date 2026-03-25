#include "LeadConstruction.hh"

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

LeadConstruction::LeadConstruction() {}
LeadConstruction::~LeadConstruction() {}

void LeadConstruction::ConstructLead(G4LogicalVolume* motherLogic) {

    // Material
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* pb_mat = nist->FindOrBuildMaterial("G4_Pb");

    G4cout << "Density Lead: " << pb_mat->GetDensity() / (g/cm3) << " g/cm³" << G4endl;

    // Dimensions
    // All Dimensions and Offsets are taken as the PMT stands on the Crystal Base with the Baseplate in the Back -> Just imagine a bit
    G4double pbLength = 200. *mm; //x
    G4double pbWidth = 100. *mm; //y
    G4double pbHeight = 50.*mm; //z


    // Offsets
    G4double yOffset = 26. *mm; // Space in front of PMT from the Calibration Sources Disk width
    G4double zOffset = -80. *mm; //Bottom of Holder


    // Lead Bricks
    G4Box* solidStandard = new G4Box("StandardLead", pbLength/2., pbWidth/2., pbHeight/2.);
    G4Box* solidHalf = new G4Box("HalfLead", pbLength/2., pbWidth/4., pbHeight/2.);

    fLogicStandard = new G4LogicalVolume(solidStandard, pb_mat, "LeadBrick");
    fLogicHalf = new G4LogicalVolume(solidHalf, pb_mat, "LeadBrick");

    // visual Attributes
    G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0.3, 0.3, 0.3, 0.8));
    visAttr->SetForceSolid(true);
    fLogicStandard->SetVisAttributes(visAttr);
    fLogicHalf->SetVisAttributes(visAttr);


    G4int nStandard = 0;
    G4int nHalf = 0;

    // Placement
    // Using a containter, in which all are placed, allows confine in the macro
    G4Box* solidContainer = new G4Box("LeadcontainerSolid", 50*cm, 50*cm, 50*cm);
    G4LogicalVolume* logicLeadContainer = new G4LogicalVolume(solidContainer, world_mat, "Lead");
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicLeadContainer, "Lead", motherLogic, false, 0, false);

    // Bottom
    G4RotationMatrix* rot1 = new G4RotationMatrix();
    rot1->rotateZ(90. *deg);

    new G4PVPlacement(rot1,
		G4ThreeVector( pbWidth/4. , yOffset - pbLength/2., zOffset - pbHeight/2.),
		fLogicStandard, "LeadBrick_0", logicLeadContainer, false, 0, true);
		nStandard++;

    new G4PVPlacement(rot1,
                G4ThreeVector( pbWidth/4. , yOffset - pbLength*3/2., zOffset - pbHeight/2.),
                fLogicStandard, "LeadBrick_1", logicLeadContainer, false, 1, true);
		nStandard++;

    new G4PVPlacement(rot1,
                G4ThreeVector( -pbWidth/2. , yOffset - pbLength/2., zOffset - pbHeight/2.),
                fLogicHalf, "LeadBrick_2", logicLeadContainer, false, 2, true);
		nHalf++;

    new G4PVPlacement(rot1,
                G4ThreeVector( -pbWidth/2. , yOffset - pbLength*3/2., zOffset - pbHeight/2.),
                fLogicHalf, "LeadBrick_3", logicLeadContainer, false, 3, true);
		nHalf++;

    //Sides
    G4RotationMatrix* rot2 = new G4RotationMatrix();
    rot2->rotateY(90. *deg);

    new G4PVPlacement(rot2,
		G4ThreeVector( pbWidth*3/4. + pbHeight/2., yOffset, zOffset +pbLength/2. - pbHeight),
		fLogicStandard, "LeadBrick_4", logicLeadContainer, false, 4, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( pbWidth*3/4. + pbHeight/2., yOffset - pbWidth, zOffset +pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_5", logicLeadContainer, false, 5, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( pbWidth*3/4. + pbHeight/2., yOffset - pbWidth*2, zOffset +pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_6", logicLeadContainer, false, 6, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( pbWidth*3/4. + pbHeight/2., yOffset - pbWidth*3, zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_7", logicLeadContainer, false, 7, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( pbWidth*3/4. + pbHeight/2., yOffset - pbWidth*4, zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_8", logicLeadContainer, false, 8, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( -pbWidth*3/4. - pbHeight/2., yOffset, zOffset +pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_9", logicLeadContainer, false, 9, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( -pbWidth*3/4. - pbHeight/2., yOffset - pbWidth, zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_10", logicLeadContainer, false, 10, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( -pbWidth*3/4. - pbHeight/2., yOffset - pbWidth*2, zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_11", logicLeadContainer, false, 11, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( -pbWidth*3/4. - pbHeight/2., yOffset - pbWidth*3, zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_12", logicLeadContainer, false, 12, true);
		nStandard++;

    new G4PVPlacement(rot2,
                G4ThreeVector( -pbWidth*3/4. - pbHeight/2., yOffset - pbWidth*4, zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_13", logicLeadContainer, false, 13, true);
		nStandard++;



    // Front
    G4RotationMatrix* rot3 = new G4RotationMatrix();
    rot3->rotateZ(90. *deg);
    rot3->rotateY(90. *deg);

    new G4PVPlacement(rot3,
                G4ThreeVector( pbWidth/4. , yOffset + pbHeight/2., zOffset + pbLength/2. - pbHeight),
                fLogicStandard, "LeadBrick_14", logicLeadContainer, false, 14, true);
		nStandard++;

    new G4PVPlacement(rot3,
                G4ThreeVector( -pbWidth/2. , yOffset + pbHeight/2., zOffset + pbLength/2. - pbHeight),
                fLogicHalf, "LeadBrick_15", logicLeadContainer, false, 15, true);
		nHalf++;


    // Back
    new G4PVPlacement(rot3,
                G4ThreeVector( pbWidth/2. , yOffset - pbLength*2. - pbHeight/2., zOffset + pbLength/2. - pbHeight),
                fLogicHalf, "LeadBrick_16", logicLeadContainer, false, 16, true);
		nHalf++;

    new G4PVPlacement(rot3,
                G4ThreeVector( -pbWidth/2. , yOffset - pbLength*2. - pbHeight/2., zOffset + pbLength/2. - pbHeight),
                fLogicHalf, "LeadBrick_17", logicLeadContainer, false, 17, true);
		nHalf++;

    // Top
    new G4PVPlacement(0,
                G4ThreeVector( 0, yOffset, zOffset + pbLength - pbHeight/2.),
                fLogicStandard, "LeadBrick_18", logicLeadContainer, false, 18, true);
		nStandard++;

    new G4PVPlacement(0,
                G4ThreeVector( 0, yOffset - pbWidth, zOffset + pbLength - pbHeight/2.),
                fLogicStandard, "LeadBrick_19", logicLeadContainer, false, 19, true);
		nStandard++;

    new G4PVPlacement(0,
                G4ThreeVector( 0, yOffset - pbWidth*2, zOffset + pbLength - pbHeight/2.),
                fLogicStandard, "LeadBrick_20", logicLeadContainer, false, 20, true);
		nStandard++;

    new G4PVPlacement(0,
                G4ThreeVector( 0, yOffset - pbWidth*3, zOffset + pbLength - pbHeight/2.),
                fLogicStandard, "LeadBrick_21", logicLeadContainer, false, 21, true);
		nStandard++;

    new G4PVPlacement(0,
                G4ThreeVector( 0, yOffset - pbWidth*4, zOffset + pbLength - pbHeight/2.),
                fLogicStandard, "LeadBrick_22", logicLeadContainer, false, 22, true);
		nStandard++;

    // Print out the Mass of the Lead
    G4double totMass = fLogicStandard->GetMass() * nStandard + fLogicHalf->GetMass() * nHalf;
    G4cout << "Mass of Lead Shield " << totMass / kg << " kg" << G4endl;
};

} //namespace NaI
