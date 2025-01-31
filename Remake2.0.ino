#include <Wire.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string>
// #include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <Arduino.h>
#include "dropDown.h"
#include "paw.h"
#include "sensor.h"
#include "kicker.h"
#include "bumper.h"
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

// Defining size, and output pins
//MAIN CODE MAX DEVICES
//#define MAX_DEVICES 32
//TESTING MAX DEVICEs
#define MAX_DEVICES 4
#define NUM_ZONES 4
#define DATA_PIN 51
#define CLK_PIN 52
#define CS_PIN 50


// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola  myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
File pinBall;
// TMRpcm audio;
dropDown dropDown1(49,48,47,30,21);
dropDown dropDown2(46,45,44,31,21);
dropDown dropDown3(43,42,41,29,21);
paw paw1(36,24);
paw paw2(35,24);
paw paw3(34,24);
paw paw4(37,24);
sensor sensor(40,27);
kicker kickerL(33,26);
kicker kickerR(32,26);
bumper bumperR(39,22,25);
bumper bumperL(38,23,25);

const int Start = 7;
const int Stop = 6;
const int Reset = 5;
const char *message[13] = 
{
  //"SPACE CATS", "Lets Play!", "Please wait", " Press Start", "Game starting", "Game ON" , "Balls Left", "", "Ball Lost", "Game Over!", "Game Resetting", "New Record!"
   "A", "B", "C", "D", "E","F","G","H","I","J","K"
};


int Start_game = 0;
int Stop_game = 0;
int Reset_game = 0;
int lastButtonState = 0; 
int dropDownState = 0;
int score= 0;
int point = 1;
unsigned long started = 0;
unsigned long elapsedTime = 0;
char scoreArray[2000];
char highScoreArray[20];
int MaxBalls = 5;
long RecordScore = 0;
int gameOn = 0;
int First_scan = 0;
int startState = 0;
int stopState = 0;

uint16_t speed = 500;
uint16_t pause = 500;
uint8_t display = 0;

