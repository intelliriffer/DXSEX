/*******************************************************************
DX7 CC to Sysex Translator for Akai Force/Raspberry PI
Author: Amit Talwar https://www.amitszone.com
Github: https://github.com/intelliriffer
***************************************************************** */

/********* DX SYSEX Message Format  *********************
SYSEX MESSAGE Parameter Change
-------------------------------
       bits    hex  description

     11110000  F0   Status byte - start sysex
     0iiiiiii  43   ID # (i=67; Yamaha)
     0sssnnnn  10   Sub-status (s=1) & channel number (n=0; ch 1)
     0gggggpp  **   parameter group # (g=0; voice, g=2; function)
     0ppppppp  **   parameter # (these are listed in next section)
                     Note that voice parameter #'s can go over 128 so
                     the pp bits in the group byte are either 00 for
                     par# 0-127 or 01 for par# 128-155. In the latter case
                     you add 128 to the 0ppppppp byte to compute par#.
     0ddddddd  **   data byte
     11110111  F7   Status - end sysex

*** Data Structure: Single Voice Dump & Parameter #'s (single voice format, g=0) ****
-------------------------------------------------------------------------
Parameter
 Number    Parameter                  Value Range
---------  ---------                  -----------
0        OP6 EG rate A              0-99
1         "  "  rate D               "
2         "  "  rate S               "
3         "  "  rate R               "
4         "  " level A               "
5         "  " level D               "
6         "  " level S              "
7         "  " level R               "
8        OP6 KBD LEV SCL BRK PT      "        C3= $27
9         "   "   "   "  LFT DEPTH   "
10         "   "   "   "  RHT DEPTH   "
11         "   "   "   "  LFT CURVE  0-3       0=-LIN, -EXP, +EXP, +LIN
12         "   "   "   "  RHT CURVE   "            "    "    "    "
13        OP6 KBD RATE SCALING       0-7
14        OP6 AMP MOD SENSITIVITY    0-3
15        OP6 KEY VEL SENSITIVITY    0-7
16        OP6 OPERATOR OUTPUT LEVEL  0-99
17        OP6 OSC MODE (fixed/ratio) 0-1        0=ratio
18        OP6 OSC FREQ COARSE        0-31
19        OP6 OSC FREQ FINE          0-99
20        OP6 OSC DETUNE             0-14

21        OP5 EG rate A              0-99
22         "  "  rate D               "
23         "  "  rate S               "
24         "  "  rate R               "
25         "  " level A               "
26         "  " level D               "
27         "  " level S              "
28         "  " level R               "
29        OP5 KBD LEV SCL BRK PT      "        C3= $27
30         "   "   "   "  LFT DEPTH   "
31         "   "   "   "  RHT DEPTH   "
32         "   "   "   "  LFT CURVE  0-3       0=-LIN, -EXP, +EXP, +LIN
33         "   "   "   "  RHT CURVE   "            "    "    "    "
34        OP5 KBD RATE SCALING       0-7
35        OP5 AMP MOD SENSITIVITY    0-3
36        OP5 KEY VEL SENSITIVITY    0-7
37        OP5 OPERATOR OUTPUT LEVEL  0-99
38        OP5 OSC MODE (fixed/ratio) 0-1        0=ratio
39        OP5 OSC FREQ COARSE        0-31
40        OP5 OSC FREQ FINE          0-99
41        OP5 OSC DETUNE             0-14

42        OP4 EG rate A              0-99
43         "  "  rate D               "
44         "  "  rate S               "
45         "  "  rate R               "
46         "  " level A               "
47         "  " level D               "
48         "  " level S              "
49         "  " level R               "
50        OP4 KBD LEV SCL BRK PT      "        C3= $27
51         "   "   "   "  LFT DEPTH   "
52         "   "   "   "  RHT DEPTH   "
53         "   "   "   "  LFT CURVE  0-3       0=-LIN, -EXP, +EXP, +LIN
54         "   "   "   "  RHT CURVE   "            "    "    "    "
55        OP4 KBD RATE SCALING       0-7
56        OP4 AMP MOD SENSITIVITY    0-3
57        OP4 KEY VEL SENSITIVITY    0-7
58        OP4 OPERATOR OUTPUT LEVEL  0-99
59        OP4 OSC MODE (fixed/ratio) 0-1        0=ratio
60        OP4 OSC FREQ COARSE        0-31
61        OP4 OSC FREQ FINE          0-99
62        OP4 OSC DETUNE             0-14

63        OP3 EG rate A              0-99
64         "  "  rate D               "
65         "  "  rate S               "
66         "  "  rate R               "
67         "  " level A               "
68         "  " level D               "
69         "  " level S              "
70         "  " level R               "
71        OP3 KBD LEV SCL BRK PT      "        C3= $27
72         "   "   "   "  LFT DEPTH   "
73         "   "   "   "  RHT DEPTH   "
74         "   "   "   "  LFT CURVE  0-3       0=-LIN, -EXP, +EXP, +LIN
75         "   "   "   "  RHT CURVE   "            "    "    "    "
76        OP3 KBD RATE SCALING       0-7
77        OP3 AMP MOD SENSITIVITY    0-3
78        OP3 KEY VEL SENSITIVITY    0-7
79        OP3 OPERATOR OUTPUT LEVEL  0-99
80        OP3 OSC MODE (fixed/ratio) 0-1        0=ratio
81        OP3 OSC FREQ COARSE        0-31
82        OP3 OSC FREQ FINE          0-99
83        OP3 OSC DETUNE             0-14

84        OP2 EG rate A              0-99
85         "  "  rate D               "
86         "  "  rate S               "
87         "  "  rate R               "
88         "  " level A               "
89         "  " level D               "
90         "  " level S              "
91         "  " level R               "
92        OP2 KBD LEV SCL BRK PT      "        C3= $27
93         "   "   "   "  LFT DEPTH   "
94         "   "   "   "  RHT DEPTH   "
95         "   "   "   "  LFT CURVE  0-3       0=-LIN, -EXP, +EXP, +LIN
96         "   "   "   "  RHT CURVE   "            "    "    "    "
97        OP2 KBD RATE SCALING       0-7
98        OP2 AMP MOD SENSITIVITY    0-3
99        OP2 KEY VEL SENSITIVITY    0-7
100        OP2 OPERATOR OUTPUT LEVEL  0-99
101        OP2 OSC MODE (fixed/ratio) 0-1        0=ratio
102        OP2 OSC FREQ COARSE        0-31
103        OP2 OSC FREQ FINE          0-99
104        OP2 OSC DETUNE             0-14

105        OP1 EG rate A              0-99
106         "  "  rate D               "
107         "  "  rate S               "
108         "  "  rate R               "
109         "  " level A               "
110         "  " level D               "
111         "  " level S              "
112         "  " level R               "
113        OP1 KBD LEV SCL BRK PT      "        C3= $27
114         "   "   "   "  LFT DEPTH   "
115         "   "   "   "  RHT DEPTH   "
116         "   "   "   "  LFT CURVE  0-3       0=-LIN, -EXP, +EXP, +LIN
117         "   "   "   "  RHT CURVE   "            "    "    "    "
118        OP1 KBD RATE SCALING       0-7
119        OP1 AMP MOD SENSITIVITY    0-3
120        OP1 KEY VEL SENSITIVITY    0-7
121        OP1 OPERATOR OUTPUT LEVEL  0-99
122        OP1 OSC MODE (fixed/ratio) 0-1        0=ratio
123        OP1 OSC FREQ COARSE        0-31
124        OP1 OSC FREQ FINE          0-99
125        OP1 OSC DETUNE             0-14

126        PITCH EG RATE 1            0-99
127          "    " RATE 2              "
128          "    " RATE 3              "
129          "    " RATE 4              "
130          "    " LEVEL 1             "
131          "    " LEVEL 2             "
132          "    " LEVEL 3             "
133          "    " LEVEL 4             "
134        ALGORITHM #                 0-31
135        FEEDBACK                    0-7
136        OSCILLATOR SYNC             0-1
137        LFO SPEED                   0-99
138         "  DELAY                    "
139         "  PITCH MOD DEPTH          "
140         "  AMP   MOD DEPTH          "
141        LFO SYNC                    0-1
142         "  WAVEFORM                0-5, (data sheet claims 9-4 ?!?)
                                       0:TR, 1:SD, 2:SU, 3:SQ, 4:SI, 5:SH
143        PITCH MOD SENSITIVITY       0-7
144        TRANSPOSE                   0-48   12 = C2
145        VOICE NAME CHAR 1           ASCII
146        VOICE NAME CHAR 2           ASCII
147        VOICE NAME CHAR 3           ASCII
148        VOICE NAME CHAR 4           ASCII
149        VOICE NAME CHAR 5           ASCII
150        VOICE NAME CHAR 6           ASCII
151        VOICE NAME CHAR 7           ASCII
152        VOICE NAME CHAR 8           ASCII
153        VOICE NAME CHAR 9           ASCII
154        VOICE NAME CHAR 10          ASCII
155        OPERATOR ON/OFF
              bit6 = 0 / bit 5: OP1 / ... / bit 0: OP6
 */

