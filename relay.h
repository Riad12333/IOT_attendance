#ifndef RELAY_H
#define RELAY_H

#include "config.h"

class DoorLock {
private:
    int relayPin;
    int openDuration;
    bool isOpen;
    
public:
    DoorLock(int pin = RELAY_PIN, int duration = DOOR_OPEN_DURATION) {
        relayPin = pin;
        openDuration = duration;
        isOpen = false;
        pinMode(relayPin, OUTPUT);
        digitalWrite(relayPin, LOW);
    }

    void open() {
        if (!isOpen) {
            Serial.println("Ouverture de la porte...");
            digitalWrite(relayPin, HIGH);
            isOpen = true;
            delay(openDuration);
            close();
        }
    }

    void close() {
        if (isOpen) {
            Serial.println("Fermeture de la porte...");
            digitalWrite(relayPin, LOW);
            isOpen = false;
        }
    }

    bool getStatus() {
        return isOpen;
    }
};

#endif
