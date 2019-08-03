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
// $Id: B4aEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4aEventAction.hh
/// \brief Definition of the B4aEventAction class

#ifndef B4aEventAction_h
#define B4aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class B4aEventAction : public G4UserEventAction
{
  public:
    B4aEventAction();
    virtual ~B4aEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void AddTarget(G4double de, G4double dl);
    void AddAbs(G4double de, G4double dl);
    void AddGap(G4double de, G4double dl);
    void AddNAbs(G4double de, G4double dl);   
    void AddNGap(G4double outp, G4double inp);
    void AddTargetHit();  
    void AddAbsHit();   
    void AddGapHit();
    void AbsHitx(G4double x); 
    void AbsHity(G4double y);
    void GapHitx(G4double x); 
    void GapHity(G4double y);

  private:
    G4double  fEnergyTarget;  
    G4double  fEnergyAbs;
    G4double  fEnergyGap;
    G4double  fTrackLTarget; 
    G4double  fTrackLAbs; 
    G4double  fTrackLGap;
    G4double  fTargetHit;
    G4double  fAbsHit;
    G4double  fGapHit;
    G4double  fAbsHitx;
    G4double  fAbsHity;
    G4double  fGapHitx;
    G4double  fGapHity;      
/*    G4double  fNpartLAbsOut; 
    G4double  fNpartLGapIn;  */  
};

// inline functions

inline void B4aEventAction::AddTarget(G4double de, G4double dl) {
  fEnergyTarget += de; 
  fTrackLTarget += dl;
}

inline void B4aEventAction::AddAbs(G4double de, G4double dl) {
  fEnergyAbs += de; 
  fTrackLAbs += dl;
}

inline void B4aEventAction::AddGap(G4double de, G4double dl) {
  fEnergyGap += de; 
  fTrackLGap += dl;
}

inline void B4aEventAction::AddTargetHit() {
  fTargetHit += 1.0;
}

inline void B4aEventAction::AddAbsHit() {
  fAbsHit += 1.0;
}

inline void B4aEventAction::AddGapHit() {
  fGapHit += 1.0;
}

inline void B4aEventAction::AbsHitx(G4double x) {
  fAbsHitx = x;
}
inline void B4aEventAction::AbsHity(G4double y) {
  fAbsHity = y;
}
inline void B4aEventAction::GapHitx(G4double x) {
  fGapHitx = x;
}
inline void B4aEventAction::GapHity(G4double y) {
  fGapHity = y;
}



// inline void B4aEventAction::AddNAbsOut(G4double outp, G4double inp) {
//   fNpartLAbsOut += outp; 
// }
// 
// inline void B4aEventAction::AddNGapIn(G4double outp, G4double inp) {
//   fNpartLGapIn += inp;
// }
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