#include <unistd.h>
#include <sys/time.h>
#include <ctime>
#include "RtMidi.h"
#include <chrono>
#include <csignal>
const unsigned char nouts = 16;
using namespace std;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

const string PORT_PREFIX = "DX";
void onMIDI(double deltatime, std::vector<unsigned char> *message, void * /*userData*/);
int limit(int val, int min, int max);
unsigned char validCC[14] = {1, 2, 7, 10, 64, 66, 120, 121, 122, 123, 124, 125, 126, 127};
void print();
void cleanup();
void listInports();
void initHWPORT();
void signalHandler(int signum);
string oPORTNAME = "";
bool HW_EXISTS = false;
void listOutPorts();
long long getSecs();
int getOutPort(std::string str);
int getInPort(std::string str);
long long nextCheck = 0;
void sendMessage(vector<unsigned char> *message);
vector<unsigned char> BASE_SYX{0xF0, 0x43, 0x10, 0, 0, 0, 0xF7};
enum BPOS
{
    GROUP = 3,
    PARAMETER = 4,
    DATA = 5

};
enum CCTYPES
{
    SYSTEM,
    SYSEX,
    SKIP,
    CC
};

struct CC_MAPPING
{
    //  int x = 0;
    CC_MAPPING(CCTYPES TYPE, int CC, int MIN, int MAX, int GROUP, int PARAMETER) : TYPE(TYPE), CC(CC), MIN(MIN), MAX(MAX), GROUP(GROUP), PARAMETER(PARAMETER){};
    CCTYPES TYPE = SKIP;
    int CC = 0;
    int MIN = 0;
    int MAX = 99;
    int GROUP = 0;
    int PARAMETER = 0;
};

