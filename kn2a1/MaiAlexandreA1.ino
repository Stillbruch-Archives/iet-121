#define P1 2
#define P2 3
#define LED_1 4
#define Led1On digitalWrite(LED_1, HIGH)
#define Led1Off digitalWrite(LED_1, LOW)

void setup()
{
    pinMode(P1, INPUT);
    pinMode(P2, INPUT);
    pinMode(LED_1, OUTPUT);
}

void loop()
{
    if (pIsDown(P1) && pIsDown(P2))
    {
        Led1On;
    }
    else {
        Led1Off;
    }
}

bool pIsDown(uint8_t pin)
{
    return digitalRead(pin) == 0;
}