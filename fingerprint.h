#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "config.h"

class FingerprintSensor {
private:
    SoftwareSerial* mySerial;
    Adafruit_Fingerprint* finger;
    bool initialized;
    
public:
    FingerprintSensor() : initialized(false) {
        mySerial = new SoftwareSerial(FINGERPRINT_RX, FINGERPRINT_TX);
        finger = new Adafruit_Fingerprint(mySerial);
        
    }

  bool begin() {
        if (!initialized) {
            initialized = true;
        }

        mySerial->begin(9600);
        if (!finger->verifyPassword()) {
            Serial.println("Erreur capteur d'empreintes!");
            return false;
        }
        Serial.println("Capteur d'empreintes initialisé avec succès!");
        return true;
    }

    int getFingerprintID() {
        uint8_t p = finger->getImage();
        if (p == FINGERPRINT_NOFINGER) return -1; // Aucun doigt
        if (p != FINGERPRINT_OK) return -3; // Erreur autre

        p = finger->image2Tz();
        if (p != FINGERPRINT_OK) return -3;

        p = finger->fingerSearch();
        if (p == FINGERPRINT_NOTFOUND) return -2; // Doigt non reconnu
        if (p != FINGERPRINT_OK) return -3;

        return finger->fingerID;
    }

    // Fonction pour enregistrer une nouvelle empreinte
    bool enrollFingerprint(uint16_t id) {
        int p = -1;
        Serial.println("Attente d'une empreinte valide à enregistrer...");
        
        while (p != FINGERPRINT_OK) {
            p = finger->getImage();
            switch (p) {
                case FINGERPRINT_OK:
                    Serial.println("Image prise");
                    break;
                case FINGERPRINT_NOFINGER:
                    Serial.print(".");
                    delay(100);
                    break;
                default:
                    Serial.println("Erreur inconnue");
                    return false;
            }
        }

        p = finger->image2Tz(1);
        if (p != FINGERPRINT_OK) {
            Serial.println("Erreur conversion");
            return false;
        }

        Serial.println("Retirez le doigt");
        delay(2000);
        p = 0;
        while (p != FINGERPRINT_NOFINGER) {
            p = finger->getImage();
        }

        p = -1;
        Serial.println("Placez le même doigt à nouveau");
        while (p != FINGERPRINT_OK) {
            p = finger->getImage();
            switch (p) {
                case FINGERPRINT_OK:
                    Serial.println("Image prise");
                    break;
                case FINGERPRINT_NOFINGER:
                    Serial.print(".");
                    delay(100);
                    break;
                default:
                    Serial.println("Erreur inconnue");
                    return false;
            }
        }

        p = finger->image2Tz(2);
        if (p != FINGERPRINT_OK) {
            Serial.println("Erreur conversion");
            return false;
        }

        p = finger->createModel();
        if (p != FINGERPRINT_OK) {
            Serial.println("Erreur création modèle");
            return false;
        }

        p = finger->storeModel(id);
        if (p != FINGERPRINT_OK) {
            Serial.println("Erreur stockage");
            return false;
        }

        Serial.println("Empreinte enregistrée avec succès!");
        return true;
    }

    bool isIdUsed(uint16_t id) {
        return finger->loadModel(id) == FINGERPRINT_OK;
    }
};

#endif
