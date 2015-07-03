#ifdef SCANNING
#include "ScanningTable.hh"

ScanningTable::ScanningTable(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  CADModelPath = "../";

  materials=mat;
  expHall_log=experimentalHall_log;

  Pos0 = new G4ThreeVector(0., 0., 44.45*mm); // center flange @ (x,z) = (0,0)

  includeCartFrame  = false;
  includeCloverCart = false;
  includeSlitMount  = false;
  includeShield     = false;

  xShift = 0.0*mm;
  yShift = 0.0*mm;
  zShift = 0.0*mm;
  
  material8020 = materials->FindMaterial("Al");
  materialCartBase = materials->FindMaterial("ssteel");
  materialCartTop = materials->FindMaterial("ssteel");
  materialCartBack = materials->FindMaterial("ssteel");
  materialSlitBrackets = materials->FindMaterial("Al");
  materialSlits = materials->FindMaterial("Hevimet");
  materialSlitAssembly = materials->FindMaterial("Al");
  materialTranslation = materials->FindMaterial("G10");
  materialTranslationAssembly = materials->FindMaterial("ssteel");
  materialCsCollimator = materials->FindMaterial("Hevimet");
  materialClover = materials->FindMaterial("HpGe");
  materialCloverShield = materials->FindMaterial("Al");
}

