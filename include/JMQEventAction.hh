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
// $Id: JMQEventAction.hh 93886 2015-11-03 08:28:26Z gcosmo $
//
/// \file JMQEventAction.hh
/// \brief Definition of the JMQEventAction class

#ifndef JMQEventAction_h
#define JMQEventAction_h 1

#include "JMQEventAction.hh"
#include "JMQSteppingAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ios.hh"

#include "Randomize.hh"
#include <iomanip>
#include <cmath>

class JMQRunAction;

/// Event action class
///

class JMQEventAction : public G4UserEventAction
{
  public:
    JMQEventAction(JMQRunAction* runAction);
    virtual ~JMQEventAction();

    // JMQHitsCollection *GetHitsCollection(const G4String& hcName, const G4Event* event) const;
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void RecordHead(G4double edep, 
		G4double point_in_x, G4double point_in_y, G4double point_in_z,
		G4double point_out_x, G4double point_out_y, G4double point_out_z);

    void RecordChest(G4double edep, 
		G4double point_in_x, G4double point_in_y, G4double point_in_z,
		G4double point_out_x, G4double point_out_y, G4double point_out_z);

  private:
    JMQRunAction* fRunAction;
    G4double px=0, py=0, pz=0;
    G4double edep1=0., edep2=0.;
    G4double edep1_x=0, edep1_y=0, edep1_z=0;
    G4double edep2_x=0, edep2_y=0, edep2_z=0;
    G4double x_edep1=0, y_edep1=0, z_edep1=0;
    G4double x_edep2=0, y_edep2=0, z_edep2=0;
    G4double xc1, yc1, zc1;
    G4double xc2, yc2, zc2;
};

inline void JMQEventAction::RecordHead(G4double edep,
                G4double point_in_x, G4double point_in_y, G4double point_in_z,
                G4double point_out_x, G4double point_out_y, G4double point_out_z) {
    edep1 += edep;
    edep1_x += (point_out_x+point_in_x)/2*edep;
    edep1_y += (point_out_y+point_in_y)/2*edep;
    edep1_z += (point_out_z+point_in_z)/2*edep;
    x_edep1 += edep;
    y_edep1 += edep;
    z_edep1 += edep;
}

inline void JMQEventAction::RecordChest(G4double edep,
                G4double point_in_x, G4double point_in_y, G4double point_in_z,
                G4double point_out_x, G4double point_out_y, G4double point_out_z) {
    edep2 += edep;
    edep2_x += (point_out_x+point_in_x)/2*edep;
    edep2_y += (point_out_y+point_in_y)/2*edep;
    edep2_z += (point_out_z+point_in_z)/2*edep;
    x_edep2 += edep;
    y_edep2 += edep;
    z_edep2 += edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
 
