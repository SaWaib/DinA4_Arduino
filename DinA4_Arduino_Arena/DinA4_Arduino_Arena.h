#ifndef DINA4_ARDUINO_ARENA_H
#define DINA4_ARDUINO_ARENA_H

#include <Arduino.h>
#include <Servo.h>

class DinA4_Arduino_Arena
{

public:
    DinA4_Arduino_Arena();
    
    void OpenClawFully();
    void OpenClawPartially();
    
    bool CloseClaw();
    bool checkForBallInClaw();
    
    void PickUp_White();
    void PickUp_Black();
    
    void Deliver_White();
    void Deliver_Black();
    
    void Close_Gate();
    void Servos_init();
    
    void sendCommand(int value);
    int getCommand();

private:
    int receivedInt;
    char ch;
    int commandvalue = 0;
    int interLED =13;


    Servo mainServo;
    Servo gripperLeftServo;
    Servo gripperRightServo;
    Servo gateServo;
};

#endif
