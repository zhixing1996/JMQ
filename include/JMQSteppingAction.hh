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
// $Id: JMQSteppingAction.hh 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file JMQSteppingAction.hh
/// \brief Definition of the JMQSteppingAction class

#ifndef JMQSteppingAction_h
#define JMQSteppingAction_h 1

#include "JMQSteppingAction.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4UserSteppingAction.hh"
#include "G4SDManager.hh"
#include "JMQEventAction.hh"
#include "globals.hh"

class G4Step;
class JMQEventAction;
class JMQDetectorConstruction;

class G4LogicalVolume;

/// Stepping action class
/// 

class JMQSteppingAction : public G4UserSteppingAction
{
  public:

    JMQSteppingAction(const JMQDetectorConstruction* detectorConstruction,
			JMQEventAction* eventAction);
    virtual ~JMQSteppingAction();

    // method from the base class
    // virtual void Initialize(G4HCofThisEvent* HCE);
    virtual void UserSteppingAction(const G4Step*);

  private:
    const JMQDetectorConstruction* fDetConstruction;
    JMQEventAction*  fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
