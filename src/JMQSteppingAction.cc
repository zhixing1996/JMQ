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
// $Id: JMQSteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file JMQSteppingAction.cc
/// \brief Implementation of the JMQSteppingAction class

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Randomize.hh"

// #include "JMQHit.hh"
#include "JMQSteppingAction.hh"
#include "JMQEventAction.hh"
#include "JMQDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQSteppingAction::JMQSteppingAction(JMQEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQSteppingAction::~JMQSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JMQSteppingAction::UserSteppingAction(const G4Step* step)
{
    G4Track* gTrack = step->GetTrack() ;
    //G4double step_length = step->GetStepLength();
    G4double edep = step->GetTotalEnergyDeposit();
    G4StepPoint* point_pre  = step->GetPreStepPoint() ;
    G4StepPoint* point_post = step->GetPostStepPoint() ;
    G4ThreeVector point_in  = point_pre->GetPosition();
    G4ThreeVector point_out = point_post->GetPosition();
    G4ThreeVector hit_position = (point_in+point_out)/2;
    G4int trackID = 0;
    trackID = gTrack->GetTrackID();

    JMQWriter* mWriter = JMQWriter::Instance();
    mWriter->WriteEdepAndCenter(trackID, edep, hit_position[0], hit_position[1], hit_position[2]);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

