/*----------------- VARAIBLES POUR LEDS MATRIX -----------------*/
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 22
char* texteLED = "Carl-David";

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(25, 10, PIN,
 NEO_MATRIX_BOTTOM    + NEO_MATRIX_LEFT +
 NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
 NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(138, 44, 226)
};
/*----------------- FIN VARAIBLES LEDS MATRIX -----------------*/

/*----------------- VARAIBLES POUR CONNEXION WI-FI -----------------*/
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> //marche sans
#include "SPIFFS.h"

// réseau Wifi
const char* ssid = "reseau2";
const char* password = "123456789";

// création instance d'un serveur asynchrone sur le port 80
AsyncWebServer monServeur(80);

/*----------------- FIN VARAIBLES CONNEXION WI-FI -----------------*/

// Autres
int effet = 5; //Éteindre par défault
const int temps = 40;

void setup() {
  // Matrix
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);

  // Wifi
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

  /** ------------------------  LES COURS ----------------------------*/

// Session 1
  monServeur.on("/1J1", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Animation et interactivite en jeu");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/1M1", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Creation video");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/1M2", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Conception graphique et imagerie matricielle");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/1W1", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Mise en page Web");
    request->send(SPIFFS, "/index.html", String(), false);
  });

// Session 2
  monServeur.on("/2J2", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Creation de jeu 2D");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/2M3", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Effets speciaux et animation");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/2M4", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Conception graphique et imagerie vectorielle");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/2W2", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Animation et interactivite Web");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // demarrer serveur
  monServeur.begin();
}

int x = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);    //Turn off all the LEDs
  matrix.setCursor(x, 0);
  matrix.print(F(texteLED));

  if( --x < -110 ) {
    x = matrix.width();

    if(++pass >= 8) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(temps);
}
void changerText(char* newText) {
  texteLED = newText;
  Serial.println(texteLED);
}
