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
// $Id: B4DetectorConstruction.cc 87359 2014-12-01 16:04:27Z gcosmo $
// 
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UnitsTable.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* B4DetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fAbsorberPV(0),
   fACE1PV(0),
   fACE2PV(0),
   fACE3PV(0),   
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials()
{ 
  // Iron material defined using NIST Manager
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Fe");
  // Nickel material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_Ni");
  // Tungsten material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_W");  
  // Aluminum Oxide material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_ALUMINUM_OXIDE"); 
  // Silicon DiOxide material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE"); 
   // Silicon  material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_Si"); 
  // Copper material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_Cu"); 
  // Aluminum material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_Al");  
  // liquid N2 material defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_lN2");   
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  G4double fracMass;
  G4int ncomp;
  G4String name, symbol;             // a=mass of a mole;
  
  G4Element* elH  = new G4Element("Hydrogen",symbol="H" , 1., 1.01*g/mole);
  G4Element* elC  = new G4Element("Carbon"  ,symbol="C" , 6.,  12.01*g/mole);
  G4Element* elN  = new G4Element("Nitrogen",symbol="N" , 7., 14.01*g/mole);
  G4Element* elO  = new G4Element("Oxygen"  ,symbol="O" , 8., 16.00*g/mole);
  //G4Element* elSi  = new G4Element("Silicon"  ,symbol="Si" , 14., 28.085*g/mole);
 // G4Element* Al = new G4Element("Aluminum", "Al", z=13, a= 26.982*g/mole);
  
  a = 55.85*g/mole;
  G4Element* elFe = new G4Element(name="Iron"    ,symbol="Fe", z=26., a);

  a = 183.84*g/mole;
  G4Element* elW = new G4Element(name="Tungsten" ,symbol="W",  z=74., a);
  
  a =  58.6934*g/mole;
  G4Element* elNi = new G4Element(name="Nickel" ,symbol="Ni",  z=28., a);  
  
    G4Material *Air = new G4Material("Air", density= 1.29*mg/cm3, ncomp=2);
   Air->AddElement(elN, fracMass= 70.*perCent);
   Air->AddElement(elO, fracMass = 30.*perCent);
  
//  G4Material *Air = new G4Material("Air", density= 1.29*mg/cm3, ncomp=2);
//   Air->AddMaterial(nistManager->FindOrBuildMaterial("elN"), 70.*perCent);
//   Air->AddMaterial(nistManager->FindOrBuildMaterial("elO"), 30.*perCent);
  
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density
  
  new G4Material("LHe", z=2, a= 4.0026*g/mole, density = 0.125*g/cm3);

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);
  
  G4Material* Walloy = new G4Material("EF17tungstenAlloy",density= 17.0*g/cm3,ncomp=3);
    Walloy->AddElement(elW,fracMass = 90*perCent);
    Walloy->AddElement(elFe,fracMass = 3*perCent);
    Walloy->AddElement(elNi,fracMass = 7*perCent);  
    
   G4Material* nylon6 = new G4Material("nylon6",density= 1.13*g/cm3,ncomp=4);
    nylon6->AddElement(elC,fracMass = 63.68*perCent);
    nylon6->AddElement(elH,fracMass = 9.79*perCent);
    nylon6->AddElement(elN,fracMass = 12.37*perCent);  
    nylon6->AddElement(elO,fracMass = 14.14*perCent);  
    
   //G4Material* quartz = G4Material::GetMaterial("G4_SILICON_DIOXIDE"); 
   //G4Material *quartz = new G4Material("quartz", density=2.32*g/cm3, ncomp=1);
   //   quartz->AddMaterial( G4_SILICON_DIOXIDE, 100.0*perCent ); 
    
   //G4Material *silicon = G4Material::GetMaterial("G4_Si");
      //silicon->AddMaterial(elSi, 100.0*perCent ); 
      
   //G4Material *aluminum = G4Material::GetMaterial("G4_Al");
     // aluminum->AddMaterial(elAl, 100.0*perCent );      

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
 // G4int nofLayers = 12;
