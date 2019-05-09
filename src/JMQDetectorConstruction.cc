//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: JMQDetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file JMQDetectorConstruction.cc
/// \brief Implementation of the JMQDetectorConstruction class

#include "JMQDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQDetectorConstruction::JMQDetectorConstruction()
: G4VUserDetectorConstruction(),
    fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQDetectorConstruction::~JMQDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* JMQDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_x = 5000.*mm;
  G4double world_y = 5000.*mm;
  G4double world_z = 5000.*mm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_x, 0.5*world_y, 0.5*world_z);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // head
  //  
  G4double head_D = 180.*mm;
  G4Material* head_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4Orb* solidHead =    
    new G4Orb("Head",                    //its name
        0.5*head_D); //its size
      
  G4LogicalVolume* logicHead =                         
    new G4LogicalVolume(solidHead,            //its solid
                        head_mat,             //its material
                        "Head");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0., 430.*mm,0.),         //at (0,0,0)
                    logicHead,                //its logical volume
                    "Head",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //    
  //neck
  // 
  G4double neck_innerD = 0.*mm;
  G4double neck_outerD = 100.*mm;
  G4double neck_h = 90.*mm;
  G4double start_angle = 0.*deg;
  G4double spanning_angle = 360.*deg;
  G4RotationMatrix* neck_rot = new G4RotationMatrix();
  neck_rot->rotateX(90.*deg);
  G4Material* neck_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector neck_pos = G4ThreeVector(0., 295.*mm, 0.);
        
  G4Tubs* solidNeck 
    = new G4Tubs("Neck", 
               0.5*neck_innerD,
               0.5*neck_outerD,
               0.5*neck_h,
               start_angle,
               spanning_angle);
                      
  G4LogicalVolume* logicNeck =                         
    new G4LogicalVolume(solidNeck,         //its solid
                        neck_mat,          //its material
                        "Neck");           //its name
               
  new G4PVPlacement(neck_rot,                       //no rotation
                    neck_pos,                    //at position
                    logicNeck,             //its logical volume
                    "Neck",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Chest
  //
  G4double chest_x = 120.*mm;
  G4double chest_y = 500.*mm;
  G4double chest_z = 260.*mm;
  G4Material* chest_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector chest_pos = G4ThreeVector(0., 0., 0.);

  G4Box* solidChest =    
    new G4Box("Chest",                      //its name
              0.5*chest_x,
              0.5*chest_y, 
              0.5*chest_z); //its size
                
  G4LogicalVolume* logicChest =                         
    new G4LogicalVolume(solidChest,         //its solid
                        chest_mat,          //its material
                        "Chest");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    chest_pos,                    //at position
                    logicChest,             //its logical volume
                    "Chest",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4double leg_innerD = 0.*mm;
  G4double leg_outerD = 110.*mm;
  G4double leg_h = 820.*mm;
  G4double leg_start = 0.*deg;
  G4double leg_spanning = 360.*deg;
  G4RotationMatrix* leg_rot = new G4RotationMatrix();
  leg_rot->rotateX(90.*deg);
  G4Material* leg_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector leg1_pos = G4ThreeVector(0., -660.*mm, -75.*mm);
  G4ThreeVector leg2_pos = G4ThreeVector(0., -660.*mm, 75.*mm);

  //     
  // leg1
  //  

  G4Tubs* solidLeg1 =    
    new G4Tubs("Leg1", 
    0.5*leg_innerD, 0.5*leg_outerD, 0.5*leg_h,
    leg_start, leg_spanning);
                      
  G4LogicalVolume* logicLeg1 =                         
    new G4LogicalVolume(solidLeg1,         //its solid
                        leg_mat,          //its material
                        "Leg1");           //its name
               
  new G4PVPlacement(leg_rot,                       //no rotation
                    leg1_pos,                    //at position
                    logicLeg1,             //its logical volume
                    "Leg1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // leg2
  //  

  G4Tubs* solidLeg2 =    
    new G4Tubs("Leg2", 
    0.5*leg_innerD, 0.5*leg_outerD, 0.5*leg_h,
    leg_start, leg_spanning);
                      
  G4LogicalVolume* logicLeg2 =                         
    new G4LogicalVolume(solidLeg2,         //its solid
                        leg_mat,          //its material
                        "Leg2");           //its name
               
  new G4PVPlacement(leg_rot,                       //no rotation
                    leg2_pos,                    //at position
                    logicLeg2,             //its logical volume
                    "Leg2",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number      
                    checkOverlaps);          //overlaps checking     //

  fScoringVolume = logicChest;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

