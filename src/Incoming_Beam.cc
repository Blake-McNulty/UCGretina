
#include "Incoming_Beam.hh"


Incoming_Beam::Incoming_Beam()
{
  A=20;
  Z=12;
  Ex=0.;
  //  KEu=100*MeV;
  KEu=0;
  KE=KEu*A;
  dtaFileName = "";
  momDist = "flat";
  posDist = "flat";
  angDist = "flat";
  Ndta = 0;
  dtaMin = 0.;
  dtaMax = 0.;
  dtaBin = 0.;
  Dpp=0.0;
  fcX=0.;
  fcDX=0.;
  fcY=0.;
  fcDY=0.;
  //  fcZ=-50.*cm;
  Z0=-50.*cm;
  maxAta=0;
  maxBta=0;
  ata0=0;
  bta0=0;
  sigma_a=0;
  sigma_b=0;
}

Incoming_Beam::~Incoming_Beam()
{;}
//---------------------------------------------------------
void Incoming_Beam::Report()
{

  G4cout<<"----> Z of the incoming beam set to  "<<Z<< G4endl;
  G4cout<<"----> A of the incoming beam set to  "<<A<< G4endl;
  G4cout<<"----> Kin. En. of the incoming beam set to "<<
  G4BestUnit(KE,"Energy")<<G4endl;
  if(dtaFileName != ""){
    G4cout<<"----> Relative KE distribution of the incoming beam read from "
	  << dtaFileName << G4endl;
    G4cout<<"----> KE per nucleon corresponding to zero relative KE set to "
	  << G4BestUnit(KEu,"Energy")<<G4endl;
  } else
    G4cout<<"----> KE per nucleon of the incoming beam set to "<<
      G4BestUnit(KEu,"Energy")<<G4endl;
  G4cout<<"----> momentum acceptance for the incoming beam set to  "<<Dpp<< G4endl;
  G4cout<<"----> momentum distribution type set to "<<momDist<< G4endl;
  G4cout<<"----> focal point X position for the incoming beam set to  "<<G4BestUnit(fcX,"Length")<< G4endl;
  G4cout<<"----> focal point DX size for the incoming beam set to  "<<G4BestUnit(fcDX,"Length")<< G4endl;
  G4cout<<"----> focal point Y position for the incoming beam set to  "<<G4BestUnit(fcY,"Length")<< G4endl;
  G4cout<<"----> focal point DY size for the incoming beam set to  "<<G4BestUnit(fcDY,"Length")<< G4endl;
  G4cout<<"----> initial Z position for the incoming beam set to  "<<G4BestUnit(Z0,"Length")<< G4endl;
  G4cout<<"----> position distribution type set to "<<posDist<< G4endl;
  G4cout<<"----> angular distribution type set to "<<angDist<< G4endl;
  if(angDist == "flat"){
    G4cout<<"----> width of the angular distribution of the incoming beam in the dispersive direction set to  "<<maxAta/mrad<<" mrad "<< G4endl;
    G4cout<<"----> width of the angular distribution of the incoming beam in the non dispersive direction set to  "<<maxBta/mrad<<" mrad" << G4endl;
  } else if(angDist == "Gaussian"){
    G4cout<<"----> sigma of the angular distribution of the incoming beam in the dispersive direction set to  "<<sigma_a/mrad<<" mrad "<< G4endl;
    G4cout<<"----> sigma of the angular distribution of the incoming beam in the non dispersive direction set to  "<<sigma_b/mrad<<" mrad" << G4endl;
  }
}
//---------------------------------------------------------
void Incoming_Beam::setA(G4int Ain)
{

  A=Ain;
  //  G4cout<<"----> A of the incoming beam set to  "<<A<< G4endl;
  
}
//---------------------------------------------------------
void Incoming_Beam::setZ(G4int Zin)
{

  Z=Zin;
  //  G4cout<<"----> Z of the incoming beam set to  "<<Z<< G4endl;
  
}
//---------------------------------------------------------
void Incoming_Beam::setDpp(G4double d)
{

  Dpp=d;
  //  G4cout<<"----> momentum acceptance for the incoming beam set to  "<<Dpp<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setfcX(G4double d)
{

  fcX=d;
  //  G4cout<<"----> focal point X position for the incoming beam set to  "<<G4BestUnit(fcX,"Length")<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setfcDX(G4double d)
{

  fcDX=d;
  //  G4cout<<"----> focal point DX size for the incoming beam set to  "<<G4BestUnit(fcDX,"Length")<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setfcDY(G4double d)
{

  fcDY=d;
  //  G4cout<<"----> focal point DY size for the incoming beam set to  "<<G4BestUnit(fcDY,"Length")<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setfcY(G4double d)
{

  fcY=d;
  //  G4cout<<"----> focal point Y position for the incoming beam set to  "<<G4BestUnit(fcY,"Length")<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setZ0(G4double d)
{

  Z0=d;
  //  G4cout<<"----> initial Z position for the incoming beam set to  "<<G4BestUnit(Z0,"Length")<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setmaxAta(G4double d)
{

  maxAta=d;
  //  G4cout<<"----> dispersive direction angular divergence for the incoming beam set to  "<<maxAta/mrad<<" mrad = "<<maxAta/deg<<" deg"<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setmaxBta(G4double d)
{

  maxBta=d;
  //  G4cout<<"----> non dispersive direction angular divergence for the incoming beam set to  "<<maxBta/mrad<<" mrad = "<<maxBta/deg<<" deg"<< G4endl;
}
//---------------------------------------------------------
void Incoming_Beam::setKE(G4double KEin)
{

  KE=KEin;
  KEu=KE/A;
  //G4cout<<"----> Kin. En. of the incoming beam set to "<<
  // G4BestUnit(KE,"Energy")<<G4endl;
  //G4cout<<"----> Kin. En. per nucleon of the incoming beam set to "<<
  // G4BestUnit(KEu,"Energy")<<G4endl;
}
//-----------------------------------------------------------------
void Incoming_Beam::setKEu(G4double KEuin)
{

  KEu=KEuin;
  KE=KEu*A;
  //G4cout<<"----> Kin. En. of the incoming beam set to "<<
  // G4BestUnit(KE,"Energy")<<G4endl;
  //G4cout<<"----> Kin. En. per nucleon of the incoming beam set to "<<
  // G4BestUnit(KEu,"Energy")<<G4endl; 
}
//-----------------------------------------------------------------
void Incoming_Beam::setDTAFile(G4String fileName)
{
  char line[1000];

  dtaFileName = fileName;
  std::ifstream dtaFile;
  dtaFile.open(dtaFileName);
  if (!dtaFile.is_open()) {
    G4cout << "Unable to open " << dtaFileName << G4endl;
    exit(EXIT_FAILURE);
  }
 
  dtaFile >> dtaMin >> dtaMax >> dtaBin;
  dtaFile.getline(line,1000);  // Advance to next line.

  G4double d;
  Ndta = 0;
  while(dtaFile >> d){
    dtaFile.getline(line,1000);  // Advance to next line.
    dta[Ndta] = d;
    Ndta++;
  }

  dtaFile.close();

}
//---------------------------------------------------------
G4ThreeVector Incoming_Beam::getDirection()
{
  G4ThreeVector direction;
  G4double x,y,z,a,b,r,phi;
  //  r1=G4UniformRand();
  //   r2=G4UniformRand();
  
  //   z=r1+cos(maxTh)*(1-r1);
  //   x=sqrt(1-z*z)*sin(2*pi*r2);
  //   y=sqrt(1-z*z)*cos(2*pi*r2);

  if(angDist == "flat"){
    phi=G4UniformRand()*8.*atan(1.);
    r=G4UniformRand()+G4UniformRand();
    if(r>=1) r=-(r-2.);
    a=r*cos(phi)*maxAta;
    b=r*sin(phi)*maxBta; 
  } else if (angDist == "Gaussian") {
    a = CLHEP::RandGauss::shoot(0, sigma_a);
    b = CLHEP::RandGauss::shoot(0, sigma_b);
  } else {
    G4cerr<<"Error: angular distribution type must be flat or Gaussian."
	  <<G4endl;
    exit(EXIT_FAILURE);
  }
  z=1./sqrt(1.+tan(a)*tan(a)+tan(b)*tan(b));
  y=z*tan(a);
  x=z*tan(b);
  direction.setX(x);
  direction.setY(y);
  direction.setZ(z);
  direction.rotateX(ata0);
  direction.rotateY(-bta0);
  return direction;
  
}
//---------------------------------------------------------
G4ThreeVector Incoming_Beam::getPosition(G4ThreeVector direction)
{
  G4ThreeVector position;
  G4double x,y;
  G4double r,phi;

  phi=G4UniformRand()*8.*atan(1.);
  r=G4UniformRand()+G4UniformRand();
  if(r>=1) r=-(r-2.);

  if(posDist == "flat"){
    x=fcX+r*cos(phi)*fcDX/2.;
    y=fcY+r*sin(phi)*fcDY/2.;
  } else if(posDist == "Gaussian") {
    x=CLHEP::RandGauss::shoot(fcX+r*cos(phi), fcDX);
    y=CLHEP::RandGauss::shoot(fcY+r*sin(phi), fcDY);
  } else {
    G4cerr << "Position distribution set to something other than flat or Gaussian." << G4endl;
    exit(EXIT_FAILURE);
  }
  
  // Extrapolate back from the target to the initial beam position.
  x += direction.x()/direction.z()*Z0;
  y += direction.y()/direction.z()*Z0;
  
  position.setX(x);
  position.setY(y);
  position.setZ(Z0);
  
  return position;
  
}

//---------------------------------------------------------
G4double Incoming_Beam::getKE(G4ParticleDefinition *ion)
{
  G4DynamicParticle dynamic;
  G4ThreeVector momentum_vector;
  G4double momentum;
  G4double rand;
  G4double ke, KinEne;
  //  momentum_vector=0;    //LR (Change to CLHEP library Hep3Vector)
  momentum_vector.setX(0.); //LR
  momentum_vector.setY(0.); //LR
  momentum_vector.setZ(1.);

  if(Ndta > 0){
    CLHEP::RandGeneral randDTA( dta, Ndta );
    ke = KE*(1 + dtaMin/100. + randDTA.fire()*(dtaMax-dtaMin)/100.);
  } else {
    ke = KE;
  }

  dynamic=G4DynamicParticle(ion,momentum_vector,ke);
  momentum=dynamic.GetTotalMomentum();

  if(momDist == "flat"){
    rand=G4UniformRand()-0.5;
    momentum*=(1+rand*Dpp);
  } else if(momDist == "Gaussian") {
     momentum = CLHEP::RandGauss::shoot(momentum, momentum*Dpp);
  } else {
    G4cerr << "Momentum distribution set to something other than flat or Gaussian." << G4endl;
    exit(EXIT_FAILURE);
  }
  
  momentum_vector.setMag(momentum);
  //  dynamic.SetMomentum(momentum); //LR (Change to CLHEP library Hep3Vector)
  dynamic.SetMomentum(momentum_vector);
  KinEne=dynamic.GetKineticEnergy();

  return KinEne;
  
}
