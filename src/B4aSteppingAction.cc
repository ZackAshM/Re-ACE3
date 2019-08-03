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
// $Id: B4aSteppingAction.cc 68058 2013-03-13 14:47:43Z gcosmo $
// 
/// \file B4aSteppingAction.cc
/// \brief Implementation of the B4aSteppingAction class

#include "B4aSteppingAction.hh"
#include "B4aEventAction.hh"
#include "B4DetectorConstruction.hh"
#include "B4Analysis.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aSteppingAction::B4aSteppingAction(
                      const B4DetectorConstruction* detectorConstruction,
                      B4aEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4aSteppingAction::~B4aSteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4aSteppingAction::UserSteppingAction(const G4Step* step)
{
    
// get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();   
  
// Collect energy and track length step by step

  // get volume of the current step
  G4VPhysicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  
  // step length
  G4double stepLength = 0.;
  G4double projStepLength = 0.;
  G4double trackCosTheta = 0.;
  G4double Rhit = 0;
  G4double Thit = 0*ns;
  G4double twopi = 2.*3.141592636;
  G4double dR = 0.25*mm;
  G4double Chit=0;
  G4double Csign = 0.0;
  G4double Etrack = 0.0;
  G4StepPoint* postStepPoint = step->GetPostStepPoint();
  
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
// Get oriented steps: positrons subtract from electrons
 //   if(step->GetTrack()->GetDefinition()->GetPDGCharge() < 0.0) stepLength = step->GetStepLength();
 //   if(step->GetTrack()->GetDefinition()->GetPDGCharge() > 0.0) stepLength = -step->GetStepLength();   
 //  trackCosTheta = (step->GetTrack()->GetMomentumDirection().cosTheta());
   // Projected net negative (eg. electron excess) step length
 //   projStepLength = stepLength*trackCosTheta;  
    projStepLength = stepLength;     
  }
  
//   // this section added to count particles------------
 
 
 
 
//   G4double inparticlecount=0, outparticlecount=0;
//   if(step->GetTrack()->GetParentID() == 0) {
//     G4StepPoint* point = step->GetPostStepPoint();
//     G4StepPoint* point2 = step->GetPreStepPoint();
//     G4VPhysicalVolume* thePostPV = point->GetPhysicalVolume();
//     G4VPhysicalVolume* thePrePV = point2->GetPhysicalVolume();
//  
//     if(thePrePV->GetName()=="Abso" && thePostPV->GetName()=="Culayer") {
//     inparticlecount += 1.0;
//     }
//  
//     if(thePrePV->GetName()=="Culayer" && thePostPV->GetName()=="Gap") {
//     outparticlecount += 1.0;
//     }
//   }
//     G4cout<<"inparticles= "<<inparticlecount<<" outparticles= "<<outparticlecount<<"\n";
//   // end of particle counting section....................
// 

// // Copper target
//   if ( volume == fDetConstruction->GetCutargetPV() ) {
//     fEventAction->AddTarget(edep,projStepLength);
//      if((postStepPoint->GetStepStatus() == fGeomBoundary) &&
//         (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)&&
//        (postStepPoint->GetMaterial() == G4Material::GetMaterial("Galactic"))) {
//   //       G4cout << "Step ends on geom boundary" << G4endl;
//     Etrack = step->GetTrack()->GetKineticEnergy();
//     G4cout << "Etrack= " << Etrack/GeV << " GeV"<< G4endl;
//      fEventAction->AddTargetHit();
//     // analysisManager->FillH2(1,postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y() );  
//      }       
//    //   fEventAction->AddTarget(edep,posLength);      
//   }

// Tungsten input layer
  if ( volume == fDetConstruction->GetAbsorberPV() ) {
    fEventAction->AddAbs(edep,projStepLength);
     if((postStepPoint->GetStepStatus() == fGeomBoundary) &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)&&
       (postStepPoint->GetMaterial() == G4Material::GetMaterial("G4_Cu"))) {
  //       G4cout << "Step ends on geom boundary" << G4endl;
     fEventAction->AddAbsHit();
     analysisManager->FillH2(1,postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y() );  
     }       
 //     fEventAction->AddAbs(edep,posLength);      
  }
  
 
 //  ACE1
  if ( volume == fDetConstruction->GetACE1PV() ) {
    fEventAction->AddGap(edep,projStepLength);
    if((postStepPoint->GetStepStatus() == fGeomBoundary) &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) &&
       (postStepPoint->GetPosition().z()-3.12*mm > fDetConstruction->GetACE1PV()->GetTranslation().z()) ) {
     fEventAction->AddGapHit();
     Chit = step->GetTrack()->GetDefinition()->GetPDGCharge();
     Csign = G4double((Chit>0) - (Chit<0));    
    //G4cout << "Csign= "<< Csign << G4endl;
     analysisManager->FillH2(2, postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y(), -Chit);
     analysisManager->FillH2(5, postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y());   
     Rhit = std::hypot(postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y());
     analysisManager->FillH1(7, Rhit, -Csign*1./(twopi*Rhit*dR) );    
     Thit = postStepPoint->GetGlobalTime()/ps;
     analysisManager->FillH1(10, Thit );     
     }        
  }

//  ACE2
  if ( volume == fDetConstruction->GetACE2PV() ) {
    if((postStepPoint->GetStepStatus() == fGeomBoundary) &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) &&
    (postStepPoint->GetPosition().z()-3.12*mm > fDetConstruction->GetACE2PV()->GetTranslation().z()) ) {
     Chit = step->GetTrack()->GetDefinition()->GetPDGCharge();  
     Csign = G4double((Chit>0) - (Chit<0));      
     analysisManager->FillH2(3, postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y(), -Chit);
     analysisManager->FillH2(6, postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y());       
     Rhit = std::hypot(postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y()); 
     analysisManager->FillH1(8, Rhit, -Csign*1./(twopi*Rhit*dR));
      Thit = postStepPoint->GetGlobalTime()/ps;
     analysisManager->FillH1(11, Thit);        
    }        
  }  
 
 //  ACE3
  if ( volume == fDetConstruction->GetACE3PV() ) {
    if((postStepPoint->GetStepStatus() == fGeomBoundary) &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) &&
    (postStepPoint->GetPosition().z()-3.12*mm > fDetConstruction->GetACE3PV()->GetTranslation().z()) ) {    
     Chit = step->GetTrack()->GetDefinition()->GetPDGCharge();
     Csign = G4double((Chit>0) - (Chit<0));      
     analysisManager->FillH2(4, postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y(), -Chit );
     analysisManager->FillH2(7, postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y());        
     Rhit = std::hypot(postStepPoint->GetPosition().x(),postStepPoint->GetPosition().y());   
 
     analysisManager->FillH1(9, Rhit, -Csign*1./(twopi*Rhit*dR));
      Thit = postStepPoint->GetGlobalTime()/ps;
     analysisManager->FillH1(12, Thit);        
    }             
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
