#include <TermopilasConfig.h>
#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <UNIT_PN532.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Miscelaneo
const String moduleID = MODULE_ID;

// Relays
const int relay1Pin = 26;
const int relay2Pin = 27;

// Card Readers
char str[32] = "";
String StrUID;

// RF522
#define SS_PIN 5
#define RST_PIN 22  
MFRC522 mfrc522(SS_PIN, RST_PIN);
int readsuccess;
byte readcard[4];

//PN532
#define PN532_SCK  18
#define PN532_MOSI 23
#define PN532_SS   5
#define PN532_MISO 19
uint8_t DatoRecibido[4];
UNIT_PN532 nfc(PN532_SS);

// HTTP Request
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;
const String apiUrl = API_URL;
const String apiKey = API_KEY;

//Data
bool success;
int isEntrance;

// Wifi
const char* ssid = WIFI_SSID;
const char* password = WIFI_PW;
/*
const IPAddress local_IP(192,168,5,201);
const IPAddress gateway(192,168,4,1);
const IPAddress subnet(255,255,255,254);
const IPAddress primaryDNS(8,8,8,8);
const IPAddress secondaryDNS(8,8,4,4);*/

#define ON_Board_LED 2 

void setup() {
  Serial.begin(115200);

  wifiSetup();

  // Set the GPIO pins as outputs
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);

  /* Setup for the RC522 Module   
  setupRC522();
  */

  /* Setup for the PN532 Module */
  setupPN532();


  delay(500);

  Serial.println("");
  Serial.println("Configuración inicial completada");
  Serial.println("");
}

void loop() {
  readsuccess = getidPN532();

  if (readsuccess) {
    // Verify the Wifi Connection
    wifiCheck();
    
    // Conection to the API when Wifi is Connected
    apiCall();
  }
}