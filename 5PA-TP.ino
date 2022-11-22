/* 
  Example "Protest scroller" for 8x32 WS2812 "NeoPixel Display Assumes you are running a standard Arduino ATMega328 compatible board
  https://youtu.be/QIijJGk0uCk
*/

/*----------------- VARAIBLES POUR LEDS MATRIX -----------------*/
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define DATA_PIN 22
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

// Matrix setup params
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(25, 10, DATA_PIN,
NEO_MATRIX_BOTTOM    + NEO_MATRIX_LEFT +
NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
NEO_GRB            + NEO_KHZ800);


char* Text[]= {"CARL-DAVID HYPPOLITE :)"};
const uint16_t colors[] = {
  matrix.Color(255, 51, 153)};
int brightness = 80;
// End Edit

int numMode = arr_len(Text)-1;
int numColor = arr_len(colors)-1;
int pixelPerChar = 4;
int maxDisplacement;
int mode = 0;

/*----------------- FIN VARAIBLES LEDS MATRIX -----------------*/

/*----------------- VARAIBLES POUR CONNEXION WI-FI -----------------*/
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> //marche sans
#include "SPIFFS.h"

// création instance d'un serveur asynchrone sur le port 80
AsyncWebServer monServeur(80);

// réseau Wifi
const char* ssid = "cm-invites";
const char* password = "sansfil3800";
/*----------------- FIN VARAIBLES CONNEXION WI-FI -----------------*/

void setup() {
  // ----- Setup led matrix
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(brightness);
  matrix.setTextColor(colors[0]);

  // ----- setup WI-Fi
  Serial.begin(115200);

  // si SPIFFS ne démarre pas, alerter
  if (!SPIFFS.begin(true)) {
    Serial.println("erreur SPIFFs");
    return;
  }

  // connection Wi-Fi (=boucle d'attente)
  WiFi.begin(ssid, password);
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
}

int y = matrix.height();
int x = matrix.width();
int pass = 0;
int line_pass = 0;

void loop() {
    
  // if mode greater than numMode reset
  if (mode > numMode) { mode = 0; }
  
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  scroll(Text[mode],50);
}

// this does the magic of scrolling
void scroll(char* message,int delays) {
  maxDisplacement = strlen(message) * pixelPerChar + matrix.width();
  if(++line_pass > matrix.width()) line_pass = 0;
  matrix.print(String(message));
  if(--x < -maxDisplacement) {
    x = matrix.width();
    if(++pass >= numColor) { pass = 0;  };
    matrix.setTextColor(colors[pass]);
    mode++;
  }
  matrix.show();
  delay(delays);
}
