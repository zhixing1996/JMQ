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
// $Id: JMQEventAction.cc 93886 2015-11-03 08:28:26Z gcosmo $
//
/// \file JMQEventAction.cc
/// \brief Implementation of the JMQEventAction class

#include "JMQEventAction.hh"
#include "JMQRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQEventAction::JMQEventAction(JMQRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQEventAction::~JMQEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JMQEventAction::BeginOfEventAction(const G4Event* event)
{    
    G4int eventID = event->GetEventID();
    G4cout << "\n---> Begin of event: " << eventID << G4endl;

    JMQWriter* mWriter = JMQWriter::Instance();
    mWriter->WriteEventTag(event->GetEventID());
    for(G4int i=0; i<event->GetNumberOfPrimaryVertex(); i++){
        px = event->GetPrimaryVertex(i)->GetPrimary()->GetPx();
        py = event->GetPrimaryVertex(i)->GetPrimary()->GetPy();
        pz = event->GetPrimaryVertex(i)->GetPrimary()->GetPz();
        mWriter->WriteRayDirection(px,py,pz);
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JMQEventAction::EndOfEventAction(const G4Event* event)
{   

    G4int eventID = event->GetEventID();
    G4cout << "\n---> End of event: " << eventID << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
