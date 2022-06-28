#!/bin/bash
g++ -w -Wall -D__MACOSX_CORE__ *.cpp -o bin/mac/dxsex -framework CoreMIDI -framework coreAudio -framework CoreFoundation -std=c++11
