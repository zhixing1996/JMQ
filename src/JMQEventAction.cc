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
#include "JMQAnalysis.hh"

#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include <iomanip>
#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQEventAction::JMQEventAction(JMQRunAction* runAction)
: G4UserEventAction(),
  edep1(0.), edep2(0.),
  edep1_x(0.), edep1_y(0.), edep1_z(0.),
  edep2_x(0.), edep2_y(0.), edep2_z(0.),
  x_edep1(0.), y_edep1(0.), z_edep1(0.),
  x_edep2(0.), y_edep2(0.), z_edep2(0.),
  xc1(0.), yc1(0.), zc1(0.),
  xc2(0.), yc2(0.), zc2(0.),
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

    for(G4int i=0; i<event->GetNumberOfPrimaryVertex(); i++){
        px = event->GetPrimaryVertex(i)->GetPrimary()->GetPx();
        py = event->GetPrimaryVertex(i)->GetPrimary()->GetPy();
        pz = event->GetPrimaryVertex(i)->GetPrimary()->GetPz();
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JMQEventAction::EndOfEventAction(const G4Event* event)
{   
    G4int eventID = event->GetEventID();
    if (x_edep1 != 0 && edep1_x != 0 &&
        y_edep1 != 0 && edep1_y != 0 &&
        z_edep1 != 0 && edep1_z != 0 &&
        x_edep2 != 0 && edep2_x != 0 &&
        y_edep2 != 0 && edep2_y != 0 &&
        z_edep2 != 0 && edep2_z != 0) {
            xc1 = x_edep1/edep1_x;
            yc1 = y_edep1/edep1_y;
            zc1 = z_edep1/edep1_z;
            xc2 = x_edep2/edep2_x;
            yc2 = y_edep2/edep2_y;
            zc2 = z_edep2/edep2_z;
    } else {
            xc1 = -9999999;
            yc1 = -9999999;
            zc1 = -9999999;
            xc2 = -9999999;
            yc2 = -9999999;
            zc2 = -9999999;
    }

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, eventID);
    analysisManager->FillNtupleDColumn(1, edep1);
    analysisManager->FillNtupleDColumn(2, edep2);
    analysisManager->FillNtupleDColumn(3, xc1);
    analysisManager->FillNtupleDColumn(4, yc1);
    analysisManager->FillNtupleDColumn(5, zc1);
    analysisManager->FillNtupleDColumn(6, xc2);
    analysisManager->FillNtupleDColumn(7, yc2);
    analysisManager->FillNtupleDColumn(8, zc2);
    analysisManager->FillNtupleDColumn(9, px);
    analysisManager->FillNtupleDColumn(10, py);
    analysisManager->FillNtupleDColumn(11, pz);
    analysisManager->AddNtupleRow();

    G4cout << "\n---> End of event: " << eventID << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