CC_MAPPING MAP[128] = {
    {SKIP, 0, 0, 127, 0, 0},     // 0
    {CC, 1, 0, 127, 0, 0},       // 1
    {CC, 2, 0, 127, 0, 0},       // breath
    {SYSEX, 3, 0, 99, 1, 9},     // 1 LFo SPEED
    {CC, 4, 0, 127, 0, 0},       // Foot
    {CC, 5, 0, 127, 0, 0},       // Portamento
    {SYSEX, 6, 0, 99, 1, 10},    // LFO DELAY
    {CC, 7, 0, 127, 0, 0},       // 7 Volume
    {SYSEX, 8, 0, 127, 1, 11},   // 8 LFO PMD
    {SYSEX, 9, 0, 127, 1, 12},   // 9 LFO AMD
    {CC, 10, 0, 127, 0, 0},      // 10 PAN
    {CC, 7, 0, 127, 0, 0},       // 11  Expression routed to Volume
    {SYSEX, 12, 0, 5, 1, 14},    // 12 LFO WAVE
    {SKIP, 13, 0, 127, 0, 0},    // 1
    {SKIP, 14, 0, 127, 0, 0},    // 1
    {SKIP, 15, 0, 127, 0, 0},    // 1
    {SKIP, 16, 0, 127, 0, 0},    // 1
    {SKIP, 17, 0, 127, 0, 0},    // 1
    {SKIP, 18, 0, 127, 0, 0},    // 1
    {SKIP, 19, 0, 127, 0, 0},    // 1
    {SYSEX, 20, 0, 99, 0, 105},  // 20 Att Rate Op1
    {SYSEX, 21, 0, 99, 0, 84},   // 21 a Rate Op2
    {SYSEX, 22, 0, 99, 0, 63},   // 22 a Rate Op3
    {SYSEX, 23, 0, 99, 0, 42},   // 23 a Rate op4
    {SYSEX, 24, 0, 99, 0, 21},   // 24
    {SYSEX, 25, 0, 99, 0, 0},    //  25 op6
    {SYSEX, 26, 0, 99, 0, 106},  // 26 Decay op1
    {SYSEX, 27, 0, 99, 0, 85},   // 27
    {SYSEX, 28, 0, 99, 0, 64},   // 28
    {SYSEX, 29, 0, 99, 0, 43},   // 29
    {SYSEX, 30, 0, 99, 0, 22},   // 30
    {SYSEX, 31, 0, 99, 0, 1},    // 1
    {SYSEX, 32, 0, 99, 0, 107},  // Sus op1
    {SYSEX, 33, 0, 99, 0, 86},   // 1
    {SYSEX, 34, 0, 99, 0, 65},   // 1
    {SYSEX, 35, 0, 99, 0, 44},   // 1
    {SYSEX, 36, 0, 99, 0, 23},   // 1
    {SYSEX, 37, 0, 99, 0, 2},    // 1
    {SYSEX, 38, 0, 99, 0, 108},  // 1 REl op1
    {SYSEX, 39, 0, 99, 0, 87},   // 1
    {SYSEX, 40, 0, 99, 0, 66},   // 1
    {SYSEX, 41, 0, 99, 0, 45},   // 1
    {SYSEX, 42, 0, 99, 0, 24},   // 1
    {SYSEX, 43, 0, 99, 0, 3},    //
    {SYSEX, 44, 0, 31, 0, 123},  // 1 Coarse op1
    {SYSEX, 45, 0, 31, 0, 102},  // 1
    {SYSEX, 46, 0, 31, 0, 81},   // 1
    {SYSEX, 47, 0, 31, 0, 60},   // 1
    {SYSEX, 48, 0, 31, 0, 39},   // 1
    {SYSEX, 49, 0, 31, 0, 18},   // 1
    {SYSEX, 50, 0, 99, 0, 124},  // 1 Fine Op1
    {SYSEX, 51, 0, 99, 0, 103},  // 1
    {SYSEX, 52, 0, 99, 0, 82},   // 1
    {SYSEX, 53, 0, 99, 0, 61},   // 1
    {SYSEX, 54, 0, 99, 0, 40},   // 1
    {SYSEX, 55, 0, 99, 0, 19},   // 1
    {SKIP, 56, 0, 127, 0, 0},    // 1
    {SKIP, 57, 0, 127, 0, 0},    // 1
    {SKIP, 58, 0, 127, 0, 0},    // 1
    {SKIP, 59, 0, 127, 0, 0},    // 1
    {SKIP, 60, 0, 127, 0, 0},    // 1
    {SKIP, 61, 0, 127, 0, 0},    // 1
    {SKIP, 62, 0, 127, 0, 0},    // 1
    {SKIP, 63, 0, 127, 0, 0},    // 1
    {CC, 64, 0, 127, 0, 0},      // Sustain
    {SKIP, 65, 0, 127, 0, 0},    // 1
    {CC, 66, 0, 127, 0, 0},      // Sostenuto
    {SKIP, 67, 0, 127, 0, 0},    // 1
    {SKIP, 68, 0, 127, 0, 0},    // 1
    {SKIP, 69, 0, 127, 0, 0},    // 1
    {SKIP, 70, 0, 127, 0, 0},    // 1
    {CC, 71, 0, 127, 0, 0},      // 1 Resonane For Dexed
    {SKIP, 72, 0, 127, 0, 0},    // 1
    {SYSEX, 73, 0, 48, 1, 16},   // Transpose
    {CC, 74, 0, 127, 0, 0},      // Curoff for Dexed Midi Learn
    {SYSEX, 75, 0, 7, 1, 7},     // Feedback
    {SYSEX, 76, 0, 31, 1, 6},    // Algorithm
    {SKIP, 77, 0, 127, 0, 0},    // 1
    {SYSEX, 78, 0, 99, 0, 109},  // Atk level 1
    {SYSEX, 79, 0, 99, 0, 110},  //  dc 1 lvl 1
    {SYSEX, 80, 0, 99, 0, 111},  // sus lvl 1
    {SYSEX, 81, 0, 99, 0, 112},  // rel lvl 1
    {SYSEX, 82, 0, 99, 0, 88},   // a lvl 2
    {SYSEX, 83, 0, 99, 0, 89},   // 1
    {SYSEX, 84, 0, 99, 0, 90},   // 1
    {SYSEX, 85, 0, 99, 0, 91},   // 1
    {SYSEX, 86, 0, 99, 0, 67},   // op3
    {SYSEX, 87, 0, 99, 0, 68},   // 1
    {SYSEX, 88, 0, 99, 0, 69},   // 1
    {SYSEX, 89, 0, 99, 0, 70},   // 1
    {SYSEX, 90, 0, 99, 0, 46},   // op 4
    {SYSEX, 91, 0, 99, 0, 47},   // 1
    {SYSEX, 92, 0, 99, 0, 48},   // 1
    {SYSEX, 93, 0, 99, 0, 49},   // 1
    {SYSEX, 94, 0, 99, 0, 25},   // op5
    {SYSEX, 95, 0, 99, 0, 26},   // 1
    {SYSEX, 96, 0, 99, 0, 27},   // 1
    {SYSEX, 97, 0, 99, 0, 28},   // 1
    {SYSEX, 98, 0, 99, 0, 4},    // op6
    {SYSEX, 99, 0, 99, 0, 5},    // 1
    {SYSEX, 100, 0, 99, 0, 6},   // 1
    {SYSEX, 101, 0, 99, 0, 7},   // 1
    {SYSEX, 102, 0, 99, 0, 121}, // op level 1
    {SYSEX, 103, 0, 99, 0, 100}, // 1
    {SYSEX, 104, 0, 99, 0, 79},  // 1
    {SYSEX, 105, 0, 99, 0, 58},  // 1
    {SYSEX, 106, 0, 99, 0, 37},  // 1
    {SYSEX, 107, 0, 99, 0, 16},  // 1
    {SKIP, 108, 0, 127, 0, 0},   // 1
    {SKIP, 109, 0, 127, 0, 0},   // 1
    {SKIP, 110, 0, 127, 0, 0},   // 1
    {SKIP, 111, 0, 127, 0, 0},   // 1
    {SKIP, 112, 0, 127, 0, 0},   // 1
    {SKIP, 113, 0, 127, 0, 0},   // 1
    {SKIP, 114, 0, 127, 0, 0},   // 1
    {SKIP, 115, 0, 127, 0, 0},   // 1
    {SKIP, 116, 0, 127, 0, 0},   // 1
    {SKIP, 117, 0, 127, 0, 0},   // 1
    {SKIP, 118, 0, 127, 0, 0},   // 1
    {SKIP, 119, 0, 127, 0, 0},   // 1
    {SYSTEM, 120, 0, 127, 0, 0}, // 1
    {SYSTEM, 121, 0, 127, 0, 0}, // 1
    {SYSTEM, 122, 0, 127, 0, 0}, // 1
    {SYSTEM, 123, 0, 127, 0, 0}, // 1
    {SYSTEM, 124, 0, 127, 0, 0}, // 1
    {SYSTEM, 125, 0, 127, 0, 0}, // 1
    {SYSTEM, 126, 0, 127, 0, 0}, // 1
    {SYSTEM, 127, 0, 127, 0, 0}, // 1

};

