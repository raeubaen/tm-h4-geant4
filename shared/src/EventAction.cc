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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"

#include "CLHEP/Units/SystemOfUnits.h"

using namespace std;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run, HistoManager* histo)
: fRunAct(run),fHistoManager(histo)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction() = default;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) {
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
  }

  string *vars = fHistoManager->GetVars();
  for(int i=0; i<fHistoManager->GetNvars(); i++)
    fMap[vars[i]] = (vector<float>){};

  fNpart = 0;
  fFillNeg = 0;
  fFillPos = 0;
  fTotPos=0;
  fTotNeg=0;
  fTotEnergy=0;
  fChargEnergy=0;
  for(int i=0; i<1; i++) fTotHit[i]==0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{

  fHistoManager->FillNtuple(fMap, fNpart);
  //fill ntuple
  //

}

void EventAction::AddPart(const G4int trackID, const G4ThreeVector p, const G4ParticleDefinition * part, const G4double en, const G4double x, const G4double y, const G4double z){

  if (en < 50 ) return;
  if (part->GetPDGCharge() < 0 ) fFillNeg += 1;
  if (part->GetPDGCharge() > 0 ) fFillPos += 1;
  if (part->GetPDGCharge() > 0) fTotPos += 1;
  if (part->GetPDGCharge() < 0) fTotNeg += 1;
  for(int i=0; i<1; i++) if(z == fZpos[i]) fTotHit[i] += 1;

  map<string, float> partMap = {{"phi", p.phi()}, {"theta", p.theta()},
    {"en", en}, {"mass", part->GetPDGMass()}, {"part", part->GetPDGEncoding()}, {"charge", part->GetPDGCharge()}, {"x", x}, {"y", y}, {"z", z}};

  string *vars = fHistoManager->GetVars();
  for(int i=0; i<fHistoManager->GetNvars(); i++)
    fMap[vars[i]].push_back(partMap[vars[i]]);

  fNpart ++;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