void setup() 
  {
  Serial.begin(9600);
  //  while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  //}
  Serial.print("Initializing SD card...");
  if (!SD.begin(SDCARD_SS_PIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  //read SD card and assign to RecordScore
  char buffer[10];
  int index = 0;
  int input = 0;
   for(int i = 0; i < 10; i++)
   {
          buffer[i] = NULL;
   }
        
  pinBall = SD.open ("high.txt");
  if (pinBall)
  {
    Serial.println("high.txt:");
    while (pinBall.available())
    {
      int num = pinBall.read();
      if(num != 10)
      {
        //write in next location in buffer
        buffer[index++] = num;
         //Serial.println(buffer);
         Serial.write(num);
    }
    input = atoi(buffer);
    RecordScore=input;
  }
    pinBall.close();
  }
  else
  {
    Serial.println("Error Opening Text");
  }

  pinMode(Start, INPUT); //set Start pin as input
  pinMode(Reset, INPUT); //set Reset pin as input
  pinMode(Stop, INPUT);  //set Stop (ball lost) as input
  myDisplay.begin(NUM_ZONES);

  //MAIN DISPLAY
  // myDisplay.setZone(0,0,7); // current score zone
  // myDisplay.setZone(1,8,15); // HIGH score zone
  // myDisplay.setZone(2,16,23); // Messages Zone
  // myDisplay.setZone(3,24,31); // Space Cats Zone

  //Display for TESTING ONLY
  myDisplay.setZone(0,0,0); // current score zone
  myDisplay.setZone(1,1,1); // HIGH score zone
  myDisplay.setZone(2,2,2); // Messages Zone
  myDisplay.setZone(3,3,3); // Space Cats Zone


  myDisplay.setIntensity(2);
  myDisplay.setInvert(false);
  myDisplay.displayZoneText(3,message[0], PA_CENTER, speed, pause, PA_NO_EFFECT,PA_NO_EFFECT);
  myDisplay.displayZoneText(2, message[1], PA_CENTER,speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
 }

void loop() 
  {
  displayMessages();
    if (myDisplay.displayAnimate()) // animates and returns true when an animation is completed
  {
    for (uint8_t i=0; i<NUM_ZONES; i++)
  {
      if (myDisplay.getZoneStatus(i))
      {   
      myDisplay.displayZoneText(0, (itoa(score, scoreArray, 10)), PA_RIGHT, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
      myDisplay.displayZoneText(1,(itoa(RecordScore, highScoreArray, 10)), PA_RIGHT, speed, pause, PA_NO_EFFECT,PA_NO_EFFECT);
      myDisplay.displayReset(i);
      }
  }
    }
  Start_game = digitalRead(Start);
  
  if (Start_game != startState){
  if(Start_game == HIGH)
    {
    gameOn = 1;
    display = 2;
  
    Serial.println("Starting");
    Serial.println(RecordScore);
  
  }
    delay(50);
  startState=Start_game;
  }
  if(gameOn == 1){
   game();
 } 
  }

void displayMessages()
  {   
  myDisplay.displayAnimate();
  if (myDisplay.getZoneStatus(2)){
  
  switch (display){
    case 0:
    myDisplay.displayZoneText(2, message[2], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    display++;
    break;

    case 1:
    myDisplay.displayZoneText(2, message[3], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    break;

    case 2:
    myDisplay.displayZoneText(2, message[4], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    display++;
    break;

    case 3:
    myDisplay.displayZoneText(2, message[5], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    break;

    case 4:
    myDisplay.displayZoneText(2,message[6], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    break;

    case 5:
    myDisplay.displayZoneText(2,message[7], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    break;

    case 6:
    myDisplay.displayZoneText(2,message[8], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    if(MaxBalls > 0)
    {
      display = 3;
    }
    if(MaxBalls == 0)
    {
      display = 7;
    }
    break;

    case 7:
    myDisplay.displayZoneText(2,message[9], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
     
    break;
    
    case 8:
    myDisplay.displayZoneText(2,message[10], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    break;

    case 9:
    myDisplay.displayZoneText(2,message[11], PA_CENTER, speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);

    default:
    myDisplay.displayZoneText(2, message[1], PA_CENTER,speed, pause, PA_NO_EFFECT, PA_NO_EFFECT);
    display ++;
    break;


  }
 
  }
  }

void game()
 { 
  while(gameOn==1){
    paw1.claw(); paw2.claw(); paw3.claw(); paw4.claw();
  dropDown1.targets(); dropDown1.reset(); 
  dropDown2.targets(); dropDown2.reset();
  dropDown3.targets(); dropDown3.reset();
  sensor.sensorRead();
  kickerL.kickerRead(); kickerR.kickerRead();
  bumperR.bumperRead(); bumperL.bumperRead();
  Reset_game = digitalRead(Reset);

   if (Reset_game==HIGH ) {
     ResetGame();
    }
                


  Stop_game = digitalRead(Stop); //lost ball
  if(Stop_game != stopState){
  if(Stop_game == HIGH){
    display = 6;
    MaxBalls --;
    Serial.println("Ball Lost");
    
  

    if(MaxBalls == 0){
      Serial.println(score);
      gameOn=2;
    display = 7;
    displayMessages();
   GameOver();
     
    }
    
  }
  delay(50);
  stopState=Stop_game;
  }
 
 return; 
 }

 }

void GameOver()
  {
  Serial.println("Game Over");
  pinBall = SD.open("high.txt",O_READ | O_WRITE | O_CREAT | O_TRUNC);
  if(score > RecordScore){
  display = 9;
  RecordScore = score;
  
  if (pinBall) {
    Serial.print("Writing to high.txt...");
    Serial.println(RecordScore);
    pinBall.print(RecordScore);

    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening high.txt");
  }
  }
  pinBall.close();
  gameOn=0;
  First_scan = 0;
  ResetGame();
 }
void ResetGame()
  {
  score = 0;
  MaxBalls = 5;
  display= -1;
  gameOn = 0;
  Serial.println("RESET GAME");
 }