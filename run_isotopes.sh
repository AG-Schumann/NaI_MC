#!/bin/bash

source /home/jens/G4/geant4-install/bin/geant4.sh

cd ~/Rd-Bkg/Simulation/NaI/

#./NaI_MC -m Cs137.mac -o ../results/Cs137.root -n 100000000

#./NaI_MC -m Co60.mac -o ../results/Co60.root -n 100000000

#./NaI_MC -m Na22.mac -o Na22.root -n 100000000

./NaI_MC -m K40.mac -o ../results/K40_Lead.root -n 100000000

./NaI_MC -m Bi214.mac -o ../results/Bi214_Lead.root -n 100000000

./NaI_MC -m Tl208.mac -o ../results/Tl208_Lead.root -n 100000000

./NaI_MC -m Ac228.mac -o ../results/Ac228_Lead.root -n 100000000

./NaI_MC -m Th234.mac -o ../results/Th234_Lead.root -n 100000000

#./NaI_MC -m Th232.mac -o ../results/Th232_Crystal.root -n 10000000

#./NaI_MC -m Th228.mac -o ../results/Th228_Crystal.root -n 10000000

#./NaI_MC -m U238.mac -o ../results/U238_Crystal.root -n 10000000

#./NaI_MC -m Ra226.mac -o ../results/Ra226_Crystal.root -n 10000000

#./NaI_MC -m U235.mac -o ../results/U235_Crystal.root -n 10000000
