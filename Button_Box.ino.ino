#include <Keypad.h>

/*
 * SOFTWARE REQUIREMENTS
 * 
 * Black Boxes need to be set in app.ini before sim launch via the software
 * values to edit:
 * [Drive Screen]
 * blackBox=2
 * [Main Screen]
 * blackBox=0
 * 
 * Use Powershell.ps1 script for folder location. (or equivilent VS coding) EG:
 * include .\Powershell.ps1
 * $mydocs = $(Get-SpecialFolders).mydocuments
 * $inifile = $mydocs + "\iracing\app.ini"
 * 
 * iracing SDK VARIABLES TO PARSE:
 * IsInGarage     bool
 * IsOnTrack      bool
 * IsOnTrackCar   bool
 * EnterExitReset where 0 = enter, 1 = Exit, 2 = Reset
 * 
 * currentBB = cBBnone;
 * Switch (EnterExitReset) {
 *    case 0:
 *             
 *    break;
 * }
 */

// Debugging Variables
String currentBB;

// are we in the car or not
boolean IsInCar = false;
// pause between startup flash
const int pause = 250;
// Sets the Mute LED blink rate
const long muteBlink = 500;
// Mute button state
int muteState;
// Previous time
unsigned long previousMillis = 0;
int muteLedstate = LOW;

// LED Pins
const int ledFuel = 17; 
const int ledIncar = 16; 
const int ledLaptime = 15; 
const int ledPit = 12; 
const int ledRel = 13; 
const int ledTires = 14; 
const int ledRadio = 19; 
const int ledMute = 18; 

// Keypad outputs
const char BBfuel = '3'; 
const char BBincar = '2'; 
const char BBlaptime = '1';
const char BBpit = '6'; 
const char BBrel = '5'; 
const char BBtires = '7';
const char BBradio = 'J';
const char delta = '4'; 
const char BBnext = 'C';
const char BBprev = '8'; 
const char chatOK = 'E';
const char chatPassLaft = '9';
const char chatPassRight = 'A';
const char chatQuit = 'L';  
const char chatShutUp = 'H';
const char cahtSorry = 'M'; 
const char chatThanks = 'I';
const char chatURwelcome = 'D';
const char mark = 'G'; 
const char reset = 'O';
const char record = 'K';
const char chatMute = 'N';
const char radioNext = 'B';
const char radioPrev = 'F';

// Black Box Numbers for switch statement
const int cBBNone = 0;
const int cBBLaptime = 1;
const int cBBStandings = 2;
const int cBBRelative = 3;
const int cBBFuel = 4;
const int cBBTires = 5;
const int cBBTireInfo = 6;
const int cBBPitStop = 7;
const int cBBInCar = 8;
const int cBBGraphics = 9;
const int cBBRadio = 10; 

const byte ROWS = 6; // Four rows  //24 Buttons
const byte COLS = 4; // six columns
// Define the Keymap
char hexaKeys[ROWS][COLS] = {
      {'1','2','3','4'}, //Button connnected to PIN 2 ORANGE
      {'5','6','7','8'}, //Button connnected to PIN 3 BLUE
      {'9','A','B','C'}, //Button connnected to PIN 4 Orange
      {'D','E','F','G'}, //Button connnected to PIN 5 YELLOW
      {'H','I','J','K'}, //Button connnected to PIN 6 BROWN
      {'L','M','N','O'}, //Button connnected to PIN 7 WHITE
     
//PIN:  8   9  10   11
//PIN:  WHITE YELLOW BROWN  GREEN  

};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {2, 3, 4, 5, 6, 7};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {8, 9, 10, 11}; 

// Create the Keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

void setup() {
Serial.begin(9600);
pinMode(ledRadio, OUTPUT);
pinMode(ledTires, OUTPUT);
pinMode(ledRel, OUTPUT);
pinMode(ledPit, OUTPUT);
pinMode(ledFuel, OUTPUT);
pinMode(ledIncar, OUTPUT);
pinMode(ledLaptime, OUTPUT);
pinMode(ledMute, OUTPUT);

// Startup test
digitalWrite(ledLaptime, HIGH);
delay(pause);
digitalWrite(ledLaptime, LOW);
digitalWrite(ledIncar, HIGH);
delay(pause);
digitalWrite(ledIncar, LOW);
digitalWrite(ledFuel, HIGH);
delay(pause);
digitalWrite(ledFuel, LOW);
digitalWrite(ledRel, HIGH);
delay(pause);
digitalWrite(ledRel, LOW);
digitalWrite(ledPit, HIGH);
delay(pause);
digitalWrite(ledPit, LOW);
digitalWrite(ledTires, HIGH);
delay(pause);
digitalWrite(ledTires, LOW);
digitalWrite(ledRadio, HIGH);
delay(pause);
digitalWrite(ledRadio, LOW);
digitalWrite(ledMute, HIGH);
delay(pause);
digitalWrite(ledMute, LOW);
}

void allLedsOff() {
  digitalWrite(ledRadio, LOW);
  digitalWrite(ledTires, LOW);
  digitalWrite(ledRel, LOW);
  digitalWrite(ledPit, LOW);
  digitalWrite(ledFuel, LOW);
  digitalWrite(ledIncar, LOW);
  digitalWrite(ledLaptime, LOW);
}

void loop() {
 // read the state of the pushbutton value
char key = customKeypad.getKey();
if (key != NO_KEY){
  switch(key) {
    Serial.println(key);
    case BBradio:
      allLedsOff();
      digitalWrite(ledRadio, HIGH);
      currentBB = "Radio";
    break;
    case BBtires:
      allLedsOff();
      digitalWrite(ledTires, HIGH);
      currentBB = "Tires";
    break;
    case BBrel:
      allLedsOff();
      digitalWrite(ledRel, HIGH);
      currentBB = "Relative";
    break;
    case BBpit:
      allLedsOff();
      digitalWrite(ledPit, HIGH);
      currentBB = "Pit Stop Adjustments";
    break;
    case BBfuel:
      allLedsOff();
      digitalWrite(ledFuel, HIGH);
      currentBB = "Fuel";
    break;
    case BBincar:
      allLedsOff();
      digitalWrite(ledIncar, HIGH);
      currentBB = "In-car Adjustments";
    break;
    case BBlaptime:
      allLedsOff();
      digitalWrite(ledLaptime, HIGH);
      currentBB = "Lap time";
    break;
    case chatMute:
      if (muteState == 0) {
        muteState = 1;
      } else {
        muteState = 0;
      }
     break;
  }  
  Serial.println(key);
  }

if (muteState == 1) {
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= muteBlink) {
    previousMillis = currentMillis;
    if (muteLedstate == LOW) {
      muteLedstate = HIGH;
    } else {
      muteLedstate = LOW;
    }
//      digitalWrite(ledMute, HIGH);
//    delay(250);
 //   digitalWrite(ledMute, LOW);
  }
} else {
 //   digitalWrite(ledMute, LOW);
    muteLedstate = LOW;
  }
digitalWrite(ledMute, muteLedstate);
Serial.flush();
}


