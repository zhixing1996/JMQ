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
// $Id: JMQRunAction.cc 99560 2016-09-27 07:03:29Z gcosmo $
//
/// \file JMQRunAction.cc
/// \brief Implementation of the JMQRunAction class

#include "JMQRunAction.hh"
#include "JMQPrimaryGeneratorAction.hh"
#include "JMQDetectorConstruction.hh"
#include "JMQAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQRunAction::JMQRunAction()
: G4UserRunAction()
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in JMQAnalysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  
  // Creating ntuple
  analysisManager->CreateNtuple("JMQ", "Edep and Hit position");
  analysisManager->CreateNtupleDColumn("EventID");
  analysisManager->CreateNtupleDColumn("edep_head");
  analysisManager->CreateNtupleDColumn("edep_chest");
  analysisManager->CreateNtupleDColumn("head_center_x");
  analysisManager->CreateNtupleDColumn("head_center_y");
  analysisManager->CreateNtupleDColumn("head_center_z");
  analysisManager->CreateNtupleDColumn("chest_center_x");
  analysisManager->CreateNtupleDColumn("chest_center_y");
  analysisManager->CreateNtupleDColumn("particle_center_z");
  analysisManager->CreateNtupleDColumn("particle_momentum_x");
  analysisManager->CreateNtupleDColumn("particle_momentum_y");
  analysisManager->CreateNtupleDColumn("particle_momentum_z");
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JMQRunAction::~JMQRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JMQRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  
  // Open an output file
  G4String fileName = "JMQ";
  analysisManager->OpenFile(fileName);

  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JMQRunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if ( nofEvents == 0 ){
        G4cout << "nofEvents = " << nofEvents << G4endl;
        return;
    }

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


