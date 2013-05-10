// Panic Jumping Robot
// Meng Shi
// CMU Spring 2013Panic Jumping Robot

//------------IR and solenoid start------------
int IRpin = 1;  
int solenoid1=5;
int solenoid2=6;
int fan=4;
int iswitch;
int counter;
int brightness = 0;    // how bright the LED is
int fadeAmount = 15;    // how many points to fade the LED by
int speed = 190;

//------------RGB LED start------------

#include <Wire.h>
#include "BlinkM_funcs.h"


int blinkm_addr = 9;//default address to blinkM
byte r,g,b;

int photocellPin = 0;// Photocell connected to analog pin 0
int photocellVal = 0; // define photocell variable
int minLight = 700;//min light threshold
int maxLight = 800;//max light threshold
int ledState = 0; //state of the led 0 = dark, 1 = light 


//------------Music start------------
#include "pitches.h"
int intro[] = {
  //intro
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B5,
  NOTE_CS6,
  NOTE_DS6,
  NOTE_CS6,
  NOTE_AS5,
  NOTE_B5,
  NOTE_FS5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B5,
  NOTE_CS6,
  NOTE_AS5,
  NOTE_B5,
  NOTE_CS6,
  NOTE_E6,
  NOTE_DS6,
  NOTE_E6,
  NOTE_B5, 

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8, //13
  8,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16 //25 intro
};


int melody[] = {
  //A
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_DS5,
  REST,
  NOTE_B4,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  REST,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_D5,
  NOTE_DS5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_DS5,
  REST,
  NOTE_B4,
  NOTE_D5, 
  NOTE_CS5,
  NOTE_B4,
  REST,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_GS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_D5,
  NOTE_DS5,
  NOTE_D5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_D5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_FS5,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  NOTE_B4,
  NOTE_CS5,
  //end of loop
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_DS4,
  NOTE_E4,
  NOTE_FS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_FS4,
  //
  NOTE_B4,
  NOTE_B4,
  NOTE_AS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_E4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_AS4,
  //
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_CS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_DS4,
  NOTE_E4,
  NOTE_FS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_B4,
  NOTE_CS5,
  NOTE_DS5,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_FS4,
  NOTE_B4,
  NOTE_B4,
  NOTE_AS4,
  NOTE_B4,
  NOTE_FS4,
  NOTE_GS4,
  NOTE_B4,
  NOTE_E5,
  NOTE_DS5,
  NOTE_E5,
  NOTE_FS5,
  NOTE_B4,
  NOTE_CS5 

};
int melodyNoteDurations[] = {
  //a
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16, 
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16, 
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  8,
  //
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  //
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  //
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  16,
  16,
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  //
  8,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  8,
  8 
};

// --------Music end------------

void setup(){
  Serial.begin(9600);  


  pinMode(solenoid1, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(fan, OUTPUT);

  digitalWrite(fan, HIGH);
  //  digitalWrite(solenoid1, LOW);
  pinMode(photocellPin, INPUT);

  BlinkM_beginWithPower();
  BlinkM_stopScript(blinkm_addr);//stop the BlinkM 
  BlinkM_setFadeSpeed(blinkm_addr, 5);//set up fade param for a smooth fade
      playstart();
}

void loop(){
  counter=counter+1;
  if(counter>=800){
     iswitch=0;
     counter=0;
  }
  // IR sensor
  float volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
//  Serial.println(distance); 
  Serial.println(distance);   // print the distance
  //  delay(100);   

  if(distance<30){

    if( iswitch==0){
//      playstart();
    }
    else{
      speed=1;
    }
    // when the user approach the robot will go faster
  }

  // when the user at normal distance it will at narmal pace
  else{
    speed =10;

  }



  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     

  if (brightness<200){
    digitalWrite(solenoid1, LOW);
    digitalWrite(solenoid2, LOW);
    delay(speed); 
  }
  else{
    digitalWrite( solenoid1, HIGH);
    digitalWrite(solenoid2, HIGH);
    iswitch+=1;
    delay(speed); 
  }

  // wait for 30 milliseconds to see the dimming effect    


  photocellVal = analogRead(photocellPin);//get photocells value

  //conditional which determines if its dark or not
  if (photocellVal < minLight and ledState == 1){
    displayColor(0);
  }                      
  else if (photocellVal > maxLight and ledState == 0){
    displayColor(1);

  }   
}

void displayColor(int val)
{

  switch(val)
  {
  case 0:
    r = 0;
    g = 255;
    b = 255;

    ledState = 0;
    break;
    
  case 1:
    r = 20;
    g = 34;
    b = 102;
    //0;34;102 Royal Blue 5

    ledState = 1;
    break;
  }

  BlinkM_fadeToRGB(blinkm_addr, r,  g,  b);//call which fades to desired color

}




void playstart(){

  for (int thisNote = 0; thisNote < 25; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1500/noteDurations[thisNote];
    tone(8, intro[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void playcat(){
  for (int thisNote = 0; thisNote > 1 && thisNote <3; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1400/melodyNoteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
















