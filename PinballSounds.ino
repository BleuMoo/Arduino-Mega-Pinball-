/*
 This reads a wave file from an SD card and plays it using the I2S interface to
 a MAX98357 I2S Amp Breakout board.

 Circuit:
 * Arduino Zero, MKR Zero or MKR1000 board
 * SD breakout or shield connected
 * MAX98357:
   * GND connected GND
   * VIN connected 5V
   * LRC connected to pin 0 (Zero) or pin 3 (MKR1000, MKR Zero)
   * BCLK connected to pin 1 (Zero) or pin 2 (MKR1000, MKR Zero)
   * DIN connected to pin 9 (Zero) or pin A6 (MKR1000, MKR Zero)

 created 15 November 2016
 by Sandeep Mistry
 */

#include <SD.h>
#include <ArduinoSound.h>

// filename of wave file to play
const char *filename[8] =
{ "NyanCat2.WAV","friday.WAV","DumbDie.WAV","leroy.WAV","gungnam.WAV","fox.WAV","cat.WAV","knocks.WAV"};
const int chipSelect = SDCARD_SS_PIN;
const int dropInput = 4;
const int pawInput = 7;
const int sensorInput = 8;
const int kickerInput = 9;
const int bumperInput = 10;
const int ballLossInput = 6;
const int startInput = 5;
int dropSound = 0;
int dropSoundState = 0;
int pawSound = 0;
int pawSoundState = 0;
int sensorSound = 0;
int sensorSoundState =0;
int kickerSound = 0;
int kickerSoundState = 0;
int bumperSound = 0;
int bumperSoundState = 0;
int ballLossSound = 0;
int ballLossSoundState = 0;
int startSound = 0;
int startSoundState = 0;
long current = 20;

// variable representing the Wave File
SDWaveFile mainLoop;
SDWaveFile friday;
SDWaveFile dumbways;
SDWaveFile leroy;
SDWaveFile gungnam;
SDWaveFile fox;
SDWaveFile cat;
SDWaveFile knocks;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  pinMode(dropInput, INPUT); 
  pinMode(pawInput, INPUT);
  pinMode(sensorInput, INPUT);
  pinMode(kickerInput, INPUT);
  pinMode(bumperInput, INPUT);
  pinMode(ballLossInput, INPUT);
  pinMode(startInput, INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // setup the SD card, depending on your shield of breakout board
  // you may need to pass a pin number in begin for SS
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // create a SDWaveFile
  mainLoop = SDWaveFile(filename[0]);
  friday = SDWaveFile(filename[1]);
  dumbways = SDWaveFile(filename[2]);
  leroy = SDWaveFile(filename[3]);
  gungnam = SDWaveFile(filename[4]);
  fox = SDWaveFile(filename[5]);
  cat = SDWaveFile(filename[6]);
  knocks = SDWaveFile(filename[7]);
  // check if the WaveFile is valid
  if (!cat) {
    Serial.println("wave file is invalid!");
    while (1); // do nothing
  }

  // print out some info. about the wave file
  Serial.print("Bits per sample = ");
  Serial.println(cat.bitsPerSample());

  long channels = cat.channels();
  Serial.print("Channels = ");
  Serial.println(channels);

  long sampleRate = cat.sampleRate();
  Serial.print("Sample rate = ");
  Serial.print(sampleRate);
  Serial.println(" Hz");

  long duration = cat.duration();
  Serial.print("Duration = ");
  Serial.print(duration);
  Serial.println(" seconds");

  // adjust the playback volume
  AudioOutI2S.volume(50);

  // check if the I2S output can play the wave file
  if (!AudioOutI2S.canPlay(cat)) {
    Serial.println("unable to play wave file using I2S!");
    while (1); // do nothing
  }

  // start playback
  Serial.println("starting playback");
  AudioOutI2S.loop(mainLoop);
}

void loop() {
  //current = mainLoop.currentTime();
  dropSound = digitalRead(dropInput);
  pawSound = digitalRead(pawInput);
  sensorSound= digitalRead(sensorInput);
 kickerSound = digitalRead(kickerInput); 
 bumperSound = digitalRead(bumperInput);
 ballLossSound = digitalRead(ballLossInput); 
 startSound = digitalRead(startInput); 

  if (dropSound != dropSoundState)
  {
    if(dropSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(gungnam);
      Serial.println("drop");

    }
    delay(50);
    dropSoundState=dropSound;
  }
    
    if (pawSound != pawSoundState)
  {
    if(pawSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(cat);
      Serial.println("Paw");

    }
    delay(50);
    pawSoundState=pawSound;
  }
    
    if (sensorSound != sensorSoundState)
  {
    if(sensorSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(friday);
      Serial.println("sensor");

    }
    delay(50);
    sensorSoundState=sensorSound;
  }
    if (kickerSound != kickerSoundState)
  {
    if(kickerSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(knocks);
      Serial.println("kicker");

    }
    delay(50);
    kickerSoundState=kickerSound;
  }
    if (bumperSound != bumperSoundState)
  {
    if(bumperSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(fox);
      Serial.println("bumper");

    }
    delay(50);
    bumperSoundState=bumperSound;
  }
    
    if (ballLossSound != ballLossSoundState)
  {
    if(ballLossSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(dumbways);
      Serial.println("ball loss");

    }
    delay(50);
    ballLossSoundState=ballLossSound;
  }      
      
  if (startSound != startSoundState)
  {
    if(startSound == HIGH)
    {
      AudioOutI2S.stop();
      delay(50);
      AudioOutI2S.play(leroy);
      Serial.println("start sound");

    }
    delay(50);
    startSoundState=startSound;
  }
  if (!AudioOutI2S.isPlaying())
        {
          AudioOutI2S.play(mainLoop);
         
          
        }

  
}