//   G4double WThickness = 15.*mm;
//   G4double W2Thickness = 10.*mm;  
//   G4double CuThickness = 1.0*mm;  
//   G4double Al2O3Thickness =  6.25*mm;
//   G4double spaceThickness =  66.5*mm;  
//   G4double calorSizeX  = 1.25*cm;
//   G4double calorSizeY  = 12.5*cm;  
  
  G4double BeamPipeSpaceThickness = 422.275*mm; 
  G4double epixThickness = 5.0*mm;  // don't actually know this one!
  G4double epix2mppcSpaceThickness = 190.5*mm;
  G4double mppcWall1Thickness = 13.56*mm;
  G4double mppcQuartzThickness = 6*mm;
  G4double mppcWall2Thickness = 5.89*mm;
  G4double mppc2WSpaceThickness = 80*mm;
  G4double WThickness = 15*mm; 
  G4double W2Dwall1SpaceThickness = 0.1*mm;//49.3*mm;
  //G4double W2Dwall1SpaceThickness = 0.1*mm;
  G4double Dwall1Thickness = 3.04*mm;
  G4double DwallSpaceThickness = 0.1*mm;//50*mm;
  //G4double DwallSpaceThickness = 0.1*mm;
  G4double Dwall2Thickness = 2.0*mm;
  G4double DbellySpaceThickness = 0.1*mm;//139.9*mm;
  //G4double DbellySpaceThickness = 0.1*mm;
  G4double CuThickness = 1.0*mm;  
  G4double Al2O3Thickness =  6.25*mm;
  G4double spaceThickness =  0.1*mm;  
  
  G4double calorSizeX  = 1.25*cm;
  G4double calorSizeY  = 12.5*cm;  

  //G4double layerThickness = absoThickness + gapThickness;
  //G4double calorThickness = nofLayers * layerThickness;
  G4double calorThickness =  BeamPipeSpaceThickness+epixThickness
                               +epix2mppcSpaceThickness+mppcWall1Thickness
                                 +mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness
                                 +Al2O3Thickness+CuThickness+spaceThickness+CuThickness+Al2O3Thickness+CuThickness;
  G4double worldSizeX = 1.2 * calorSizeX;
  G4double worldSizeY = 1.2 * calorSizeY;  
  G4double worldSizeZ  = 1.2 * calorThickness; 
  
  // Get materials test
  G4Material* defaultMaterial = G4Material::GetMaterial("Galactic");
  G4Material* WMaterial = G4Material::GetMaterial("G4_W");
  G4Material* Walloy = G4Material::GetMaterial("EF17tungstenAlloy");
  G4Material* Al2O3Material = G4Material::GetMaterial("G4_ALUMINUM_OXIDE");
  G4Material* quartzMaterial = G4Material::GetMaterial("G4_SILICON_DIOXIDE");
  G4Material* CuMaterial = G4Material::GetMaterial("G4_Cu");
  G4Material* nylonMaterial = G4Material::GetMaterial("nylon6");
  G4Material* vacuum = G4Material::GetMaterial("Galactic"); 
  G4Material* LHeMaterial = G4Material::GetMaterial("LHe");
  G4Material* siliconMaterial = G4Material::GetMaterial("G4_Si");
  G4Material* airMaterial = G4Material::GetMaterial("Air");
  G4Material* AlMaterial = G4Material::GetMaterial("G4_Al");
  
  if ( !defaultMaterial || ! WMaterial || ! Al2O3Material || ! CuMaterial  
        || ! Walloy || ! nylonMaterial || ! vacuum  
       || ! LHeMaterial || ! siliconMaterial || ! airMaterial || ! AlMaterial) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("B4DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  }  
  
  //G4cout << "End of materials definition, start detector volumes" << G4endl;
   
  
  //     
  // World ---------------------------------------------
  //
  G4VSolid* worldS 
    = new G4Box("World",           // its name
                 worldSizeX/2, worldSizeY/2, worldSizeZ/2); // its size
                         
  G4LogicalVolume* worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                               
  // Calorimeter  ---------------------------------------------
  //  
  G4VSolid* calorimeterS
    = new G4Box("Calorimeter",     // its name
                 calorSizeX/2, calorSizeY/2, calorThickness/2); // its size
                         
  G4LogicalVolume* calorLV
    = new G4LogicalVolume(
                 calorimeterS,     // its solid
                 defaultMaterial,  // its material
                 "Calorimeter");   // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 calorLV,          // its logical volume                         
                 "Calorimeter",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  //                                 
  // Space from beam pipe to ePix100 camera ---------------------------------------------
  //
  G4VSolid* BeamPipeSpaceS 
    = new G4Box("BeamPipeSpace",           // its name
                 calorSizeX/2, calorSizeY/2, BeamPipeSpaceThickness/2); // its size
  G4LogicalVolume* BeamPipeSpaceLV
    = new G4LogicalVolume(
                 BeamPipeSpaceS,           // its solid
                 airMaterial,  // its material
                 "BeamPipeSpace");         // its name
  fBeamPipeSpacePV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness/2), // its position
                 BeamPipeSpaceLV,       // its logical volume                         
                 "BeamPipeSpace",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
    
  //                                 
  // ePix100 camera ---------------------------------------------
  //
  G4VSolid* epixS 
    = new G4Box("epix",           // its name
                 calorSizeX/2, calorSizeY/2, epixThickness/2); // its size
                         
  G4LogicalVolume* epixLV
    = new G4LogicalVolume(
                 epixS,           // its solid
                 siliconMaterial,  // its material
                 "epix");         // its name
    
  fepixPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness/2), // its position
                 epixLV,       // its logical volume                         
                 "epix",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
  //                                 
  // Space after ePix100 camera to mppc---------------------------------------------
  //
  G4VSolid* epix2mppcSpaceS 
    = new G4Box("epix2mppcSpace",           // its name
                 calorSizeX/2, calorSizeY/2, epix2mppcSpaceThickness/2); // its size
                         
  G4LogicalVolume* epix2mppcSpaceLV
    = new G4LogicalVolume(
                 epix2mppcSpaceS,           // its solid
                 airMaterial,  // its material
                 "epix2mppcSpace");         // its name
    
  fepix2mppcSpacePV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                                 epix2mppcSpaceThickness/2), // its position
                 epix2mppcSpaceLV,       // its logical volume                         
                 "epix2mppcSpace",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                                 
  // mppc wall 1 ---------------------------------------------
  //
  G4VSolid* mppcWall1S 
    = new G4Box("mppcWall1",           // its name
                 calorSizeX/2, calorSizeY/2, mppcWall1Thickness/2); // its size
                         
  G4LogicalVolume* mppcWall1LV
    = new G4LogicalVolume(
                 mppcWall1S,           // its solid
                 nylonMaterial,  // its material
                 "mppcWall1");         // its name
    
  fmppcWall1PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                                 +epix2mppcSpaceThickness+mppcWall1Thickness/2), // its position
                 mppcWall1LV,       // its logical volume                         
                 "mppcWall1",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
                  
  //                                 
  // mppc quartz ---------------------------------------------
  //
  G4VSolid* mppcQuartzS 
    = new G4Box("mppcQuartz",           // its name
                 calorSizeX/2, calorSizeY/2, mppcQuartzThickness/2); // its size
                         
  G4LogicalVolume* mppcQuartzLV
    = new G4LogicalVolume(
                 mppcQuartzS,           // its solid
                 quartzMaterial,  // its material
                 "mppcQuartz");         // its name
    
  fmppcQuartzPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                                 +epix2mppcSpaceThickness+mppcWall1Thickness+mppcQuartzThickness/2), // its position
                 mppcQuartzLV,       // its logical volume                         
                 "mppcQuartz",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
                  
  //                                 
  // mppc wall2 ---------------------------------------------
  //
  G4VSolid* mppcWall2S 
    = new G4Box("mppcWall2",           // its name
                 calorSizeX/2, calorSizeY/2, mppcWall2Thickness/2); // its size
                         
  G4LogicalVolume* mppcWall2LV
    = new G4LogicalVolume(
                 mppcWall2S,           // its solid
                 nylonMaterial,  // its material
                 "mppcWall2");         // its name
    
  fmppcWall2PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                                 +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness/2), // its position
                 mppcWall2LV,       // its logical volume                         
                 "mppcWall2",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  //                                 
  // mppc to tungsten space ---------------------------------------------
  //
  G4VSolid* mppc2WSpaceS 
    = new G4Box("mppc2WSpace",           // its name
                 calorSizeX/2, calorSizeY/2, mppc2WSpaceThickness/2); // its size
                         
  G4LogicalVolume* mppc2WSpaceLV
    = new G4LogicalVolume(
                 mppc2WSpaceS,           // its solid
                 airMaterial,  // its material
                 "mppc2WSpace");         // its name
    
  fmppc2WSpacePV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                                 +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness/2), // its position
                 mppc2WSpaceLV,       // its logical volume                         
                 "mppc2WSpace",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps               
  //                                 
  // Tungsten Layer 1
  //
  G4VSolid* WlayerS 
    = new G4Box("Abso",           // its name
                 calorSizeX/2, calorSizeY/2, WThickness/2); // its size
                         
  G4LogicalVolume* WlayerLV
    = new G4LogicalVolume(
                 WlayerS,           // its solid
                 Walloy,  // its material
                 "Abso");         // its name
    
  fAbsorberPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness + WThickness/2), // its position
                 WlayerLV,       // its logical volume                         
                 "Abso",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
  //                                 
  // Tungsten to dewar space ----------------------------------------
  //
  G4VSolid* W2Dwall1SpaceS 
    = new G4Box("W2Dwall1Space",           // its name
                 calorSizeX/2, calorSizeY/2, W2Dwall1SpaceThickness/2); // its size
                         
  G4LogicalVolume* W2Dwall1SpaceLV
    = new G4LogicalVolume(
                 W2Dwall1SpaceS,           // its solid
                 airMaterial,  // its material
                 "W2Dwall1Space");         // its name
    
  fW2Dwall1SpacePV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness/2 ), // its position
                 W2Dwall1SpaceLV,       // its logical volume                         
                 "W2Dwall1Space",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
  //                                 
  // Dewar Al wall ----------------------------------------
  //
  G4VSolid* Dwall1S 
    = new G4Box("Dwall1",           // its name
                 calorSizeX/2, calorSizeY/2, Dwall1Thickness/2); // its size
                         
  G4LogicalVolume* Dwall1LV
    = new G4LogicalVolume(
                 Dwall1S,           // its solid
                 AlMaterial,  // its material
                 "Dwall1");         // its name
    
  fDwall1PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness/2 ), // its position
                 Dwall1LV,       // its logical volume                         
                 "Dwall1",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
 
  //                                 
  // Dewar space between walls ----------------------------------------
  //
  G4VSolid* DwallSpaceS 
    = new G4Box("DwallSpace",           // its name
                 calorSizeX/2, calorSizeY/2, DwallSpaceThickness/2); // its size
                         
  G4LogicalVolume* DwallSpaceLV
    = new G4LogicalVolume(
                 DwallSpaceS,           // its solid
                 vacuum,  // its material
                 "DwallSpace");         // its name
    
  fDwallSpacePV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness/2 ), // its position
                 DwallSpaceLV,       // its logical volume                         
                 "DwallSpace",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps    
    
  //                                 
  // Dewar inner wall  ----------------------------------------
  //
  G4VSolid* Dwall2S 
    = new G4Box("Dwall2",           // its name
                 calorSizeX/2, calorSizeY/2, Dwall2Thickness/2); // its size
                         
  G4LogicalVolume* Dwall2LV
    = new G4LogicalVolume(
                 Dwall2S,           // its solid
                 AlMaterial,  // its material
                 "Dwall2");         // its name
    
  fDwall2PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness/2 ), // its position
                 Dwall2LV,       // its logical volume                         
                 "Dwall2",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps    
    
  //                                 
  // Dewar belly space to ACE1  ----------------------------------------
  //
  G4VSolid* DbellySpaceS 
    = new G4Box("DbellySpace",           // its name
                 calorSizeX/2, calorSizeY/2, DbellySpaceThickness/2); // its size
                         
  G4LogicalVolume* DbellySpaceLV
    = new G4LogicalVolume(
                 DbellySpaceS,           // its solid
                 LHeMaterial,  // its material
                 "DbellySpace");         // its name
    
  fDbellySpacePV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness/2 ), // its position
                 DbellySpaceLV,       // its logical volume                         
                 "DbellySpace",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps    
    
             

  //                                 
  // 1st waveguide input Copper Layer
  //
  G4VSolid* CulayerSc0 
    = new G4Box("CuLayer",           // its name
                 calorSizeX/2, calorSizeY/2, CuThickness/2); // its size
                         
  G4LogicalVolume* CulayerLVc0
    = new G4LogicalVolume(
                 CulayerSc0,           // its solid
                 CuMaterial,  // its material
                 "CuLayer");         // its name
    
  fCulayerPVc0
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                                -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness+CuThickness/2), // its position
                 CulayerLVc0,       // its logical volume                         
                 "Culayer",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
  
  //                               
  // 1st waveguide Alumina layer
  //
  G4VSolid* AlumSc0
    = new G4Box("ACE1",            // its name
                 calorSizeX/2, calorSizeY/2, Al2O3Thickness/2); // its size
                         
  G4LogicalVolume* AlumLVc0
    = new G4LogicalVolume(
                 AlumSc0,        // its solid
                 Al2O3Material, // its material
                 "ACE1");          // its name
                                   
  fACE1PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                  -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness/2), // its position
                 AlumLVc0,       // its logical volume                         
                 "ACE1",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                                 
  // 1st waveguide output Copper Layer
  //
  G4VSolid* CulayerSc1 
    = new G4Box("CuLayer",           // its name
                 calorSizeX/2, calorSizeY/2, CuThickness/2); // its size
                         
  G4LogicalVolume* CulayerLVc1
    = new G4LogicalVolume(
                 CulayerSc1,           // its solid
                 CuMaterial,  // its material
                 "CuLayer");         // its name
    
  fCulayerPVc1
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness/2), // its position
                 CulayerLVc1,       // its logical volume                         
                 "Culayer",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
     
  //                               
  // 1st Space between waveguides
  //
  G4VSolid* spaceSc0
    = new G4Box("Space",             // its name
                 calorSizeX/2, calorSizeY/2, spaceThickness/2); // its size
                         
  G4LogicalVolume* spaceLVc0
    = new G4LogicalVolume(
                 spaceSc0,             // its solid
                 LHeMaterial,      // its material
                 "Space");           // its name
                                   
  fspacePVc0
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0.,-calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness/2 ), // its position
                 spaceLVc0,            // its logical volume                         
                 "Space",            // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  
  //                                 
  // 2nd waveguide input Copper Layer
  //
  G4VSolid* CulayerSc2 
    = new G4Box("CuLayer",           // its name
                 calorSizeX/2, calorSizeY/2, CuThickness/2); // its size
                         
  G4LogicalVolume* CulayerLVc2
    = new G4LogicalVolume(
                 CulayerSc2,           // its solid
                 CuMaterial,  // its material
                 "CuLayer");         // its name
    
  fCulayerPVc2
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness/2), // its position
                 CulayerLVc2,       // its logical volume                         
                 "Culayer",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 2,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
  
  //                               
  // 2nd waveguide Alumina layer
  //
  G4VSolid* AlumSc1 
    = new G4Box("ACE2",            // its name
                 calorSizeX/2, calorSizeY/2, Al2O3Thickness/2); // its size
                         
  G4LogicalVolume* AlumLVc1
    = new G4LogicalVolume(
                 AlumSc1,        // its solid
                 Al2O3Material, // its material
                 "ACE2");          // its name
                                   
  fACE2PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness+Al2O3Thickness/2), // its position
                 AlumLVc1,       // its logical volume                         
                 "ACE2",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                                 
  // 2nd waveguide output Copper Layer
  //
  G4VSolid* CulayerSc3 
    = new G4Box("CuLayer",           // its name
                 calorSizeX/2, calorSizeY/2, CuThickness/2); // its size
                         
  G4LogicalVolume* CulayerLVc3
    = new G4LogicalVolume(
                 CulayerSc3,           // its solid
                 CuMaterial,  // its material
                 "CuLayer");         // its name
    
  fCulayerPVc3
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness
                                 +Al2O3Thickness+CuThickness/2), // its position
                 CulayerLVc3,       // its logical volume                         
                 "Culayer",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 3,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
     
  //                               
  // 2nd Space between waveguides
  //
  G4VSolid* spaceSc1
    = new G4Box("Space",             // its name
                 calorSizeX/2, calorSizeY/2, spaceThickness/2); // its size
                         
  G4LogicalVolume* spaceLVc1
    = new G4LogicalVolume(
                 spaceSc1,             // its solid
                 LHeMaterial,      // its material
                 "Space");           // its name
                                   
  fspacePVc1
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0.,
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness
                                 +Al2O3Thickness+CuThickness+spaceThickness/2), // its position
                 spaceLVc1,            // its logical volume                         
                 "Space",            // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps 
 
  //                                 
  // 3rd waveguide input Copper Layer
  //
  G4VSolid* CulayerSc4 
    = new G4Box("CuLayer",           // its name
                 calorSizeX/2, calorSizeY/2, CuThickness/2); // its size
                         
  G4LogicalVolume* CulayerLVc4
    = new G4LogicalVolume(
                 CulayerSc4,           // its solid
                 CuMaterial,  // its material
                 "CuLayer");         // its name
    
  fCulayerPVc4
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness
                                 +Al2O3Thickness+CuThickness+spaceThickness+CuThickness/2), // its position
                 CulayerLVc4,       // its logical volume                         
                 "Culayer",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 4,                // copy number
                 fCheckOverlaps);  // checking overlaps     