ScanningTable::~ScanningTable()
{;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* ScanningTable::Construct()
{

  //--- First the physical cart: 8020 frame, base, top and back panel ---------

  G4cout << "Loading STL files from directory:\n" << CADModelPath 
	 << "\nand building Tessellated solids ... " << G4endl;

  G4String CADFileName;

  if (includeCartFrame) {

    const int CartParts = 37;
    G4String CartPart[CartParts];
    G4Material* CartMaterial[CartParts];
    CartPart[0] = "Cart8020BackBrace1";
    CartMaterial[0] = material8020;
    CartPart[1] = "Cart8020BackBrace2";
    CartMaterial[1] = material8020;
    CartPart[2] = "Cart8020BackBrace3";
    CartMaterial[2] = material8020;
    CartPart[3] = "Cart8020BackBrace4";
    CartMaterial[3] = material8020;
    CartPart[4] = "Cart8020BackBrace5";
    CartMaterial[4] = material8020;
    CartPart[5] = "Cart8020BackBrace6";
    CartMaterial[5] = material8020;
    CartPart[6] = "Cart8020BackBrace7";
    CartMaterial[6] = material8020;
    CartPart[7] = "Cart8020BackBrace8";
    CartMaterial[7] = material8020;
    CartPart[8] = "Cart8020BottomBrace1";
    CartMaterial[8] = material8020;
    CartPart[9] = "Cart8020BottomBrace2";
    CartMaterial[9] = material8020;
    CartPart[10] = "Cart8020BottomBrace3";
    CartMaterial[10] = material8020;
    CartPart[11] = "Cart8020BottomBrace4";
    CartMaterial[11] = material8020;
    CartPart[12] = "Cart8020BottomBrace5";
    CartMaterial[12] = material8020;
    CartPart[13] = "Cart8020BottomBrace6";
    CartMaterial[13] = material8020;
    CartPart[14] = "Cart8020ExtBackLeft2";
    CartMaterial[14] = material8020;
    CartPart[15] = "Cart8020ExtBackMid2";
    CartMaterial[15] = material8020;
    CartPart[16] = "Cart8020ExtBackRight2";
    CartMaterial[16] = material8020;
    CartPart[17] = "Cart8020ExtBackTop2";
    CartMaterial[17] = material8020;
    CartPart[18] = "Cart8020ExtTopLeft2";
    CartMaterial[18] = material8020;
    CartPart[19] = "Cart8020ExtBottomLeft2";
    CartMaterial[19] = material8020;
    CartPart[20] = "Cart8020ExtBottomMid2";
    CartMaterial[20] = material8020;
    CartPart[21] = "Cart8020ExtBottomRight2";
    CartMaterial[21] = material8020;
    CartPart[22] = "Cart8020ExtFrontBottom2";
    CartMaterial[22] = material8020;
    CartPart[23] = "Cart8020ExtFrontLeft2";
    CartMaterial[23] = material8020;
    CartPart[24] = "Cart8020ExtFrontRight2";
    CartMaterial[24] = material8020;
    CartPart[25] = "Cart8020ExtTopRight2";
    CartMaterial[25] = material8020;
    CartPart[26] = "Cart8020FrontBrace1";
    CartMaterial[26] = material8020;
    CartPart[27] = "Cart8020FrontBrace2";
    CartMaterial[27] = material8020;
    CartPart[28] = "Cart8020LeftBrace1";
    CartMaterial[28] = material8020;
    CartPart[29] = "Cart8020LeftBrace2";
    CartMaterial[29] = material8020;
    CartPart[30] = "Cart8020LeftBrace3";
    CartMaterial[30] = material8020;
    CartPart[31] = "Cart8020LeftBrace4";
    CartMaterial[31] = material8020;
    CartPart[32] = "Cart8020RightBrace1";
    CartMaterial[32] = material8020;
    CartPart[33] = "Cart8020RightBrace2";
    CartMaterial[33] = material8020;
    CartPart[34] = "Cart8020RightBrace3";
    CartMaterial[34] = material8020;
    CartPart[35] = "Cart8020RightBrace4";
    CartMaterial[35] = material8020;
    CartPart[36] = "Cart8020ExtBottomBack2";
    CartMaterial[36] = material8020;

    G4Colour lpurple (0.5, 0.3, 1.0, 0.3);
    G4VisAttributes* VisCart = new G4VisAttributes(lpurple);
    VisCart->SetVisibility(true);
    VisCart->SetForceWireframe(true);

    for(int i=0;i<CartParts;i++){
      if(CartPart[i] != ""){
	CADFileName = CADModelPath + "/";
	CADFileName += CartPart[i];
	CADFileName += ".stl";
	CADMesh *mesh = new CADMesh((char*)CADFileName.data(),
				    (char*)"STL");
	mesh->SetScale(mm);
	mesh->SetOffset(G4ThreeVector(0., 0., 0.));
     
	G4VSolid *Cart = mesh->TessellatedMesh();
	Cart_log = new G4LogicalVolume(Cart, CartMaterial[i], 
				       CartPart[i], 0, 0, 0);
	Cart_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0),
				      Cart_log,
				      CartPart[i],
				      expHall_log,false,0);
	Cart_log->SetVisAttributes(VisCart);
      }
    }

    const int CartTopParts = 9;
    G4String CartTopPart[CartTopParts];
    G4Material* CartTopMaterial[CartTopParts];
    CartTopPart[0] = "CartTopBar";
    CartTopMaterial[0] = materialCartTop;
    CartTopPart[1] = "CartTopFlange";
    CartTopMaterial[1] = materialCartTop;
    CartTopPart[2] = "CartTopPlate";
    CartTopMaterial[2] = materialCartTop;
    CartTopPart[3] = "CartTopUBaseBottomLeft";
    CartTopMaterial[3] = materialCartTop;
    CartTopPart[4] = "CartTopUBaseBottomMid";
    CartTopMaterial[4] = materialCartTop;
    CartTopPart[5] = "CartTopUBaseBottomRight";
    CartTopMaterial[5] = materialCartTop;
    CartTopPart[6] = "CartTopUBaseUpperLeft";
    CartTopMaterial[6] = materialCartTop;
    CartTopPart[7] = "CartTopUBaseUpperMid";
    CartTopMaterial[7] = materialCartTop;
    CartTopPart[8] = "CartTopUBaseUpperRight";
    CartTopMaterial[8] = materialCartTop;

    for(int i=0; i < CartTopParts; i++){
      if(CartTopPart[i] != ""){
	CADFileName = CADModelPath + "/";
	CADFileName += CartTopPart[i];
	CADFileName += ".stl";
	CADMesh *mesh = new CADMesh((char*)CADFileName.data(),
				    (char*)"STL");
	mesh->SetScale(mm);
	mesh->SetOffset(G4ThreeVector(0., 0., 0.));
     
	G4VSolid *CartTop = mesh->TessellatedMesh();
	
	CartTop_log = new G4LogicalVolume(CartTop,
					  CartTopMaterial[i], 
					  CartTopPart[i], 0, 0, 0);
	CartTop_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0),
					 CartTop_log,
					 CartTopPart[i],
					 expHall_log,false,0);
	CartTop_log->SetVisAttributes(VisCart);
      }
    }
  }
  
  //--- Now the slit assembly -------------------------------------------------

  const int ZSlitParts = 10;
  G4String ZSlitPart[ZSlitParts];
  G4Material* ZSlitMaterial[ZSlitParts];
  ZSlitPart[0] = "ZSlitsBottomBracket";
  ZSlitMaterial[0] = materialSlitBrackets;
  ZSlitPart[1] = "ZSlitsLeftBracket";
  ZSlitMaterial[1] = materialSlitBrackets;
  ZSlitPart[2] = "ZSlitsRightBracket";
  ZSlitMaterial[2] = materialSlitBrackets;
  ZSlitPart[3] = "ZSlitsTopBracket";
  ZSlitMaterial[3] = materialSlitBrackets;
  ZSlitPart[4] = "ZSlitsLowerLeftWall";
  ZSlitMaterial[4] = materialSlits;
  ZSlitPart[5] = "ZSlitsLowerRightWall";
  ZSlitMaterial[5] = materialSlits;
  ZSlitPart[6] = "ZSlitsMidLeftWall";
  ZSlitMaterial[6] = materialSlits;
  ZSlitPart[7] = "ZSlitsMidRightWall";
  ZSlitMaterial[7] = materialSlits;
  ZSlitPart[8] = "ZSlitsUpperLeftWall";
  ZSlitMaterial[8] = materialSlits;
  ZSlitPart[9] = "ZSlitsUpperRightWall";
  ZSlitMaterial[9] = materialSlits;

  G4Colour lblue(0.0, 1.0, 1.0, 1.0);
  G4Colour lblue2(0.0, 1.0, 1.0, 0.3);
  G4VisAttributes* VisSlit = new G4VisAttributes(lblue);
  G4VisAttributes* VisSlit2 = new G4VisAttributes(lblue2);
  VisSlit->SetVisibility(true);
  VisSlit->SetForceSolid(false);
  VisSlit2->SetVisibility(true);
  VisSlit2->SetForceWireframe(true);
  
  for(int i=0;i<ZSlitParts;i++){
    if(ZSlitPart[i] != ""){
      CADFileName = CADModelPath + "/";
      CADFileName += ZSlitPart[i];
      CADFileName += ".stl";
      CADMesh *mesh = new CADMesh((char*)CADFileName.data(),
				  (char*)"STL");
      mesh->SetScale(mm);
      mesh->SetOffset(G4ThreeVector(0., zShift, 0.));
     
      G4VSolid *Slits = mesh->TessellatedMesh();
      ZSlit_log = new G4LogicalVolume(Slits, ZSlitMaterial[i], 
				      SlitPart[i], 0, 0, 0);
      ZSlit_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0),
				     ZSlit_log,
				     ZSlitPart[i],
				     expHall_log,false,0);
      ZSlit_log->SetVisAttributes(VisSlit);
    }
  }

