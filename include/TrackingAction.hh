#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "PrimaryVertexInformation.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "GEB.hh"

#include "EventAction.hh"

class TrackingAction : public G4UserTrackingAction {

public:

  TrackingAction(EventAction*);
  ~TrackingAction() {};
 
  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);

private:

  EventAction* eventAction;
  PrimaryVertexInformation* primaryVertexInfo;
};
 
#endif //TRACKINGACTION_H
