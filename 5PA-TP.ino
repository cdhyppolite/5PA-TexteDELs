//librairies
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> //marche sans
#include "SPIFFS.h"
#include <FastLED.h>

// réseau Wifi
const char* ssid = "reseau2";
const char* password = "123456789";
/**********************/
//const char* ssid = "cm-invites";
//const char* password = "sansfil3800";

//breadboard
const int PIN_DATA = 27;

// Autres
int effet = 5; //Éteindre par défault
const int temps = 10;

// Fast Leds
const int nbLeds = 25;
CRGB myLights[nbLeds];
int brightness = 50;
uint8_t hue = 0;

// création instance d'un serveur asynchrone sur le port 80
AsyncWebServer monServeur(80);

void setup() {

  //config. pin en sortie
  FastLED.addLeds<NEOPIXEL, PIN_DATA>(myLights, nbLeds);
  FastLED.setBrightness(brightness);
  FastLED.clear(false);
  Serial.begin(115200);

  // si SPIFFS ne démarre pas, alerter
  if (!SPIFFS.begin(true)) {
    Serial.println("erreur SPIFFs");
    return;
  }

  // connection Wi-Fi (=boucle d'attente)
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Attendez...");
  }

  // afficher adresse IP une fois connecté
  Serial.println(WiFi.localIP());

  // écoute requète page web
  monServeur.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète fichier style.css (reçue par le lien de style.css dans html)
  monServeur.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  /** ------------------------  LES EFFETS ----------------------------*/

  // écoute requète effet1 (envoyé par bouton html)
  monServeur.on("/effet1", HTTP_GET, [](AsyncWebServerRequest * request) {
    effet = 1;
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet2 (envoyé par bouton html)
  monServeur.on("/effet2", HTTP_GET, [](AsyncWebServerRequest * request) {
    effet = 2;
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet3 (envoyé par bouton html)
  monServeur.on("/effet3", HTTP_GET, [](AsyncWebServerRequest * request) {
    effet = 3;
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet4 (envoyé par bouton html)
  monServeur.on("/effet4", HTTP_GET, [](AsyncWebServerRequest * request) {
    effet = 4;
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet5 (envoyé par bouton html)
  monServeur.on("/effet5", HTTP_GET, [](AsyncWebServerRequest * request) {
    effet = 5;
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // demarrer serveur
  monServeur.begin();
}
void loop() {
  FastLED.clear(effet==2);

  /*switch (effet) {
    case 1 :
      effet1();
      break;
    case 2 :
      effet2();
      break;
    case 3 :
      effet3();
      break;
    case 4 :
      effet4();
      break;
    case 5 :
      effet5();
      break;
  }*/

}

// Couleur Fix
void effet1() {

}
// Moving dots
void effet2() {

}
//Tricolore
void effet3() {

}

// ARC-EN-CIEL
void effet4() {

}

// Éteindre
void effet5() {

}
