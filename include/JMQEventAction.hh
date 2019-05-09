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
//#include "JMQHit.hh"
#include "JMQWriter.hh"

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

  private:
    JMQRunAction* fRunAction;
    G4double px=0, py=0, pz=0;
//    G4double dx=0, dy=0, dz=0;
//    G4double rx=0, ry=0, rz=0;
//    G4double L=0., l=0.;
//    G4double sin_phi=0, cos_phi=0, sin_theta=0, cos_theta=0;
//    G4double edep1=0., edep2=0.;
//    G4double edep1_x=0, edep1_y=0, edep1_z=0;
//    G4double edep2_x=0, edep2_y=0, edep2_z=0;
//    G4double xedep1=0, yedep1=0, zedep1=0;
//    G4double xedep2=0, yedep2=0, zedep2=0;
//    G4double xc1=0, yc1=0, zc1=0;
//    G4double xc2=0, yc2=0, zc2=0;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
