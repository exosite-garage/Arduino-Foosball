================================================================================
About Arduino Foosball
================================================================================
This project is a simple Arduino C code project that runs on Arduino Uno or
Deumilanove board with attached Ethernet shield.  The Leaderboard and video at 
https://portals.exosite.com/views/2219771501/1385257981 shows how the thing
was put together.  In general, it is a sumper simple system - just sending
raw data up to the cloud where the data from the Avatars and goal sensors is
parsed to create a web-enabled Foosball table - Internet of Things gaming!

License is BSD, Copyright 2013, Exosite LLC (see LICENSE file)

Tested with Arduino 1.0.1

================================================================================
Quick Start
================================================================================
1) Download the Arduino toolchain and development environment<br>
* http://www.arduino.cc/en/Main/software<br>

2) Download the Exosite Arduino library<br>
* https://github.com/exosite-garage/arduino_exosite_library<br>

3) Configure the toolchain to use the libary
* Open the Arduino toolchain
* Go to "Sketch->Show Sketch Folder", your Sketch folder will then be displayed. 
* Create a directory named "libraries" if it does not exist.
* Copy the Exosite library folder to the directory 
  sketchbook-location\"libraries". 
* You should then see "File->Examples->Exosite"

2) Open the "foosball.ino" file in the Arduino toolchain<br>

3) Edit the "PUTYOURCIKHERE" value in foosball.ino to match your CIK value<br>
* HINT: Obtain a CIK from https://portals.exosite.com by clicking +Add Device<br>

4) In Portals (https://portals.exosite.com), add DataSources to match the data 
resources (aliases) the code is using.<br>
* HINT: Goto https://portals.exosite.com/manage/data and click +Add Data Source<br>
* HINT: Ensure the "Resource:" (alias) values are set to: game_state, player_a1, 
  player_a2, player_b1, player_b2, goals_a, goals_b - to match the code<br>
* HINT: Add additional scripts or post-processed data elements to make the 
  incoming data meaninful!

6) In the Arduino software, compile and verify there are no errors<br>

7) Go to Tools->Serial Port and select the serial port your Arduino is connected to<br>

8) Go to File->Upload to I/O Board to upload the program<br>

9) After "Done uploading" is displayed, go to https://portals.exosite.com to see
your data in the cloud!<br>
* HINT: Your Arduino must be connected to the Internet via the RJ-45 ethernet jack<br>

For more information on this project and other examples, checkout our Exosite
Garage github page at http://exosite-garage.github.com<br>

================================================================================
Release Info
================================================================================
--------------------------------------------------------------------------------
Release 2013-02-19<br>
--------------------------------------------------------------------------------
--) first release<br>
--) seems to work great - been in operation for about 3 months<br>