//                               
// 3rd waveguide Alumina layer
//
  G4VSolid* AlumSc2 
    = new G4Box("ACE3",            // its name
                 calorSizeX/2, calorSizeY/2, Al2O3Thickness/2); // its size
                         
  G4LogicalVolume* AlumLVc2
    = new G4LogicalVolume(
                 AlumSc2,        // its solid
                 Al2O3Material, // its material
                 "ACE3");          // its name
                                   
  fACE3PV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness
                                 +Al2O3Thickness+CuThickness+spaceThickness+CuThickness+Al2O3Thickness/2 ), // its position
                 AlumLVc2,       // its logical volume                         
                 "ACE3",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                                 
  // 3rd waveguide output Copper Layer
  //
  G4VSolid* CulayerSc5 
    = new G4Box("CuLayer",           // its name
                 calorSizeX/2, calorSizeY/2, CuThickness/2); // its size
                         
  G4LogicalVolume* CulayerLVc5
    = new G4LogicalVolume(
                 CulayerSc5,           // its solid
                 CuMaterial,  // its material
                 "CuLayer");         // its name
    
  fCulayerPVc5
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., 
                               -calorThickness/2+BeamPipeSpaceThickness+epixThickness+
                               +epix2mppcSpaceThickness+mppcWall1Thickness+
                                 mppcQuartzThickness+mppcWall2Thickness+mppc2WSpaceThickness
                                  + WThickness + W2Dwall1SpaceThickness
                                 +Dwall1Thickness+DwallSpaceThickness+Dwall2Thickness+DbellySpaceThickness
                                 +CuThickness+Al2O3Thickness+CuThickness+spaceThickness+CuThickness
                                 +Al2O3Thickness+CuThickness+spaceThickness+CuThickness+Al2O3Thickness+CuThickness/2), // its position
                 CulayerLVc5,       // its logical volume                         
                 "Culayer",           // its name
                 calorLV,          // its mother  volume
                 false,            // no boolean operation
                 5,                // copy number
                 fCheckOverlaps);  // checking overlaps     
   
  //
  // print parameters
  //
//   G4cout
//     << G4endl 
//     << "------------------------------------------------------------" << G4endl
//     << "---> The calorimeter is " << nofLayers << " layers of: [ "
//     << absoThickness/mm << "mm of " << absorberMaterial->GetName() 
//     << " + "
//     << gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
//     << "------------------------------------------------------------" << G4endl;
//   
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::Invisible);

  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  calorLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
