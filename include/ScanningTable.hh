#ifdef SCANNING
#ifndef ScanningTable_H
#define ScanningTable_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"

#include "CADMesh.hh"
#include "G4VisExtent.hh"

class ScanningTable 
{
  public:

  G4LogicalVolume *expHall_log;

  ScanningTable(G4LogicalVolume*,Materials*);
  ~ScanningTable();
  
  G4VPhysicalVolume *Construct();
  void SetCADPath(G4String pth) { CADModelPath = pth; }
  void SetIncludeCloverCart() { includeCloverCart = true; }
  void SetIncludeCartFrame() { includeCartFrame = true; }
  void SetIncludeSlitMount() { includeSlitMount = true; }
  void SetIncludeShield() { includeShield = true; }
  void SetXShift(G4double value) { xShift = value; }
  void SetYShift(G4double value) { yShift = value; }
  void SetZShift(G4double value) { zShift = value; }
  void Report();
  
    private:
  //flags
  G4bool includeCloverCart;
  G4bool includeCartFrame;
  G4bool includeSlitMount;
  G4bool includeShield;

  G4String CADModelPath;
  G4String SlitPart[10];
  G4String CartPart[37];
  G4String CollimatorPart[3];
  G4String SlitZAssemblyPart[23];
  G4String CloverAssemblyPart[6];
  G4String CartTopPart[9];
  int ZSlitParts;
  int CartParts;
  int CollimatorParts;
  int SlitZAssemblyParts;
  int CloverAssemblyParts;
  int CartTopParts;

  G4double xShift;
  G4double yShift;
  G4double zShift;
  
  //materials
  Materials* materials;
  G4Material* ZSlitMaterial[10];
  G4Material* CartMaterial[37];
  G4Material* CollimatorMaterial[3];
  G4Material* SlitZAssemblyMaterial[23];
  G4Material* CloverAssemblyMaterial[6];
  G4Material* CartTopMaterial[9];
  G4Material* material8020;
  G4Material* materialCartBase;
  G4Material* materialCartTop;
  G4Material* materialCartBack;
  G4Material* materialSlitBrackets;
  G4Material* materialSlits;
  G4Material* materialSlitAssembly;
  G4Material* materialTranslation;
  G4Material* materialTranslationAssembly;
  G4Material* materialCsCollimator;
  G4Material* materialClover;
  G4Material* materialCloverShield;

  //default position
  G4RotationMatrix NoRot;
  G4RotationMatrix Rot;
  G4ThreeVector *Pos0;

  //logical volume
  G4LogicalVolume* Cart_log;
  G4LogicalVolume* Cart8020_log;
  G4LogicalVolume* Collimator_log;
  G4LogicalVolume* CartBase_log;
  G4LogicalVolume* SlitZAssembly_log;
  G4LogicalVolume* CloverAssembly_log;
  G4LogicalVolume* CartTop_log;
  G4LogicalVolume* CartTopUBaseBottomLeft_log; 
  G4LogicalVolume* CartTopUBaseBottomMid_log;
  G4LogicalVolume* CartTopUBaseBottomRight_log;
  G4LogicalVolume* CartTopUBaseUpperLeft_log;
  G4LogicalVolume* CartTopUBaseUpperMid_log;
  G4LogicalVolume* CartTopUBaseUpperRight_log;
  G4LogicalVolume* CartTopFlange_log;
  G4LogicalVolume* CartTopPlate_log;
  G4LogicalVolume* CartTopBar_log;
  G4LogicalVolume* CartBack_log;
  G4LogicalVolume* Brake_log;
  G4LogicalVolume* ZSlit_log;
  G4LogicalVolume* ZSlitsLeftBracket_log;
  G4LogicalVolume* ZSlitsUpperLeftWall_log;
  G4LogicalVolume* ZSlitsMidLeftWall_log;
  G4LogicalVolume* ZSlitsLowerLeftWall_log;
  G4LogicalVolume* ZSlitsUpperRightWall_log;
  G4LogicalVolume* ZSlitsBottomBracket_log;
  G4LogicalVolume* ZSlitsMidRightWall_log;
  G4LogicalVolume* ZSlitsLowerRightWall_log;
  G4LogicalVolume* ZSlitsRightBracket_log;
  G4LogicalVolume* ZSlitsTopBracket_log;
  G4LogicalVolume* SlitAssembly_log;
  G4LogicalVolume* TranslateX_log;
  G4LogicalVolume* TranslateY_log;
  G4LogicalVolume* Translate_log;
  G4LogicalVolume* CsCollimatorBase_log;
  G4LogicalVolume* CsCollimatorBody_log;
  G4LogicalVolume* CsCollimatorPlug_log;
  G4LogicalVolume* CloverBase_log;
  G4LogicalVolume* CloverElevator_log;
  G4LogicalVolume* CloverRight_log;
  G4LogicalVolume* CloverLeft_log;
  G4LogicalVolume* CloverAssemblyLeftBase_log;
  G4LogicalVolume* CloverAssemblyLeftLeft_log;
  G4LogicalVolume* CloverAssemblyLeftRight_log;
  G4LogicalVolume* CloverAssemblyRightBase_log;
  G4LogicalVolume* CloverAssemblyRightLeft_log;
  G4LogicalVolume* CloverAssemblyRightRight_log;
  G4LogicalVolume* CloverRightShield_log;
  G4LogicalVolume* CloverLeftShield_log;
  
