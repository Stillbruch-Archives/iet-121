#define P1 2
#define P2 3
#define LED_GREEN 6
#define LED_RED 7
#define ENABLE_LED_GREEN digitalWrite(LED_GREEN, HIGH)
#define DISABLE_LED_GREEN digitalWrite(LED_GREEN, LOW)
#define ENABLE_LED_RED digitalWrite(LED_RED, HIGH)
#define DISABLE_LED_RED digitalWrite(LED_RED, LOW)

const unsigned long P1_COUNTER_INITIAL_VALUE = 0;
const unsigned long P2_COUNTER_INITIAL_VALUE = 0;
unsigned long p1Counter = P1_COUNTER_INITIAL_VALUE;
unsigned long p2Counter = P2_COUNTER_INITIAL_VALUE;
const unsigned long TICK_INTERVAL = 20;
const unsigned long DEFAULT_GREEN_INTERVAL = 750;
const unsigned long DEFAULT_RED_INTERVAL = 400;
const unsigned long DEFAULT_MONITORING_INTERVAL = 1000;

int phaseLedGreen = 1;
int phaseLedRed = 1;
int phaseP1 = 1;

unsigned long ledGreenTimestamp;
unsigned long ledRedTimestamp;
unsigned long monitoringTimestamp;
unsigned long p1DownTimestamp;

void setup() {
    pinMode(P1, INPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    Serial.begin(9600);
    ledGreenTimestamp = millis();
    ledRedTimestamp = millis();
    monitoringTimestamp = millis();
}

void loop() {

    if (pIsDown(P1)) {
        switch (phaseP1) {
            case 1:
                ENABLE_LED_GREEN;
                ENABLE_LED_RED;
                if (millis() - ledGreenTimestamp > DEFAULT_GREEN_INTERVAL) {
                    ledGreenTimestamp = millis();
                    phaseP1 = 2;
                }
                break;
            case 2:
                DISABLE_LED_GREEN;
                DISABLE_LED_RED;
                if (millis() - ledGreenTimestamp > DEFAULT_GREEN_INTERVAL) {
                    ledGreenTimestamp = millis();
                    phaseP1 = 1;
                }
                break;
        }
    }
    else {
        switch (phaseLedGreen) {
            case 1:
                ENABLE_LED_GREEN;
                if (millis() - ledGreenTimestamp > DEFAULT_GREEN_INTERVAL) {
                    ledGreenTimestamp = millis();
                    phaseLedGreen = 2;
                }
                break;
            case 2:
                DISABLE_LED_GREEN;
                if (millis() - ledGreenTimestamp > DEFAULT_GREEN_INTERVAL) {
                    ledGreenTimestamp = millis();
                    phaseLedGreen = 1;
                }
                break;
        }

        switch (phaseLedRed) {
            case 1:
                ENABLE_LED_RED;
                if (millis() - ledRedTimestamp > DEFAULT_RED_INTERVAL) {
                    ledRedTimestamp = millis();
                    phaseLedRed = 2;
                }
                break;
            case 2:
                DISABLE_LED_RED;
                if (millis() - ledRedTimestamp > DEFAULT_RED_INTERVAL) {
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