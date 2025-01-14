
#ifndef TrackerGammaSD_h
#define TrackerGammaSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TrackerGammaHit.hh"
#include "G4RunManager.hh"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class G4Step;
class G4HCofThisEvent;

class TrackerGammaSD : public G4VSensitiveDetector
{
  public:
      TrackerGammaSD(G4String);
     ~TrackerGammaSD();

      void SetDepth(G4int dep){depth = dep;}

      void SetPrint(){
	G4cout<<"----> Gamma track data set to print at the end of event"<<G4endl;
	print=true;}
      void UnSetPrint(){
	G4cout<<"----> Gamma track data set not to print at the end of event"<<G4endl;
	print=false;}

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
      void SetPHDA(G4double a){phdA = a;}
      void SetPHDB(G4double b){phdB = b;}
      void SetPosRes(G4double r){posRes = r;}

  private:
      TrackerGammaHitsCollection* gammaCollection;
      G4int         depth;
      G4bool        print;
      G4int         primaryGammaID;
      G4double      phdA;
      G4double      phdB;
      G4double      posRes;
};


#endif

