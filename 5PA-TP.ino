/*----------------- VARAIBLES POUR LEDS MATRIX -----------------*/
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 22
char* texteLED = "Carl-David";

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(25, 10, DATA_PIN,
NEO_MATRIX_BOTTOM    + NEO_MATRIX_LEFT +
NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(204, 0, 204), matrix.Color(204, 204, 0), matrix.Color(0, 255, 255),
  matrix.Color(255, 10, 127), matrix.Color(127, 0, 255), matrix.Color(0, 255, 0),
  matrix.Color(255, 99, 255)
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
const int temps = 10;

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

  /** ------------------------  LES EFFETS ----------------------------*/

  // écoute requète effet1 (envoyé par bouton html)
  monServeur.on("/effet1", HTTP_GET, [](AsyncWebServerRequest * request) {
    printEffet("BonJour");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet2 (envoyé par bouton html)
  monServeur.on("/effet2", HTTP_GET, [](AsyncWebServerRequest * request) {
    printEffet("mario");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet3 (envoyé par bouton html)
  monServeur.on("/effet3", HTTP_GET, [](AsyncWebServerRequest * request) {
    printEffet("Luigi");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet4 (envoyé par bouton html)
  monServeur.on("/effet4", HTTP_GET, [](AsyncWebServerRequest * request) {
    printEffet("OMG");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // écoute requète effet5 (envoyé par bouton html)
  monServeur.on("/effet5", HTTP_GET, [](AsyncWebServerRequest * request) {
    printEffet("QwerTY");
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
  delay(33);
}
void printEffet(char* newText) {
  texteLED = newText;
  Serial.println(texteLED);
}
