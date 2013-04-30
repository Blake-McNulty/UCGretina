## Compile and install UCGretina ##

    $ source <G4INSTALL>/share/Geant4-9.6.1/geant4make/geant4make.sh
    $ make

Here, the file env.sh comes from your local installation of geant4. 

To use the liquid hydrogen target:

    $ make LHTARGET=1

produces the binary UCGretina_LH

## Examples ##

Several examples are in the examples subdirectory, including
illustrations of fitting simulations to measured source and in-beam
spectra. In the examples, the GrROOT package is used for sorting the
mode 2 output from UCGretina.

## Selected Macro File Commands ##

### Geometry ###

Optional commands for setting target parameters:

    /Target/Material <material name>

    /Target/X_length <double> <unit>

    /Target/Y_length <double> <unit>

    /Target/SetPosition_Z  <double> <unit>

    /Target/Thickness  <double> <unit>

    /Target/ScaleDensity <double>

    /Target/Sled

Mandatory command for building a target/source frame:

    /Target/Construct

Optional commands for setting beam-tube geometry:

    /BeamTube/R_min <double> <unit>

    /BeamTube/R_max <double> <unit>

    /BeamTube/Length <double> <unit>

Mandatory command for building the beam tube:

    /BeamTube/Construct

Optional commands for including Gretina-related dead material:

    /Gretina/detector/enableCapsules 

    /Gretina/detector/enableCryostats

    /Gretina/Shell <full || north || south>

Mandatory command after setting any GRETINA parameters:

    /Gretina/update

### In-beam Simulations ###

Commands related to the incoming beam:

    /BeamIn/A <A>
    /BeamIn/Z <Z>

> Mass number and atomic number

    /BeamIn/KEu <double> <unit>

> Kinetic energy per nucleon of the incoming beam

    /BeamIn/Focus/X <double> <unit>
    /BeamIn/Focus/Y <double> <unit>
    /BeamIn/Focus/Z <double> <unit>

> Offsets of the focus of the incoming beam 

    /BeamIn/Focus/DX <double> <unit>
    /BeamIn/Focus/DY <double> <unit>

> Horizontal and vertical widths of the beam spot on target

    /BeamIn/Focus/Ata0 <double> <unit>
    /BeamIn/Focus/Bta0 <double> <unit>

> Direction of the incoming beam on target (dispersive and 
> nondispersive angles, respectively)

    /BeamIn/Focus/maxAta <double> <unit>
    /BeamIn/Focus/maxBta <double> <unit>

> Angular divergences of the incoming beam in the dispersive and
> nondispersive directions, respectively.

    /BeamIn/Dpp <double>

> Momentum acceptance (dp/p) for the incoming beam

Commands related to the outgoing reaction product:

    /BeamOut/DA <int>
    /BeamOut/DZ <int>

> Changes in mass number and atomic number of the reaction. The
> incoming beam has (A,Z) and the outgoing reaction product has
> (A+DA, Z+DZ)

    /BeamOut/ProjectileExcitation <double> <unit>

> Excitation energy of the outgoing reaction product. 

    /BeamOut/seta0 <double>
    /BeamOut/seta2 <double>
    /BeamOut/seta4 <double>

> Angular distribution coefficients for the emitted gamma rays. 

> NOTE: These commands are superseded by a level scheme file if
> a /BeamOut/LevelSchemeFile command is present.

    /BeamOut/tau <double> <unit>

> Mean lifetime of the excitation

> NOTE: This command is superseded by a level scheme file if
> a /BeamOut/LevelSchemeFile command is present.

    /BeamOut/LevelSchemeFile <filename>

> The level scheme file describes the portion of the level scheme
> populated by de-excitation of the initial state, including the 
> initial state. (The initial state must be at the energy specified by
> the /BeamOut/ProjectileExcitation command.) The format of the level
> scheme file:

>       <Level energy [keV]>  <Number of gamma-decay Branches>  <Lifetime [ps]>
>       <BR 1>   <Final-state energy [keV]>  <A0>  <A2>  <A4>
>       <BR 2>   <Final-state energy [keV]>  <A0>  <A2>  <A4>
>       ...
>       <Level energy [keV]>  <Number of gamma-decay Branches>  <Lifetime [ps]>
>       <BR 1>   <Final-state energy [keV]>  <A0>  <A2>  <A4>
>       <BR 2>   <Final-state energy [keV]>  <A0>  <A2>  <A4>
>       ...

> where <BR N> are branching rations, <A0>, <A2>, <A4> are gamma-ray
> angular distribution coefficients.