RtMidiIn *midiIn = 0;
RtMidiOut *SYX = 0;
RtMidiOut *HWOUT = 0;

int main(int argc, char *argv[])
{
    midiIn = new RtMidiIn();
    midiIn->setCallback(&onMIDI);
    midiIn->ignoreTypes(false, false, true); // dont ignore clocK
    SYX = new RtMidiOut();
    HWOUT = new RtMidiOut();
    signal(SIGINT, signalHandler);

    if (argc > 1)
    {
        string cmd(argv[1]);
        cout << "Command: " << cmd << endl;
        if (cmd == "-ports")
        {
            listOutPorts();
            cout << endl
                 << endl;
            //     listInports();
            cleanup();
        }
        /*  if (cmd == "-print")
          {

              cleanup();
          }*/
        if (cmd == "-p")
        {
            if (argc < 3)
            {
                cout << "Error ! Please Provide Midi Port Name to bind to!" << endl;
                cleanup();
            }
            oPORTNAME = string(argv[2]);
            initHWPORT();
        }
    }

    if (oPORTNAME == "")
    {
        SYX->openVirtualPort(PORT_PREFIX + "SYX");
        cout << "dxsex => Created Virtual Output Port: " << PORT_PREFIX << "SYX" << endl;
    }
    midiIn->openVirtualPort(PORT_PREFIX + "CC");
    cout << "dxsex => Created Virtual Input Port: " << PORT_PREFIX << "CC" << endl;
    cout << "Send Your CC Commands to PORT: " << PORT_PREFIX << "CC" << endl;

    while (true) // the main loop
    {

        if (oPORTNAME != "")
        {
            long elapsed = getSecs() - nextCheck;
            if (elapsed >= 2)
            {
                int pid = getOutPort(oPORTNAME);
                if (pid == -1)
                {
                    HW_EXISTS = false;
                }
                else
                {
                    if (HW_EXISTS == false)
                    {
                        initHWPORT();
                    }
                }
                nextCheck = getSecs() + 2;
            }
        }

        usleep(5000);
    }
    cleanup();
    return 0;
}

