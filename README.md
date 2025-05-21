# Système IoT de Contrôle d'Accès et de Présence

Ce projet implémente un système de contrôle d'accès et de gestion de présence utilisant un ESP32, un capteur d'empreintes digitales AS608, et un relais pour contrôler une serrure électromagnétique.

## Composants Matériels
- ESP32
- Capteur d'empreintes digitales AS608
- Module relais
- Serrure électromagnétique
- Alimentation 12V pour la serrure
- Câbles de connexion
- Écran OLED SSD1306 0.96"

## Configuration
1. Ouvrez `src/config.h`
2. Modifiez les paramètres WiFi (SSID et mot de passe)
3. Ajustez les URLs des serveurs selon votre configuration

## Installation des Bibliothèques Arduino
Dans le gestionnaire de bibliothèques Arduino (Croquis > Inclure une bibliothèque > Gérer les bibliothèques), installez :
- Adafruit_Fingerprint
- ArduinoJson
- Adafruit GFX Library
- Adafruit SSD1306
- ESP8266WiFi (inclus avec le support ESP8266)
- ESP8266HTTPClient (inclus avec le support ESP8266)

Note : Assurez-vous d'avoir installé le support ESP8266 dans Arduino IDE :
1. Allez dans Fichier > Préférences
2. Dans "URL de gestionnaire de cartes supplémentaires", ajoutez : http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Allez dans Outils > Type de carte > Gestionnaire de cartes
4. Cherchez "ESP8266" et installez le support

## Branchements
- AS608 (Capteur d'empreintes)
  - TX → D5 (GPIO14) ESP8266
  - RX → D6 (GPIO12) ESP8266
  - VCC → 3.3V ESP8266
  - GND → GND ESP8266
- Relais
  - IN → D1 (GPIO5) ESP8266
  - VCC → 5V ESP8266
  - GND → GND ESP8266
- OLED SSD1306 0.96"
  - SDA → D2 (GPIO4) ESP8266
  - SCL → D3 (GPIO0) ESP8266
  - VCC → 3.3V ESP8266 (branché en parallèle avec le VCC du AS608)
  - GND → GND ESP8266
- Serrure électrique
  - Connectée aux bornes NO/COM du relais
  - Alimentée en 12V DC externe

Note : Le capteur d'empreintes AS608 et l'écran OLED sont tous deux alimentés par la même broche 3.3V en parallèle, car leur consommation de courant est faible.

## Utilisation
1. Téléversez le code sur l'ESP32
2. Ouvrez le moniteur série (115200 baud)
3. Le système est prêt à :
   - Vérifier les accès des professeurs
   - Enregistrer les présences des étudiants
   - Contrôler la serrure

## Fonctionnalités
- Lecture d'empreintes digitales
- Distinction professeurs/étudiants
- Contrôle d'accès pour les professeurs
- Enregistrement des présences pour les étudiants
- Communication avec les serveurs backend
- Contrôle de serrure électromagnétique

## Architecture
- `config.h` : Configuration du système
- `fingerprint.h` : Gestion du capteur d'empreintes
- `relay.h` : Contrôle du relais et de la serrure
- `main.ino` : Programme principal
