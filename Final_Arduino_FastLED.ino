//LIBRARY
#include <FastLED.h>

//CONSTANTS
#define led_pin A5    //Arduino pin where LEDs are plugged into
#define led_total 60  //Total number of LEDs in strip
#define half_led_total led_total/2
#define sound_pin A0  //Arduino pin for envelope connection on sound detector
#define trim_pin A1   //Arduino pin for trimpot
#define visual_button 5
#define num_visuals 1 //number of visuals - 1

//GLOBALS
CRGB leds[led_total]; //LED array

//amplitude measured from sound recorder ranges from 0 to 1023
unsigned int volume = 0; //unsigned int - to 1023
unsigned int trim_pot = 0; //unsigned int 0 to 1023
unsigned int visual = 0; //hold current visual


void setup() {
  Serial.begin(9600);
  //define button as a digital input
  pinMode(visual_button, INPUT);
  //write HIGH to button, enable pullup resistor (unpressed reads as HIGH/True/1)
  digitalWrite(visual_button, HIGH);
  //add leds to FastLED object
  FastLED.addLeds<WS2812, led_pin, GRB>(leds, led_total);
  //set brightness for LEDs
  FastLED.setBrightness(25);
}

void loop() {
  volume = analogRead(sound_pin);
  trim_pot = analogRead(trim_pin);
  //change visual if needed
  Change_Visual();
  //check what visual is selected and execute it
  Select_Visual();
  delay(50);
}

void Change_Visual() {
  if (!digitalRead(visual_button)) {

    visual++; //increment to next visual

    volume = 0; //reset volume for new visual

    //go back to first visual
    if (visual > num_visuals) visual = 0;
    //button kinda loud so don't record anything for a moment
    delay(300);
  }
}

void Select_Visual(){
  switch(visual){
    case 0: return Solid_Animation();
    case 1: return Middle_Out();
    default: return Solid_Animation();}
  }

void Solid_Animation(){
  //leds[0] = CHSV(getHueVal, 255, getBrightVal(trim_pot));
  fill_solid(leds, led_total, CHSV(getHueVal(volume), 255, getBrightVal(trim_pot)));
  FastLED.show();
  }

void Middle_Out(){
  leds[(half_led_total) - 1] = CHSV(getHueVal(volume), 255, getBrightVal(trim_pot));
  leds[half_led_total] = CHSV(getHueVal(volume), 255, getBrightVal(trim_pot));
  for(unsigned int i = 0; i <= ((half_led_total)-2); i++){
    leds[i] = leds[i + 1];
    leds[led_total - 1 - i] = leds[led_total - i - 2];
    }
  FastLED.show();
  delay(25);
  }

//map the amplitude to a hue value
unsigned int getHueVal(unsigned int i){
  return map(i, 0, 1023, 0, 255);
  }

//map the trimpot to the V value in HSV
unsigned int getBrightVal(unsigned int i){
  return map(i, 0, 1023, 0, 255);
  }
