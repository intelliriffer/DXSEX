#!/bin/bash
#g++ -w -Wall -D__UNIX_JACK__ *.cpp -o seq -ljack  && ./seq

#g++ -w -Wall -D__LINUX_ALSA__ -O3 -fPIC -Wno-unused-variable  *.cpp -o euclidier  -lncurses -lm -ldl -lstdc++ -lasound -lpthread  && ./euclidier
g++ -w -D__LINUX_ALSA__ -O3 -fPIC -Wno-unused-variable *.cpp -o bin/dxsex -lncurses -lm -ldl -lstdc++ -lasound -lpthread
#g++ -Wall -D__UNIX_JACK__ -O3 -fPIC -Wno-unused-variable *.cpp -o bin/volca_jack -lncurses -lm -ldl -lstdc++ -lasound -lpthread -ljack
