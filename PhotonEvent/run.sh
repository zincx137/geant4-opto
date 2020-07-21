#!/bin/bash
sed -i 's/G4double absoThickness = [0-9]*/G4double absoThickness = 5/g' src/B4DetectorConstruction.cc 
cd bd && cmake .. && make clean && make && ./exampleB4a -m run.mac > ../output/Gamma5mm
cd ..
sed -i 's/G4double absoThickness = [0-9]*/G4double absoThickness = 10/g' src/B4DetectorConstruction.cc 
cd bd && cmake .. && make clean && make && ./exampleB4a -m run.mac > ../output/Gamma10mm
cd ..
sed -i 's/G4double absoThickness = [0-9]*/G4double absoThickness = 15/g' src/B4DetectorConstruction.cc 
cd bd && cmake .. && make clean && make && ./exampleB4a -m run.mac > ../output/Gamma15mm
cd ..
sed -i 's/G4double absoThickness = [0-9]*/G4double absoThickness = 20/g' src/B4DetectorConstruction.cc 
cd bd && cmake .. && make clean && make && ./exampleB4a -m run.mac > ../output/Gamma20mm
cd ..
sed -i 's/G4double absoThickness = [0-9]*/G4double absoThickness = 25/g' src/B4DetectorConstruction.cc 
cd bd && cmake .. && make clean && make && ./exampleB4a -m run.mac > ../output/Gamma25mm