> NOTE: This command supersedes values set with the
> /BeamOut/seta0, /BeamOut/seta2, /BeamOut/seta4, and /BeamOut/tau
> commands described above.

    /BeamOut/AngDistSigmaA 0.012 rad
    /BeamOut/AngDistSigmaB 0.012 rad

> Angular spreads of the outgoing reaction products in the
> dispersive and nondispersive directions, respectively.

### Source Simulations (see also ./examples/eu152) ###

Mandatory commands

    /Experiment/RunSource

    /Experiment/Source/Set <type>

> Currently implemented types: eu152, cs137, co56, co60,
> photopeaks, eu152_peaks, co56_peaks, au, white, simple

> The simple source type emits gamma rays of a single energy (set with
> the /Experiment/Source/setEnergy command) 

> The white source type emits gamma rays in a uniform energy
> distribution between 100 keV and 10 MeV. These limits can be set
> with the /Experiment/Source/setWhiteLowE and
> /Experiment/Source/setWhiteHighE commands.

> eu152_peaks, co56_peaks, and photopeaks sources produce selected
> gamma-rays from 152Eu, 56Co, and both, respectively. The gamma rays
> are emitted in equal quantities to facilitiate determining photopeak
> efficiencies by fitting the photopeaks directly.

Optional commands

    /Experiment/Source/setEnergy <double> <unit>

> Set the energy of the "simple" source type

    /Experiment/Source/setWhiteLowE  <double> <unit>
    /Experiment/Source/setWhiteHighE <double> <unit>

> Set the limits of the energy distribution of the "white" source type

    /Target/sourceFrame <frame type>

> Optionally include the source frame (/Target/Construct command required).

> Currently implemented frames: eu152_Z2707, cs137_E2879, and co56_2012

## Mode 2 Output ##

Mode 2 output from in-beam simulations contains S800 tracking events
(GEB type 9), decomposed gamma-ray events (GEB type 1), and emitted
gamma-ray (GEB type 11). (Source simulations do not produce S800
tracking events.) S800 tracking events are only written for events in
which gamma rays are detected. Emitted gamma-ray events are written
for every event. They include the energies, emission positions, and
emission directions of all gamma rays emitted in an event.

Energies are expressed in keV, and positions are expressed in mm.

### Commands related to mode 2 output ###

    /Mode2/Filename <filename>

> This optional command activates Mode 2 output.

    /Mode2/crmatFile <filename>

> The file "crmat.LINUX" is provided. It specifies the rotation
> matrices and translation vectors from each crystal frame into the
> world coordinate system. UCGretina inverts this transformation to
> produce data in the crystal frames, as expected in Mode 2 data.

    /Mode2/GretinaCoords

> When this command is present, the world coordinates are rotated Pi/2
> about z to match the standard GRETINA coordinate system (x = down, z
> = beam). This is the coordinate system expected in Mode 2 data. This
> only affects the decomposed gamma-ray events. 

> Interaction points are expressed in the Geant4 coordinate system 
> (y = up, z = beam) by default. 

    /Mode2/PositionRes <float> <unit>

> The PositionRes parameter determines the closest spacing of
> gamma-ray interaction points within each event that GRETINA can
> resolve. Simulated interaction points are consolidated
> accordingly. Specify a zero position resolution to turn off
> consolidation.

    /Mode2/S800KE <float> <unit>

> Specifies the kinetic energy of the reaction product centered in the
> acceptance of the S800. This is needed for calculating DTA
> (dT/T) values of the S800 tracking events in the Mode2 output. 

    /Mode2/Print

> This command triggers printing of information on Mode 2 data to
> stdout. 

### ASCII Output ###

The optional command

    /Output/Filename <filename>

activates ASCII output.

The output file contains gamma-ray information for each event that
deposited energy in GRETINA. For each event there is a header line
beginning with '$':

    $ nHits Egamma Event#

where nHits is the number of interaction ponts, Egamma is the total
energy of the event, and Event# is the event number. The header line
is followed by nHits lines describing the hits with the format:

    detNum Edep x y z

where Edep is the energy (in keV) deposited in crystal detNum by the
hit. The hit positions (x, y, z) are in mm.

## Visualize the array ##

Run the macro file "vis/vis.mac" an interactive session:

    $ UCGretina

    Idle> /control/execute vis/vis.mac
    Idle> exit

This generates a VRML 2 file named g4_XX.wrl which can be viewed
with a VRML viewer (like mayavi2).

Within mayavi2, the python scripts ./vis/mlab.animate.py and
./vis/mlab.movie.py can be run (File -> Run Python Script). The
former animates the scene, and the latter saves the animation frames
as a series of .png files which can be stitched together into an
animated png or gif.
