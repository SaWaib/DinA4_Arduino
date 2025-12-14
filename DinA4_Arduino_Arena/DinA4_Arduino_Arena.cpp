#include "DinA4_Arduino_Arena.h"
#include "Servo.h"
#include <Arduino.h>

int gripperLeftFullyOpenPos=80;
int gripperLeftPartiallyOpenPos = 145;//bigger number == tighter grip
int gripperLeftClosedPos=255;

int gripperRightFullyOpenPos=108;
int gripperRightPartiallyOpenPos=42;//smaller number == tighter grip
int gripperRightClosedPos=0;

int mainServoUpperPos=50;
int mainServoLowerPos=255;

int message;

DinA4_Arduino_Arena::DinA4_Arduino_Arena()
{
    Serial.begin(19200);
    pinMode(interLED, OUTPUT);
}


int DinA4_Arduino_Arena::getCommand() {
  static String inputBuffer = "";
  static bool receiving = false;

  while (Serial.available()) {
    ch = Serial.read();

    if (ch == '<') {
      inputBuffer = "";
      receiving = true;
    }
    else if (ch == '>' && receiving) {
      receiving = false;
      receivedInt = inputBuffer.toInt();  // Convert to int
      inputBuffer = "";                  // Clear buffer
      return receivedInt;                     // ✅ Return the integer
    }
    else if (receiving) {
      if (isDigit(ch)) {
        inputBuffer += ch;
      }
    }
  }

  return -1;  // ❌ Return -1 if no complete message is received yet
}

void DinA4_Arduino_Arena::sendCommand(int value) {
  Serial.write('<');     // start marker
  Serial.print(value);   // integer payload
  Serial.write('>');     // end marker
  Serial.println();      // optional: newline (safe for Pi)
}

void DinA4_Arduino_Arena::Servos_init()
{
    
    mainServo.attach(A0);
    gripperLeftServo.attach(A2);
    gripperRightServo.attach(A3);
    gateServo.attach(A1);
    
    mainServo.write(mainServoUpperPos);         
    gripperLeftServo.write(gripperLeftClosedPos);  
    gripperRightServo.write(gripperRightClosedPos);
    gateServo.write(90); // Mittelposition
}

void DinA4_Arduino_Arena::OpenClawFully()
{
    mainServo.write(mainServoLowerPos);         // Platzhalter für Untenposition
    gripperLeftServo.write(gripperLeftFullyOpenPos);  // Platzhalter für Aussenposition
    gripperRightServo.write(gripperRightFullyOpenPos); // Platzhalter für Aussenposition
}

void DinA4_Arduino_Arena::OpenClawPartially()
{
    mainServo.write(mainServoLowerPos);         // Platzhalter für Untenposition
    gripperLeftServo.write(gripperLeftPartiallyOpenPos);  // Platzhalter für Aussenposition
    gripperRightServo.write(gripperRightPartiallyOpenPos); // Platzhalter für Aussenposition
}

bool DinA4_Arduino_Arena::CloseClaw()
{
    int leftPos  = gripperLeftFullyOpenPos;
    int rightPos = gripperRightFullyOpenPos;
    while (leftPos != gripperLeftClosedPos || rightPos != gripperRightClosedPos) {
    
      if (checkForBallInClaw()==true){
      return true;
      }
      // Left gripper closes by increasing (80 → 190)
      if (leftPos < gripperLeftClosedPos) {
        leftPos++;
        gripperLeftServo.write(leftPos);
      }

      // Right gripper closes by decreasing (108 → 8)
      if (rightPos > gripperRightClosedPos) {
        rightPos--;
        gripperRightServo.write(rightPos);
      }

      delay(15);  // slower = higher number, faster = lower number
    }
    return false;
}

bool DinA4_Arduino_Arena::checkForBallInClaw(){
  message = getCommand();
  if (message==5){
    return true;
  }
  else{
    return false;
  }
  }

void DinA4_Arduino_Arena::PickUp_White()
{
  
        gripperLeftServo.write(gripperLeftClosedPos);  // Platzhalter für Greifposition
        gripperRightServo.write(gripperRightClosedPos); // Platzhalter für Greifposition
        delay(200);
        mainServo.write(mainServoUpperPos); // Platzhalter für Obenposition
        delay(700);
        gripperRightServo.write(gripperLeftFullyOpenPos); // Platzhalter für Aussenposition
        
    
}

void DinA4_Arduino_Arena::PickUp_Black()
{
    
        gripperLeftServo.write(gripperLeftClosedPos);  // Platzhalter für Greifposition
        gripperRightServo.write(gripperRightClosedPos); // Platzhalter für Greifposition
        delay(200);
        mainServo.write(mainServoUpperPos); // Platzhalter für Obenposition
        delay(700);
        gripperLeftServo.write(gripperRightFullyOpenPos); // Platzhalter für Aussenposition
        
    
}

void DinA4_Arduino_Arena::Deliver_White()
{
    gateServo.write(0); // oder 180, je nach Bau
    /*Serial.write("0");
    if (getCommand() == 0)
    {
        delay(2000);         // Pi schüttet Ball aus
        gateServo.write(90); // Mittelposition
        delay(500);
    }*/
    delay(5000);
    Close_Gate();
}

void DinA4_Arduino_Arena::Deliver_Black()
{
    gateServo.write(180); // oder 0, je nach Bau
    /*delay(200);
    Serial.write("0");
    if (getCommand() == 0)
    {
        delay(2000);         // Pi schüttet Ball aus
        gateServo.write(90); // Mittelposition
        delay(500);
    }*/
    delay(5000);
    Close_Gate();
   
}

void DinA4_Arduino_Arena::Close_Gate()
{
gateServo.write(90);
}

