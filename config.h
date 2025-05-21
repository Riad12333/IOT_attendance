#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "IdoomFibre_ATANV2R4f"
#define WIFI_PASSWORD "nFp5DCKF"

// Server Configuration (à adapter selon tes serveurs)
#define SERVER1_URL "http://192.168.100.21:3000/api/access"         // Serveur des étudiants
#define SERVER2_URL "http://192.168.100.21:3002/api/professor-access"  // Serveur des professeurs
#define SERVER3_URL "http://192.168.100.21:3006/api/fingerprint-template"  // Serveur des empreintes
#define ROOM_ID "3"  // Identifiant numérique de la salle (doit correspondre à l'ID dans la base de données)

// Pin Configuration pour ESP8266 D1 R3
#define FINGERPRINT_RX D5   // GPIO14
#define FINGERPRINT_TX D6     // GPIO12
#define RELAY_PIN     D1      // GPIO5

// Configuration écran OLED
#define OLED_SDA D3          // GPIO4
#define OLED_SCL D4         // GPIO0
#define OLED_RESET -1        // Pas de pin de reset
#define OLED_ADDRESS 0x3C    // Adresse I2C de l'écran

// Mode Configuration
#define MODE_STUDENT 1
#define MODE_PROFESSOR 2

// Autres configurations
#define DOOR_OPEN_DURATION 3000  // Durée d'ouverture de la porte en ms
#define MAX_PROFESSOR_ID 2     // Les IDs en dessous sont des professeurs

#endif
