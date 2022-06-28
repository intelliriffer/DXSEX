# dxSex - CC to Sysex Converter for DX7, VolcaFM, Dexed for Akai Force, Raspberry Pi, intel Mac.

## Download Latest Binaries 0.1.0
1. [Akai Force, Akai MPC & Raspberry Pi/Mac](https://mega.nz/file/dtgDAaJQ#YQTccky9V2LtWmvxBexHB7kM2MWfvNehzfd_1xZQDvc)

####  **[Some Nerd Stats from 40000 Unique, Presets](Most%20Popular%20DX7%20Algos.txt)

### Note: Not All Params Have Been Mapped.
Please view the code in main.cpp to check mappings for the time being until its documented.

## Installation:

** **For Mockba Modded Akai Force:**

1. With My NodeServer App (https://github.com/intelliriffer/FORCE-APPS-SERVER-MOCKBA) Installed.
   1. Copy dxsex.json and dxsex to your /media/662522/AddOns/nodeServer/modules/
   2.  Launch The NoderServer App in Browser and Go to Modules and enable DxSex. By Default it will output to the Physical Midi Din Port. To Change the Target Port, Change the Portname with Hardware Port you want to Route Sysex Output to. 
   3. You can List Available Ports by running "dxsex -ports" command in console..

2. Without The NodeServer App
   1. Copy dxSexAddon.sh and dxsex to /media/662522/AddOns and reboot Force. Henceforth dxsex will autolaunch on start.

   2. You can edit the dxSexAddon.sh script to change the dest midi port name.

** **For Non Modded Devices (raspberry pi) or intel Macs**
 
 1. Copy dxsex to your Raspberry Pi Device, (copy mac/dxsex to your mac)
 2. from Terminal run the Command dxsex -ports to list available midi ports.
 3. run dxsex -p PORTNAME to route output to needed port (Replace PORTNAME with a Valid PortName from Step 2).
 4. You may need top create a Virtual Midi Port to use with DAW or Dexed Standalone.
 5. if you run dxsex without -p, it will create a virtual DXSYX port that you can use.

## Routing
1. On Your Akai Device Load the Provided Midi Map File (DEXED - Raspi.xpm) onto a Midi Track.
2. If you have installed directly on your Akai Device, set the Midi track output to DXCC and ch 1.
3. If you are using it on a Mac or raspberry pi, Set output to the midi port that connects to that.
   1. On your Mac or Raspberry Pi, Route the Incoming Port to DXCC Virtual Port.
   2. Route DXSYX port to your H/W Device or Dexed Standalone/vst/au ...

 Changing Parameters on Akai Screen/Macro Knobs (set to screen mode) Should Change Mapped Params on your Device..









