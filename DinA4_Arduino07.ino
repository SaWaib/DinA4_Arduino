#include "DinA4_Arduino_Arena.h"
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

DinA4_Arduino_Arena arena;
Servo myservo;
Adafruit_NeoPixel strip(13, 3, NEO_GRB + NEO_KHZ800);

int pi_message;
int sensorValue;
int switch_status;
int reflection_value;

const int REFLECTIVE_PIN = A7;


void setup() {
  // put your setup code here, to run once:

  strip.begin();             // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();              // Turn OFF all pixels ASAP
  strip.setBrightness(255);  // put your setup code here, to run once:
  colorWipe(strip.Color(255, 255, 255), 0);
  strip.show();

  arena.Servos_init();
  Serial.begin(19200);

  Serial.println("Beginning Programm");
}

void loop() {

  //sensorValue = analogRead(A7);
  //Serial.println(sensorValue);
  //checkForReflection();

  //arena.Servos_init();
  //delay(3000);
  //arena.OpenClawFully();
  //delay(3000);


  //arena.sendCommand(5);
  //delay(1000);

  pi_message = arena.getCommand();
  //if (message != -1){
  //Serial.println(message);}
  if (pi_message == 1) {
    arena.OpenClawFully();
  }

  else if (pi_message == 2) {
    if (arena.CloseClaw() == true) {
      arena.sendCommand(2);
    }

    else {
      arena.sendCommand(3);
    }


  } else if (pi_message == 3) {
    arena.PickUp_White();
  } else if (pi_message == 4) {
    arena.PickUp_Black();
  }


  else if (pi_message == 5) {
    arena.Deliver_Black();
  } else if (pi_message == 6) {
    arena.Deliver_White();
  }




  /*arena.OpenClawFully();
  delay(2000);
  arena.CloseClaw();
  delay(2000);
  arena.PickUp_White();
  delay(2000);*/

  //Serial.print("message:");
  //Serial.println(message);void Send_Command();
  //myservo.write(255);
  //arena.LowerClaw();
  //delay(2000);
  //myservo.write(50);
  //arena.PickUp_Black();
  //delay(2000);

  /*if (Serial.available() > 0) {
    int received = Serial.parseInt(); // Reads an int from serial
    Serial.println(received);         // Echo it back
    }*/
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}

bool checkForReflection() {
  if (analogRead(REFLECTIVE_PIN) <= 250) {
    arena.sendCommand(1);
    return true;

  } else {
    return false;
  }
}
