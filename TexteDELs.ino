//Affiche.ino

/*----------------- VARAIBLES POUR LEDS MATRIX -----------------*/
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 22
char* texteLED = "Bienvenu!   Joyeuse Fetes!   Bonne vacances!";

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(25, 10, PIN,
 NEO_MATRIX_BOTTOM    + NEO_MATRIX_LEFT +
 NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
 NEO_GRB            + NEO_KHZ800);

// Tableau avec la liste des couleurs

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
    request->send(SPIFFS, "/logo.png", "image/png");
  });

  // écoute requète fichier style.css (reçue par le lien de style.css dans html)
  monServeur.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  //Logo
   monServeur.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/logo.png", "image/png");
  });
  // Ajout des police de DELs
  monServeur.on("/AdvancedLEDBoard-7.woff", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/AdvancedLEDBoard-7.woff", "text/css");
  });
  monServeur.on("/AdvancedLEDBoard-7.woff2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/AdvancedLEDBoard-7.woff2", "text/css");
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

// Session 3
  monServeur.on("/3C1", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Design d’interactivite");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/3J3", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Creation de jeu 3D");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/3M5", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Imagerie 3D");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/3W3", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Creation de sites Web dynamiques");
    request->send(SPIFFS, "/index.html", String(), false);
  });

// Session 4
  monServeur.on("/4C2", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Gestion de projets multimedias");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/4J4", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Creation de jeu en equipe");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/4MB", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Animation 3D");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/4PA", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Interfaces Web reactives et animees");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/4W4", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Conception d’interfaces et developpement Web");
    request->send(SPIFFS, "/index.html", String(), false);
  });

// Session 5
  monServeur.on("/5E1", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Methodes de recherche et preparation au marche du travail");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/5JA", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Experimentation en jeu – volet programmation");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/5JB", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Experimentation en jeu – volet creation");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/5MB", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Technologies emergentes et avancees – volet Creation");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/5PA", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Technologies emergentes et avancees – volet programmation");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/5W5", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Projet Web en equipe");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/5N1", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Communication et dynamique d’une equipe de travail");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  //Session 6
  monServeur.on("/6N2", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Stage");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/6N3", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Projet de fin d’etudes");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // AUTRES
  monServeur.on("/CDH", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("Realise par: Carl-David Hyppolite");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/139", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("139 Pie-IX");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  monServeur.on("/185", HTTP_GET, [](AsyncWebServerRequest * request) {
    changerText("185 Sherbrooke");
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // demarrer serveur
  monServeur.begin();
}

int x = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);    //Éteindre toutes les LEDs
  matrix.setCursor(x, 0);
  matrix.print(F(texteLED)); //Affiche le texte

  //Défiler le texte (selon le nombre de lettre dans le mot)
  if( --x < -(5.8 * strlen(texteLED)) ) {
    x = matrix.width();

    if(++pass >= 8) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(temps);
}

//Remplace la valeur du text affiché par une autre
void changerText(char* newText) {
  texteLED = newText;
  Serial.println(texteLED);
  Serial.println(strlen(texteLED));
}
// fovayis610@bitvoo.com