  //physical volume
  G4VPhysicalVolume* Cart_phys;
  G4VPhysicalVolume* Cart8020_phys;
  G4VPhysicalVolume* Collimator_phys;
  G4VPhysicalVolume* CartBase_phys;
  G4VPhysicalVolume* SlitZAssembly_phys;
  G4VPhysicalVolume* CloverAssembly_phys;
  G4VPhysicalVolume* CartTop_phys;
  G4VPhysicalVolume* CartTopUBaseBottomLeft_phys;
  G4VPhysicalVolume* CartTopUBaseBottomMid_phys;
  G4VPhysicalVolume* CartTopUBaseBottomRight_phys;
  G4VPhysicalVolume* CartTopUBaseUpperLeft_phys;
  G4VPhysicalVolume* CartTopUBaseUpperMid_phys;
  G4VPhysicalVolume* CartTopUBaseUpperRight_phys;
  G4VPhysicalVolume* CartTopFlange_phys;
  G4VPhysicalVolume* CartTopPlate_phys;
  G4VPhysicalVolume* CartTopBar_phys;
  G4VPhysicalVolume* CartBack_phys;
  G4VPhysicalVolume* Brake_phys;
  G4VPhysicalVolume* ZSlit_phys;
  G4VPhysicalVolume* ZSlitsLeftBracket_phys;
  G4VPhysicalVolume* SlitAssembly_phys;
  G4VPhysicalVolume* ZSlitsUpperLeftWall_phys;
  G4VPhysicalVolume* ZSlitsMidLeftWall_phys;
  G4VPhysicalVolume* ZSlitsLowerLeftWall_phys;
  G4VPhysicalVolume* ZSlitsUpperRightWall_phys;
  G4VPhysicalVolume* ZSlitsBottomBracket_phys;
  G4VPhysicalVolume* ZSlitsMidRightWall_phys;
  G4VPhysicalVolume* ZSlitsLowerRightWall_phys;
  G4VPhysicalVolume* ZSlitsTopBracket_phys;
  G4VPhysicalVolume* ZSlitsRightBracket_phys;
  G4VPhysicalVolume* TranslateX_phys;
  G4VPhysicalVolume* TranslateY_phys;
  G4VPhysicalVolume* Translate_phys;
  G4VPhysicalVolume* CsCollimatorBase_phys;
  G4VPhysicalVolume* CsCollimatorBody_phys;
  G4VPhysicalVolume* CsCollimatorPlug_phys;
  G4VPhysicalVolume* CloverBase_phys;
  G4VPhysicalVolume* CloverElevator_phys;
  G4VPhysicalVolume* CloverRight_phys;
  G4VPhysicalVolume* CloverLeft_phys;
  G4VPhysicalVolume* CloverAssemblyRightBase_phys;
  G4VPhysicalVolume* CloverAssemblyRightLeft_phys;
  G4VPhysicalVolume* CloverAssemblyRightRight_phys;
  G4VPhysicalVolume* CloverAssemblyLeftBase_phys;
  G4VPhysicalVolume* CloverAssemblyLeftLeft_phys;
  G4VPhysicalVolume* CloverAssemblyLeftRight_phys;
  G4VPhysicalVolume* CloverRightShield_phys;
  G4VPhysicalVolume* CloverLeftShield_phys;

};

#endif
#endif