//-------------------------------------------------------------

  if(includeSlitMount){

    const int SlitZAssemblyParts = 25;
    G4String SlitZAssemblyPart[SlitZAssemblyParts];
    G4Material* SlitZAssemblyMaterial[SlitZAssemblyParts];
    SlitZAssemblyPart[0] = "SlitZAssemblyBelt";
    SlitZAssemblyMaterial[0] = materialSlitAssembly;
    SlitZAssemblyPart[1] = "SlitZAssemblyCenterCylinder";
    SlitZAssemblyMaterial[1] = materialSlitAssembly;
    SlitZAssemblyPart[2] = "SlitZAssemblyCenterCylinderBase";
    SlitZAssemblyMaterial[2] = materialSlitAssembly;
    SlitZAssemblyPart[3] = "SlitZAssemblyCenterCylinderDisk";
    SlitZAssemblyMaterial[3] = materialSlitAssembly;
    SlitZAssemblyPart[4] = "SlitZAssemblyCenterCylinderPlug";
    SlitZAssemblyMaterial[4] = materialSlitAssembly;
    //    SlitZAssemblyPart[5] = "SlitZAssemblyCirclePlate"; // until the overlap with the crystals is fixed
    SlitZAssemblyPart[5] = "";
    SlitZAssemblyMaterial[5] = materialSlitAssembly;
    SlitZAssemblyPart[6] = "SlitZAssemblyLeftCrescentWithHoles";
    SlitZAssemblyMaterial[6] = materialSlitAssembly;
    SlitZAssemblyPart[7] = "SlitZAssemblyCrescentRight";
    SlitZAssemblyMaterial[7] = materialSlitAssembly;
    SlitZAssemblyPart[8] = "SlitZAssemblyLeftCrescentClip";
    SlitZAssemblyMaterial[8] = materialSlitAssembly;
    SlitZAssemblyPart[9] = "SlitZAssemblyLeftBrace";
    SlitZAssemblyMaterial[9] = materialSlitAssembly;
    SlitZAssemblyPart[10] = "SlitZAssemblyLeftClamp";
    SlitZAssemblyMaterial[10] = materialSlitAssembly;
    SlitZAssemblyPart[11] = "SlitZAssemblyLeftPlate2";
    SlitZAssemblyMaterial[11] = materialSlitAssembly;
    SlitZAssemblyPart[12] = "SlitZAssemblyLeftPlate";
    SlitZAssemblyMaterial[12] = materialSlitAssembly;
    SlitZAssemblyPart[13] = "SlitZAssemblyLeftScrew";
    SlitZAssemblyMaterial[13] = materialSlitAssembly;
    SlitZAssemblyPart[14] = "SlitZAssemblyCrescentLeft";
    SlitZAssemblyMaterial[14] = materialSlitAssembly;
    SlitZAssemblyPart[15] = "SlitZAssemblyPlateWithHoles";
    SlitZAssemblyMaterial[15] = materialSlitAssembly;
    SlitZAssemblyPart[16] = "SlitZAssemblyPlug";
    SlitZAssemblyMaterial[16] = materialSlitAssembly;
    SlitZAssemblyPart[17] = "SlitZAssemblyRightBrace";
    SlitZAssemblyMaterial[17] = materialSlitAssembly;
    SlitZAssemblyPart[18] = "SlitZAssemblyRightClamp";
    SlitZAssemblyMaterial[18] = materialSlitAssembly;
    SlitZAssemblyPart[19] = "SlitZAssemblyRightCrescentClip";
    SlitZAssemblyMaterial[19] = materialSlitAssembly;
    SlitZAssemblyPart[20] = "SlitZAssemblyRightCrescentWithHoles";
    SlitZAssemblyMaterial[20] = materialSlitAssembly;
    SlitZAssemblyPart[21] = "SlitZAssemblyRightPlate";
    SlitZAssemblyMaterial[21] = materialSlitAssembly;
    SlitZAssemblyPart[22] = "SlitZAssemblyScrew";
    SlitZAssemblyMaterial[22] = materialSlitAssembly;
    SlitZAssemblyPart[23] = "SlitZAssemblyTPlate";
    SlitZAssemblyMaterial[23] = materialSlitAssembly;
    SlitZAssemblyPart[24] = "SlitZAssemblyUPlate";
    SlitZAssemblyMaterial[24] = materialSlitAssembly;
    
    for(int i=0; i < SlitZAssemblyParts; i++){
      if(SlitZAssemblyPart[i] != ""){
	CADFileName = CADModelPath + "/";
	CADFileName += SlitZAssemblyPart[i];
	CADFileName += ".stl";
	CADMesh *mesh = new CADMesh((char*)CADFileName.data(),
				    (char*)"STL");
	mesh->SetScale(mm);
	mesh->SetOffset(G4ThreeVector(0., zShift, 0.));
     
	G4VSolid *SlitAssembly = mesh->TessellatedMesh();
	SlitZAssembly_log = new G4LogicalVolume(SlitAssembly, 
						SlitZAssemblyMaterial[i], 
						SlitZAssemblyPart[i], 0, 0, 0);
	SlitZAssembly_phys = new G4PVPlacement(G4Transform3D(NoRot, 
							     *Pos0),
					       SlitZAssembly_log,
					       SlitZAssemblyPart[i],
					       expHall_log,false,0);
	SlitZAssembly_log->SetVisAttributes(VisSlit2);
      }
    }
  }

  //--- And the Cs collimator assemblies --------------------------------------

  // G4Colour lgrey(0.7, 0.7, 0.7, 0.3);
  // G4VisAttributes* VisTranslation = new G4VisAttributes(lgrey);
  // VisTranslation->SetVisibility(true);
  // VisTranslation->SetForceWireframe(true);

  // CADFileName = CADModelPath + "/SourceTranslation1.stl";
  // CADMesh *meshTranslateX = new CADMesh((char*)CADFileName.data(), 
  // 					(char*)"STL");
  // meshTranslateX->SetScale(mm);
  // meshTranslateX->SetOffset(G4ThreeVector(xShift, 0., 0.));

  // CADFileName = CADModelPath + "/SourceTranslation2.stl";
  // CADMesh *meshTranslateY = new CADMesh((char*)CADFileName.data(), 
  // 					(char*)"STL");
  // meshTranslateY->SetScale(mm);
  // meshTranslateY->SetOffset(G4ThreeVector(0., 0., yShift));

  // CADFileName = CADModelPath + "/SourceTranslationAssembly.stl";
  // CADMesh *meshTranslate = new CADMesh((char*)CADFileName.data(), 
  // 				       (char*)"STL");
  // meshTranslate->SetScale(mm);
  // meshTranslate->SetOffset(G4ThreeVector(xShift, 0., yShift));

  // G4VSolid *TranslateX = meshTranslateX->TessellatedMesh();
  // TranslateX_log = new G4LogicalVolume(TranslateX, materialTranslation,
  // 				       "TranslateX_log", 0, 0, 0);
  // TranslateX_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0), 
  // 				      TranslateX_log,
  // 				      "TranslationX", 
  // 				      expHall_log, false, 0);
  // TranslateX_log->SetVisAttributes(VisTranslation);

  // G4VSolid *TranslateY = meshTranslateY->TessellatedMesh();
  // TranslateY_log = new G4LogicalVolume(TranslateY, materialTranslation,
  // 				       "TranslateY_log", 0, 0, 0);
  // TranslateY_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0), 
  // 				      TranslateY_log,
  // 				      "TranslationY", 
  // 				      expHall_log, false, 0);
  // TranslateY_log->SetVisAttributes(VisTranslation);
  
  // G4VSolid *Translate = meshTranslate->TessellatedMesh();
  // Translate_log = new G4LogicalVolume(Translate, materialTranslationAssembly,
  // 				      "Translate_log", 0, 0, 0);
  // Translate_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0), 
  // 				     Translate_log,
  // 				     "TranslationAssembly", 
  // 				     expHall_log, false, 0);
  // Translate_log->SetVisAttributes(VisTranslation);

  const int CollimatorParts = 3;
  G4String CollimatorPart[CollimatorParts];
  G4Material* CollimatorMaterial[CollimatorParts];
  CollimatorPart[0] = "CsCollimatorBase";
  CollimatorMaterial[0] = materialCsCollimator;
  CollimatorPart[1] = "CsCollimatorBody";
  CollimatorMaterial[1] = materialCsCollimator;
  CollimatorPart[2] = "CsCollimatorPlug";
  CollimatorMaterial[2] = materialCsCollimator;

  for(int i=0; i < CollimatorParts; i++){
    if(CollimatorPart[i] != ""){
      CADFileName = CADModelPath + "/";
      CADFileName += CollimatorPart[i];
      CADFileName += ".stl";
      CADMesh *mesh = new CADMesh((char*)CADFileName.data(),
				  (char*)"STL");
      mesh->SetScale(mm);
      mesh->SetOffset(G4ThreeVector(xShift, 0., yShift));
     
      G4VSolid *Collimator = mesh->TessellatedMesh();

      Collimator_log = new G4LogicalVolume(Collimator,
					   CollimatorMaterial[i], 
					   CollimatorPart[i], 0, 0, 0);
      Collimator_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0),
					  Collimator_log,
					  CollimatorPart[i],
					  expHall_log,false,0);
      Collimator_log->SetVisAttributes(VisSlit2);
    }
  }

  //--- Now the clover cart: base and elevator --------------------------------

  if (includeCloverCart) {
    const int CloverAssemblyParts = 6;
    G4String CloverAssemblyPart[CloverAssemblyParts];
    G4Material* CloverAssemblyMaterial[CloverAssemblyParts];
    CloverAssemblyPart[0] = "CloverAssemblyLeftBase";
    CloverAssemblyMaterial[0] = materialCartBase;
    CloverAssemblyPart[1] = "CloverAssemblyLeftLeft";
    CloverAssemblyMaterial[1] = materialCartBase;
    CloverAssemblyPart[2] = "CloverAssemblyLeftRight";
    CloverAssemblyMaterial[2] = materialCartBase;
    CloverAssemblyPart[3] = "CloverAssemblyRightBase";
    CloverAssemblyMaterial[3] = materialCartBase;
    CloverAssemblyPart[4] = "CloverAssemblyRightLeft";
    CloverAssemblyMaterial[4] = materialCartBase;
    CloverAssemblyPart[5] = "CloverAssemblyRightRight";
    CloverAssemblyMaterial[5] = materialCartBase;

    G4Colour lpurpleBlue (0.3, 0.2, 1.0, 0.3);
    G4VisAttributes* VisCloverCart = new G4VisAttributes(lpurpleBlue);
    VisCloverCart->SetVisibility(true);
    VisCloverCart->SetForceWireframe(true);

    for(int i=0; i < CloverAssemblyParts; i++){
      if(CloverAssemblyPart[i] != ""){
	CADFileName = CADModelPath + "/";
	CADFileName += CloverAssemblyPart[i];
	CADFileName += ".stl";
	CADMesh *mesh = new CADMesh((char*)CADFileName.data(),
				    (char*)"STL");
	mesh->SetScale(mm);
	mesh->SetOffset(G4ThreeVector(xShift, 0., yShift));
     
	G4VSolid *CloverAssembly = mesh->TessellatedMesh();

	CloverAssembly_log = new G4LogicalVolume(CloverAssembly,
						 CloverAssemblyMaterial[i], 
						 CloverAssemblyPart[i], 0, 0, 0);
	CloverAssembly_phys = new G4PVPlacement(G4Transform3D(NoRot, 
							      *Pos0),
						CloverAssembly_log,
						CloverAssemblyPart[i],
						expHall_log,false,0);
	CloverAssembly_log->SetVisAttributes(VisSlit2);
      }
    }
  }
    
  //--- Now the shields -- just for show right now ------------------------

  if(includeShield){

    G4Colour lgreen (0.0, 1.0, 0.5, 0.3);
    G4VisAttributes* VisShield = new G4VisAttributes(lgreen);
    VisShield->SetVisibility(true);
    VisShield->SetForceWireframe(true);

    CADFileName = CADModelPath + "/Shield-Right.stl";
    CADMesh *meshCloverRightShield = new CADMesh((char*)CADFileName.data(), 
						 (char*)"STL");
    meshCloverRightShield->SetScale(mm);
    meshCloverRightShield->SetOffset(G4ThreeVector(0., zShift, 0.));

    G4VSolid *CloverRightShield = meshCloverRightShield->TessellatedMesh();
    CloverRightShield_log = new G4LogicalVolume(CloverRightShield, 
						materialCloverShield, 
						"CloverRightShield_log", 
						0, 0, 0);
    CloverRightShield_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0),
    					       CloverRightShield_log, 
    					       "RightCloverShield",
    					       expHall_log, false, 0);
    CloverRightShield_log->SetVisAttributes(VisShield);

    // G4cout << "CloverRightShield: center @" 
    // 	   << CloverRightShield->GetExtent().GetExtentCenter() 
    // 	   << " xmin = " 
    // 	   << CloverRightShield->GetExtent().GetXmin() 
    // 	   << " xmax = " 
    // 	   << CloverRightShield->GetExtent().GetXmax() 
    // 	   << " ymin = " 
    // 	   << CloverRightShield->GetExtent().GetYmin() 
    // 	   << " ymax = " 
    // 	   << CloverRightShield->GetExtent().GetYmax() 
    // 	   << " zmin = " 
    // 	   << CloverRightShield->GetExtent().GetZmin() 
    // 	   << " zmax = " 
    // 	   << CloverRightShield->GetExtent().GetZmax() 
    // 	   << G4endl;

    CADFileName = CADModelPath + "/Shield-Left.stl";
    CADMesh *meshCloverLeftShield = new CADMesh((char*)CADFileName.data(), 
						(char*)"STL");
    meshCloverLeftShield->SetScale(mm);
    meshCloverLeftShield->SetOffset(G4ThreeVector(0., zShift, 0.));

    G4VSolid *CloverLeftShield = meshCloverLeftShield->TessellatedMesh();
    CloverLeftShield_log = new G4LogicalVolume(CloverLeftShield, 
					       materialCloverShield, 
					       "CloverLeftShield_log", 
					       0, 0, 0);
    CloverLeftShield_phys = new G4PVPlacement(G4Transform3D(NoRot, *Pos0),
    					      CloverLeftShield_log, 
    					      "LeftCloverShield",
    					      expHall_log, false, 0);
    CloverLeftShield_log->SetVisAttributes(VisShield);

  }

  G4cout << "Done." << G4endl;
  
  return Cart8020_phys;
}
//-----------------------------------------------------------------------------
#endif