void onMIDI(double deltatime, std::vector<unsigned char> *message, void * /*userData*/) // handles incomind midi
{

    unsigned char byte0 = (int)message->at(0);
    unsigned char typ = byte0 & 0xF0;
    unsigned char ch = byte0 & 0x0F;
    uint size = message->size();
    if (size == 1 || byte0 == 0xF0 || typ != 0xB0) // sysex or clock or non cc
    {
        sendMessage(message);
    }
    else
    {
        int mCC = (int)message->at(1);
        CC_MAPPING C = MAP[mCC];
        // cout << "MAP: " << C.TYPE << " Param: " << C.PARAMETER << endl;
        if (C.TYPE == CC || C.TYPE == SYSTEM)
        {
            // cout << "CC: " << mCC << endl;
            message->at(1) = C.CC; // remap incoming CC to target CC as in MAP.
            sendMessage(message);
            return;
        }
        if (C.TYPE == SYSEX)
        {

            vector<unsigned char> oSYX = BASE_SYX;
            int value = limit(message->at(2), C.MIN, C.MAX);
            oSYX.at(BPOS::GROUP) = C.GROUP;
            oSYX.at(BPOS::PARAMETER) = C.PARAMETER;
            oSYX.at(BPOS::DATA) = value;
            // cout << "CC for Syx: " << mCC << " Value: " << value << endl;
            sendMessage(&oSYX);
        }
    }
}

