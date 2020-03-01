#include "mfs.h"

const unsigned long DEFAULT_RED_STATE_DURATION = 1000;
const unsigned long MIN_ORANGE_STATE_DURATION = 500;
const unsigned long MAX_ORANGE_STATE_DURATION = 5000;

enum GameState
{
    Red,
    Orange,
    Green,
    Over
} gameState;

unsigned long timeInState;
unsigned long redStateDuration;
unsigned long orangeStateDuration;

void setup()
{
    // software init
    randomSeed(analogRead(0));

    // hardware init
    pinMode(P1, INPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    Serial.begin(9600);

    // game state init
    resetGame();
}

void loop()
{
    if(isResetButtonPressed()) {
        resetGame();
    }

    if (!isGameRunning())
    {
        return;
    }

    if (isReactionMeasurementButtonPressed())
    {
        if (gameState == GameState::Green)
        {
            outputReactionTime();
        }
        else
        {
            outputError();
        }

        setGameStateAndResetTimeInState(GameState::Over);
    }

    switch (gameState)
    {
    case GameState::Red:
        setLedsToRed();

        if (getTimeInState() > redStateDuration)
        {
            setGameStateAndResetTimeInState(GameState::Orange);
        }

        break;
    case GameState::Orange:
        setLedsToOrange();

        if (getTimeInState() > orangeStateDuration)
        {
            setGameStateAndResetTimeInState(GameState::Green);
        }

        break;
    case GameState::Green:
        setLedsToGreen();

        break;
    }
}

void resetGame() {
    setGameStateAndResetTimeInState(GameState::Red);
    redStateDuration = DEFAULT_RED_STATE_DURATION;
    orangeStateDuration = random(MIN_ORANGE_STATE_DURATION, MAX_ORANGE_STATE_DURATION);
    Serial.println("Game has started.");
}

void setLedsToRed()
{
    Led1On;
    Led2Off;
    Led3Off;
}

void setLedsToOrange()
{
    Led1On;
    Led2On;
    Led3Off;
}

void setLedsToGreen()
{
    Led1Off;
    Led2Off;
    Led3On;
}

void setGameStateAndResetTimeInState(GameState newGameState)
{
    gameState = newGameState;
    resetTimeInState();
}

unsigned long getTimeInState()
{
    return millis() - timeInState;
}

void resetTimeInState()
{
    timeInState = millis();
}

void outputError()
{
    Serial.println(gameState, DEC);
}

void outputReactionTime()
{
    Serial.println(getTimeInState(), DEC);
}

bool isReactionMeasurementButtonPressed()
{
    return pIsDown(P1);
}

bool isResetButtonPressed()
{
    return pIsDown(P2);
}

bool isGameRunning()
{
    return gameState != GameState::Over;
}

bool pIsDown(uint8_t pin)
{
    return digitalRead(pin) == 0;
}