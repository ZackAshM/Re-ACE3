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
// $Id: B4DetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4DetectorConstruction.hh
/// \brief Definition of the B4DetectorConstruction class

#ifndef B4DetectorConstruction_h
#define B4DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class B4DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4DetectorConstruction();
    virtual ~B4DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // get methods
    //
    const G4VPhysicalVolume* GetAbsorberPV() const;
    const G4VPhysicalVolume* GetACE1PV() const;
    const G4VPhysicalVolume* GetACE2PV() const;
    const G4VPhysicalVolume* GetACE3PV() const;
    
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
    
    G4VPhysicalVolume*   fBeamPipeSpacePV;
    G4VPhysicalVolume*   fepixPV;
    G4VPhysicalVolume*   fepix2mppcSpacePV;
    G4VPhysicalVolume*   fmppcWall1PV;
    G4VPhysicalVolume*   fmppcQuartzPV;
    G4VPhysicalVolume*   fmppcWall2PV;
    G4VPhysicalVolume*   fmppc2WSpacePV;
    G4VPhysicalVolume*   fAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*   fW2Dwall1SpacePV;
    G4VPhysicalVolume*   fDwall1PV;
    G4VPhysicalVolume*   fDwallSpacePV;
    G4VPhysicalVolume*   fDwall2PV;
    G4VPhysicalVolume*   fDbellySpacePV;
    G4VPhysicalVolume*   fWlayerPV;
    G4VPhysicalVolume*   fCulayerPVc0;
    G4VPhysicalVolume*   fACE1PV;      // ACE1 physical volume
    G4VPhysicalVolume*   fCulayerPVc1;
    G4VPhysicalVolume*   fspacePVc0;
    G4VPhysicalVolume*   fWlayerPVc2;   
    G4VPhysicalVolume*   fCulayerPVc2;
    G4VPhysicalVolume*   fACE2PV;
    G4VPhysicalVolume*   fCulayerPVc3;
    G4VPhysicalVolume*   fspacePVc1;
    G4VPhysicalVolume*   fWlayerPVc4;   
    G4VPhysicalVolume*   fCulayerPVc4;
    G4VPhysicalVolume*   fACE3PV;
    G4VPhysicalVolume*   fCulayerPVc5;  

    
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions


inline const G4VPhysicalVolume* B4DetectorConstruction::GetAbsorberPV() const { 
  return fAbsorberPV; 
}

inline const G4VPhysicalVolume* B4DetectorConstruction::GetACE1PV() const  { 
  return fACE1PV; 
}

inline const G4VPhysicalVolume* B4DetectorConstruction::GetACE2PV() const  { 
  return fACE2PV; 
}

inline const G4VPhysicalVolume* B4DetectorConstruction::GetACE3PV() const  { 
  return fACE3PV; 
}
     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