int limit(int v, int min, int max)
{
    if (v < min)
        v = min;
    if (v > max)
        v = max;
    return v;
}

void listInports()
{
    uint nPorts = midiIn->getPortCount();
    cout << "************ INPUTS ************" << endl;
    for (uint i = 0; i < nPorts; i++)
    {
        std::string portName = midiIn->getPortName(i);
        std::cout << portName << "\n";
    }
}
void listOutPorts()
{
    uint nPorts = SYX->getPortCount();
    cout << "************ Midi Outputs ************" << endl;
    for (uint i = 0; i < nPorts; i++)
    {
        std::string portName = SYX->getPortName(i);
        std::cout << portName << "\n";
    }
}
void cleanup()
{
    delete midiIn;
    delete SYX;
    HWOUT->closePort();
    delete HWOUT;
    exit(0);
}

int getinPort(std::string str)
{
    int nPorts = midiIn->getPortCount();
    for (int i = 0; i < nPorts; i++)
    {
        std::string portName = midiIn->getPortName(i);
        size_t found = portName.find(str);
        if (found != string::npos)
        {
            return i;
        }
    }
    return 99;
}
int getOutPort(std::string str)
{
    int nPorts = SYX->getPortCount();
    for (int i = 0; i < nPorts; i++)
    {
        std::string portName = SYX->getPortName(i);
        size_t found = portName.find(str);
        if (found != string::npos)
        {
            return i;
        }
    }
    return -1;
}
void initHWPORT()
{
    int oid = getOutPort(oPORTNAME);
    if (oid != -1)
    {
        if (HWOUT->isPortOpen())
        {
            HWOUT->closePort();
        }
        try
        {
            HWOUT->openPort((unsigned int)oid, PORT_PREFIX + "SYX");
            HW_EXISTS = true;
            cout << "Opened HW Port (" << SYX->getPortName(oid) << " as " << PORT_PREFIX << "SYX) for Output with ID: " << oid << endl;
        }
        catch (...)
        {
            HW_EXISTS = false;
            cout << "Error Opening: " << SYX->getPortName(oid) << "for Output" << endl;
        }
    }
    else
    {
        HW_EXISTS = false;
        cout << oPORTNAME << "Not Available Yet" << endl;
    }
}
void sendMessage(vector<unsigned char> *message)
{
    if (oPORTNAME == "")
        SYX->sendMessage(message);
    else
    {

        try
        {
            HWOUT->sendMessage(message);
        }
        catch (...)
        {
            cout << "Error Sendind Midi to: " << oPORTNAME << endl;
        }
    }
}
long long getSecs() // gets time since epch in seconds
{
    auto t1 = std::chrono::system_clock::now();
    long long us = duration_cast<seconds>(t1.time_since_epoch()).count();
    return us;
}
void signalHandler(int signum)
{
    cout << "Interrupt signal (" << signum << ") received.\n";
    cout << "Process dxsex Terminiated!" << endl;
    cleanup();
}