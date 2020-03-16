#include "station2d.h"
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int TEST_SPEED = 140;
const unsigned long TEST_INTERVAL = 2000;

int stateTimestamp;

enum VehicleState
{
    MovingForward,
    MovingBackward,
    RotatingLeft,
    RotatingRight,
    Stopped
} vehicleState;

const VehicleState INITIAL_STATE = MovingForward;

void setup()
{
    // hardware init
    pinMode(ENA, OUTPUT);
    pinMode(N1, OUTPUT);
    pinMode(N2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(N3, OUTPUT);
    pinMode(N4, OUTPUT);

    // software init
    Serial.begin(9600);

    // other init
    stateTimestamp = millis();
    vehicleState = INITIAL_STATE;
}

void loop()
{
    switch (vehicleState)
    {
    case MovingForward:
        printCurrentState();
        moveForward(TEST_SPEED);
        if (getTimeInState() > TEST_INTERVAL)
        {
            stopAllEngines();
            stateTimestamp = millis();
            vehicleState = MovingBackward;
        }
        break;
    case MovingBackward:
        printCurrentState();
        moveBackward(TEST_SPEED);
        if (getTimeInState() > TEST_INTERVAL)
        {
            stopAllEngines();
            stateTimestamp = millis();
            vehicleState = RotatingLeft;
        }
        break;
    case RotatingLeft:
        printCurrentState();
        rotateLeft(TEST_SPEED);
        if (getTimeInState() > TEST_INTERVAL)
        {
            stopAllEngines();
            stateTimestamp = millis();
            vehicleState = RotatingRight;
        }
        break;
    case RotatingRight:
        printCurrentState();
        rotateRight(TEST_SPEED);
        if (getTimeInState() > TEST_INTERVAL)
        {
            stopAllEngines();
            stateTimestamp = millis();
            vehicleState = Stopped;
        }
        break;
    case Stopped:
        printCurrentState();
        if (getTimeInState() > TEST_INTERVAL)
        {
            stateTimestamp = millis();
            vehicleState = INITIAL_STATE;
        }
        break;
    }
}

unsigned long getTimeInState()
{
    return millis() - stateTimestamp;
}

void printCurrentState()
{
    Serial.println(vehicleState, DEC);
}

void rotateLeft(int speed)
{
    engineLeftBackward(speed);
    engineRightForward(speed);
}

void rotateRight(int speed)
{
    engineLeftForward(speed);
    engineRightBackward(speed);
}

void moveForward(int speed)
{
    engineLeftForward(speed);
    engineRightForward(speed);
}

void moveBackward(int speed)
{
    engineLeftBackward(speed);
    engineRightBackward(speed);
}

void engineLeftForward(int speed)
{
    analogWrite(ENA, speed);
    digitalWrite(N1, HIGH);
    digitalWrite(N2, LOW);
}

void engineRightForward(int speed)
{
    analogWrite(ENB, speed);
    digitalWrite(N3, HIGH);
    digitalWrite(N4, LOW);
}

void engineLeftBackward(int speed)
{
    analogWrite(ENA, speed);
    digitalWrite(N1, LOW);
    digitalWrite(N2, HIGH);
}

void engineRightBackward(int speed)
{
    analogWrite(ENB, speed);
    digitalWrite(N3, LOW);
    digitalWrite(N4, HIGH);
}

void stopAllEngines()
{
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(N1, HIGH);
    digitalWrite(N2, HIGH);
    digitalWrite(N3, HIGH);
    digitalWrite(N4, HIGH);
}