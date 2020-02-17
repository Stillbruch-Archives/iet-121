#define P1 2
#define LED_GREEN 6
#define ENABLE_LED_GREEN digitalWrite(LED_GREEN, HIGH)
#define DISABLE_LED_GREEN digitalWrite(LED_GREEN, LOW)
#define P1Down (digitalRead(P1) == 0)

const unsigned long P1_COUNTER_INITIAL_VALUE = 0;
unsigned long p1Counter = P1_COUNTER_INITIAL_VALUE;
const unsigned long TICK_INTERVAL = 20;
const unsigned long DEFAULT_FLASH_INTERVAL = 1000;
const unsigned long DEFAULT_MONITORING_INTERVAL = 1000;

int phaseLed = 1;
int phaseP1 = 1;

unsigned long ledTime;
unsigned long monitoringTime;
unsigned long p1DownTimestamp;

void setup() {
    pinMode(P1, INPUT);
    pinMode(LED_GREEN, OUTPUT);
    Serial.begin(9600);
    ledTime = millis();
    monitoringTime = millis();
}

void loop() {
    serialMonitoring(DEFAULT_MONITORING_INTERVAL);

    if (P1Down) {
        switch (phaseP1) {
            case 1:
                p1DownTimestamp = millis();
                p1Counter = P1_COUNTER_INITIAL_VALUE;
                phaseP1 = 2;
                break;
            case 2:
                if (millis() - p1DownTimestamp > TICK_INTERVAL) {
                    p1DownTimestamp = millis();
                    p1Counter++;
                }
                break;
        }
    }
    else {
        phaseP1 = 1;
    }

    switch (phaseLed) {
        case 1:
            ENABLE_LED_GREEN;
            if (millis() - ledTime > getFlashInterval()) {
                ledTime = millis();
                phaseLed = 2;
            }
            break;
        case 2:
            DISABLE_LED_GREEN;
            if (millis() - ledTime > getFlashInterval()) {
                ledTime = millis();
                phaseLed = 1;
            }
            break;
    }
}

unsigned long getFlashInterval() {
    return DEFAULT_FLASH_INTERVAL / getTicks();
}

unsigned long getTicks() {
    return p1Counter/ 50 > 0 ? p1Counter / 50 : 1;
}

void serialMonitoring(unsigned long monitoringInterval){
    if (millis() - monitoringTime > monitoringInterval) {
        Serial.println(getTicks(), DEC);
        Serial.println(p1Counter, DEC);
        Serial.println(phaseP1, DEC);
        Serial.println("===");
        monitoringTime = millis();
    }
}