# tm-h4-geant4
```
#originally used for different stuff

#adapting to explore the idea of seeing pi0->yy at h4 with CMS ECAL SM36

#ssh [...]@lxplus.cern.ch

#git clone [...]
source /cvmfs/geant4.cern.ch/geant4/11.2/x86_64-el9-gcc11-optdeb/CMake-setup.sh
source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.30.00/almalinux9.2x86_64-gcc113-opt/bin/thisroot.sh
mv tm-h4-geant4 pi0yy-cms-ecal-h4

cd pi0yy-cms-ecal-h4
#[look around]
cd ..
mkdir pi0yy-cms-ecal-h4_build
cd pi0yy-cms-ecal-h4_build
cmake -S ../pi0yy-cms-ecal-h4 -B .
make

./AnaEx01 AnaEx01.in out.root $RANDOM
```
