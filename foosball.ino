//*****************************************************************************
// foosball.ino - Sends foosball data to the cloud
//
// License is BSD - see file LICENSE for more information
//
//*****************************************************************************

#include <SPI.h>
#include <Ethernet.h>
#include <Exosite.h>

//global variables
byte macData[] = { "0x90,0xA2,0xDA,0xFE,0xEE,0xEE"  }; // <-- Fill in your MAC here! (e.g. {0x90, 0xA2, 0xDA, 0x00, 0x22, 0x33}) 
String cikData = "PUTYOURCIKHERE";      // <-- Fill in your CIK here! (https://portals.exosite.com -> Add Device)
Exosite exosite(&Ethernet, macData, cikData);

int goala = A0;      // input pin for goala (not full 5V)
int playera1 = A1;    // input pin for player a1 select
int playera2 = A2;    // input pin for player a2 select
int playerb1 = A3;    // input pin for player b1 select
int playerb2 = A4;    // input pin for player b2 select
int goalb = A5;       // input pin for goalb
int gameon = 2;      // digital square wave indicating gameon
int resetpin = 7;    // ethernet goes out from time to time, so we reset the board from time to time
int counter = 0;
int game_state = 0;

/*==============================================================================
* setup
*
* Arduino setup function.
*=============================================================================*/
void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing foosball table");
  game_state = 0;
  exosite.init();
  Serial.println("Exosite On");  
  exosite.sendToCloud("game_state", 0);
}

/*==============================================================================
* loop 
*
* Arduino loop function.
*=============================================================================*/
void loop()
{

  switch (game_state) {
  case 0: //waiting to start
    if (counter++ > 10000) { //reset the board every 10,000 loops of no-activity
      pinMode(resetpin, OUTPUT);
      digitalWrite(resetpin, 0); //reset the board      
    }
    if (digitalRead(gameon)) {  //read game_on pin - this is a digital square wave that goes active when a game is being played (don't ask...)
      game_state++;  
      delay(1000); //delay for a second before going on
      Serial.println("game started");  
    }
    break;
    
  case 1: //kick the game off!
    //first, update game state
    exosite.sendToCloud("game_state", game_state);
      
    //second, check in players
    exosite.sendToCloud("player_a1", analogRead(playera1));
    exosite.sendToCloud("player_a2", analogRead(playera2));
    exosite.sendToCloud("player_b1", analogRead(playerb1));     
    exosite.sendToCloud("player_b2", analogRead(playerb2));
    
    //go into full play mode
    game_state++;
    break;
    
  case 2: //we are playing!
    
    if (analogRead(goala) < 50) {
      exosite.sendToCloud("goals_a", 1);
      Serial.println("goala");
      delay(1000); //debounce
    }
    
    if (analogRead(goalb) < 50) {
      exosite.sendToCloud("goals_b", 1);
      Serial.println("goalb");    
      delay(1000);  //debounce
    }
    
    game_state++; 
    for (counter = 0; counter < 30; counter++) { //this is still fast enough to loop and capture a goal - a goal creates a 150mS pulse
      if (digitalRead(gameon)) { //check to see if game is still on (we have to sample)
        game_state--; //go back to our current game state
        break;
      }
      delay(1);
    }
      
    break;
    
  case 3: //we are done... 
    //before shutting the game down, we re-send player values one more time
    exosite.sendToCloud("player_a1", analogRead(playera1));
    exosite.sendToCloud("player_a2", analogRead(playera2));
    exosite.sendToCloud("player_b1", analogRead(playerb1));     
    exosite.sendToCloud("player_b2", analogRead(playerb2));  
    delay(2000); //delay for a minimum of 2 seconds... 
    game_state = 0;
    exosite.sendToCloud("game_state", game_state);   
    Serial.println("game ended");
    
    pinMode(resetpin, OUTPUT);
    digitalWrite(resetpin, 0); //reset the board
      
    break;
    
  }
}

