#define P1 2
#define LED_1 6
#define LED_2 7
#define Led1On digitalWrite(LED_1, HIGH)
#define Led1Off digitalWrite(LED_1, LOW)
#define Led2On digitalWrite(LED_2, HIGH)
#define Led2Off digitalWrite(LED_2, LOW)

const unsigned long DEFAULT_LED_1_INTERVAL = 1000;
const unsigned long DEFAULT_LED_2_INTERVAL = 100;

int phaseLedGreen = 1;
int phaseLedRed = 1;
int phaseP1 = 1;

unsigned long ledGreenTimestamp;
unsigned long ledRedTimestamp;

void setup() {
    pinMode(P1, INPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    ledGreenTimestamp = millis();
    ledRedTimestamp = millis();
}

void loop() {
    if (!pIsDown(P1)) {
        Led1Off;
        Led2Off;
    }
    else {
        switch (phaseLedGreen) {
            case 1:
                Led1On;
                if (millis() - ledGreenTimestamp > DEFAULT_LED_1_INTERVAL) {
                    ledGreenTimestamp = millis();
                    phaseLedGreen = 2;
                }
                break;
            case 2:
                Led1Off;
                if (millis() - ledGreenTimestamp > DEFAULT_LED_1_INTERVAL) {
                    ledGreenTimestamp = millis();
                    phaseLedGreen = 1;
                }
                break;
        }

        switch (phaseLedRed) {
            case 1:
                Led2On;
                if (millis() - ledRedTimestamp > DEFAULT_LED_2_INTERVAL) {
                    ledRedTimestamp = millis();
                    phaseLedRed = 2;
                }
                break;
            case 2:
                Led2Off;
                if (millis() - ledRedTimestamp > DEFAULT_LED_2_INTERVAL) {
                    ledRedTimestamp = millis();
                    phaseLedRed = 1;
                }
                break;
        }
    }
}

bool pIsDown(uint8_t pin) {
    return digitalRead(pin) == 0;
}