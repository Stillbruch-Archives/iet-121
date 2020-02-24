#define SPKR 1
#define P1 2
#define P2 3
#define LED_GREEN 5
#define LED_YELLOW 6
#define LED_RED 7
#define ENABLE_LED_GREEN digitalWrite(LED_GREEN, HIGH)
#define DISABLE_LED_GREEN digitalWrite(LED_GREEN, LOW)
#define ENABLE_LED_YELLOW digitalWrite(LED_YELLOW, HIGH)
#define DISABLE_LED_YELLOW digitalWrite(LED_YELLOW, LOW)
#define ENABLE_LED_RED digitalWrite(LED_RED, HIGH)
#define DISABLE_LED_RED digitalWrite(LED_RED, LOW)

const unsigned long DEFAULT_PHASE_1_INTERVAL = 1000;
const unsigned long DEFAULT_PHASE_2_INTERVAL = 2000;
const unsigned long DEFAULT_MONITORING_INTERVAL = 1000;
const long DEFAULT_RANDOM_LOWER = 500;
const long DEFAULT_RANDOM_UPPER = 5000;

int phaseGame = 1;

unsigned long phaseGameTimestamp;
long timeToGreen;
unsigned long monitoringTimestamp;

void setup() {
    pinMode(P1, INPUT);
    pinMode(SPKR, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    // Serial.begin(9600);
    phaseGameTimestamp = millis();
    monitoringTimestamp = millis();
    randomSeed(analogRead(0));
    timeToGreen = random(DEFAULT_RANDOM_LOWER, DEFAULT_RANDOM_UPPER);
    // Serial.println(timeToGreen, DEC);
}

void loop() {
    switch (phaseGame) {
        case 1:
            ENABLE_LED_RED;
            if (millis() - phaseGameTimestamp > DEFAULT_PHASE_1_INTERVAL) {
                phaseGameTimestamp = millis();
                phaseGame = 2;
            }
            break;
        case 2:
            ENABLE_LED_YELLOW;
            if (millis() - phaseGameTimestamp > timeToGreen) {
                phaseGameTimestamp = millis();
                phaseGame = 3;
            }
            break;
        case 3:
            DISABLE_LED_RED;
            DISABLE_LED_YELLOW;
            ENABLE_LED_GREEN;
            // phaseGame = 1;
            break;
    }
}

bool pIsDown(uint8_t pin) {
    return digitalRead(pin) == 0;
}