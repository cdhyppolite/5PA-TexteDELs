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


char* Text[] = {"CARL-DAVID HYPPOLITE :)"};
char* getRequete = "";
const uint16_t colors[] = {
  matrix.Color(255, 51, 153)
};
int brightness = 80;
// End Edit

int numMode = arr_len(Text) - 1;
int numColor = arr_len(colors) - 1;
int pixelPerChar = 4;
int maxDisplacement;
int mode = 0;

const long logoTim[]PROGMEM = {
  0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0A, 0x08, 0x04, 0x00, 0x00, 0x00, 0xEB, 0xA2, 0x3D, 0xDD, 0x00, 0x00, 0x00, 0xED, 0x69, 0x43, 0x43, 0x50, 0x47, 0x72, 0x61, 0x79, 0x20, 0x47, 0x61, 0x6D, 0x6D, 0x61, 0x20, 0x32, 0x2E, 0x32, 0x00, 0x00, 0x18, 0x95, 0x95, 0xCE, 0x3F, 0x4A, 0x03, 0x41, 0x1C, 0xC5, 0xF1, 0xEF, 0x44, 0xD4, 0x4E, 0x2D, 0x82, 0xF5, 0x5C, 0x40, 0xC1, 0xB5, 0xDA, 0x72, 0xF2, 0x87, 0x45, 0xB0, 0x08, 0x31, 0x45, 0x36, 0x95, 0x9B, 0xD9, 0x41, 0x43, 0xD8, 0x9D, 0x61, 0xF6, 0xE7, 0x9F, 0xBD, 0x81, 0x47, 0xF0, 0x38, 0xDE, 0x20, 0x85, 0x90, 0x8B, 0x44, 0xAC, 0x2D, 0x0C, 0x04, 0x3B, 0xF3, 0xA9, 0x1E, 0xAF, 0x79, 0x0F, 0xD4, 0xBB, 0x19, 0xF4, 0x86, 0x9D, 0x33, 0xA8, 0x6A, 0x89, 0xD9, 0xD8, 0xE4, 0xD3, 0x7C, 0xA6, 0x8F, 0x57, 0x1C, 0x71, 0x00, 0x00, 0x85, 0x6D, 0x82, 0x19, 0x8D, 0x6E, 0x01, 0x6A, 0x5F, 0x3B, 0xFE, 0x52, 0xF0, 0xBD, 0x46, 0x01, 0x7C, 0x5E, 0x98, 0x41, 0x6F, 0xC8, 0x7E, 0x0E, 0x6D, 0x88, 0x02, 0x7C, 0x00, 0x49, 0xE9, 0x1A, 0x0B, 0x7C, 0x01, 0x8B, 0x17, 0x09, 0x02, 0xEA, 0x1E, 0xE8, 0xCE, 0x97, 0x41, 0x40, 0x09, 0xD0, 0x5D, 0x4E, 0xC6, 0x7D, 0x50, 0x6F, 0xC0, 0x89, 0xB8, 0x57, 0x01, 0xE8, 0xFB, 0xD0, 0xC6, 0xC5, 0xC3, 0xA3, 0xE8, 0xAB, 0x34, 0x4D, 0xB5, 0x29, 0xFD, 0xDC, 0xE9, 0xBB, 0xB6, 0x11, 0x57, 0x35, 0xFA, 0xA6, 0xB6, 0x3E, 0x06, 0x1F, 0x0B, 0x71, 0x25, 0xB0, 0xDD, 0x00, 0x38, 0xCD, 0x62, 0xD1, 0xEA, 0xAC, 0xA8, 0xAA, 0x42, 0x27, 0x97, 0xC9, 0x9E, 0xCF, 0xFF, 0x61, 0x9A, 0xCF, 0xF4, 0x6F, 0xDA, 0x4C, 0x50, 0x80, 0x3A, 0x5F, 0xED, 0xBA, 0x1D, 0xFB, 0x14, 0x9F, 0xB7, 0x51, 0x75, 0xAE, 0xE1, 0x07, 0x4B, 0x1B, 0x38, 0x30, 0xDC, 0x8A, 0x57, 0xB4, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x1E, 0xC2, 0x00, 0x00, 0x1E, 0xC2, 0x01, 0x6E, 0xD0, 0x75, 0x3E, 0x00, 0x00, 0x04, 0xEE, 0x69, 0x54, 0x58, 0x74, 0x58, 0x4D, 0x4C, 0x3A, 0x63, 0x6F, 0x6D, 0x2E, 0x61, 0x64, 0x6F, 0x62, 0x65, 0x2E, 0x78, 0x6D, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x3F, 0x78, 0x70, 0x61, 0x63, 0x6B, 0x65, 0x74, 0x20, 0x62, 0x65, 0x67, 0x69, 0x6E, 0x3D, 0x22, 0xEF, 0xBB, 0xBF, 0x22, 0x20, 0x69, 0x64, 0x3D, 0x22, 0x57, 0x35, 0x4D, 0x30, 0x4D, 0x70, 0x43, 0x65, 0x68, 0x69, 0x48, 0x7A, 0x72, 0x65, 0x53, 0x7A, 0x4E, 0x54, 0x63, 0x7A, 0x6B, 0x63, 0x39, 0x64, 0x22, 0x3F, 0x3E, 0x20, 0x3C, 0x78, 0x3A, 0x78, 0x6D, 0x70, 0x6D, 0x65, 0x74, 0x61, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x78, 0x3D, 0x22, 0x61, 0x64, 0x6F, 0x62, 0x65, 0x3A, 0x6E, 0x73, 0x3A, 0x6D, 0x65, 0x74, 0x61, 0x2F, 0x22, 0x20, 0x78, 0x3A, 0x78, 0x6D, 0x70, 0x74, 0x6B, 0x3D, 0x22, 0x41, 0x64, 0x6F, 0x62, 0x65, 0x20, 0x58, 0x4D, 0x50, 0x20, 0x43, 0x6F, 0x72, 0x65, 0x20, 0x37, 0x2E, 0x32, 0x2D, 0x63, 0x30, 0x30, 0x30, 0x20, 0x37, 0x39, 0x2E, 0x31, 0x62, 0x36, 0x35, 0x61, 0x37, 0x39, 0x2C, 0x20, 0x32, 0x30, 0x32, 0x32, 0x2F, 0x30, 0x36, 0x2F, 0x31, 0x33, 0x2D, 0x31, 0x37, 0x3A, 0x34, 0x36, 0x3A, 0x31, 0x34, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x3E, 0x20, 0x3C, 0x72, 0x64, 0x66, 0x3A, 0x52, 0x44, 0x46, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x72, 0x64, 0x66, 0x3D, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x77, 0x77, 0x77, 0x2E, 0x77, 0x33, 0x2E, 0x6F, 0x72, 0x67, 0x2F, 0x31, 0x39, 0x39, 0x39, 0x2F, 0x30, 0x32, 0x2F, 0x32, 0x32, 0x2D, 0x72, 0x64, 0x66, 0x2D, 0x73, 0x79, 0x6E, 0x74, 0x61, 0x78, 0x2D, 0x6E, 0x73, 0x23, 0x22, 0x3E, 0x20, 0x3C, 0x72, 0x64, 0x66, 0x3A, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x72, 0x64, 0x66, 0x3A, 0x61, 0x62, 0x6F, 0x75, 0x74, 0x3D, 0x22, 0x22, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x78, 0x6D, 0x70, 0x3D, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x6E, 0x73, 0x2E, 0x61, 0x64, 0x6F, 0x62, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x78, 0x61, 0x70, 0x2F, 0x31, 0x2E, 0x30, 0x2F, 0x22, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x64, 0x63, 0x3D, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x70, 0x75, 0x72, 0x6C, 0x2E, 0x6F, 0x72, 0x67, 0x2F, 0x64, 0x63, 0x2F, 0x65, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x73, 0x2F, 0x31, 0x2E, 0x31, 0x2F, 0x22, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x70, 0x68, 0x6F, 0x74, 0x6F, 0x73, 0x68, 0x6F, 0x70, 0x3D, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x6E, 0x73, 0x2E, 0x61, 0x64, 0x6F, 0x62, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x70, 0x68, 0x6F, 0x74, 0x6F, 0x73, 0x68, 0x6F, 0x70, 0x2F, 0x31, 0x2E, 0x30, 0x2F, 0x22, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x78, 0x6D, 0x70, 0x4D, 0x4D, 0x3D, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x6E, 0x73, 0x2E, 0x61, 0x64, 0x6F, 0x62, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x78, 0x61, 0x70, 0x2F, 0x31, 0x2E, 0x30, 0x2F, 0x6D, 0x6D, 0x2F, 0x22, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3A, 0x73, 0x74, 0x45, 0x76, 0x74, 0x3D, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x6E, 0x73, 0x2E, 0x61, 0x64, 0x6F, 0x62, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x78, 0x61, 0x70, 0x2F, 0x31, 0x2E, 0x30, 0x2F, 0x73, 0x54, 0x79, 0x70, 0x65, 0x2F, 0x52, 0x65, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x45, 0x76, 0x65, 0x6E, 0x74, 0x23, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x3A, 0x43, 0x72, 0x65, 0x61, 0x74, 0x6F, 0x72, 0x54, 0x6F, 0x6F, 0x6C, 0x3D, 0x22, 0x41, 0x64, 0x6F, 0x62, 0x65, 0x20, 0x50, 0x68, 0x6F, 0x74, 0x6F, 0x73, 0x68, 0x6F, 0x70, 0x20, 0x32, 0x33, 0x2E, 0x35, 0x20, 0x28, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x29, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x3A, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x44, 0x61, 0x74, 0x65, 0x3D, 0x22, 0x32, 0x30, 0x32, 0x32, 0x2D, 0x31, 0x31, 0x2D, 0x32, 0x39, 0x54, 0x31, 0x35, 0x3A, 0x31, 0x30, 0x3A, 0x35, 0x33, 0x2D, 0x30, 0x35, 0x3A, 0x30, 0x30, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x3A, 0x4D, 0x6F, 0x64, 0x69, 0x66, 0x79, 0x44, 0x61, 0x74, 0x65, 0x3D, 0x22, 0x32, 0x30, 0x32, 0x32, 0x2D, 0x31, 0x31, 0x2D, 0x32, 0x39, 0x54, 0x31, 0x35, 0x3A, 0x31, 0x34, 0x3A, 0x32, 0x35, 0x2D, 0x30, 0x35, 0x3A, 0x30, 0x30, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x3A, 0x4D, 0x65, 0x74, 0x61, 0x64, 0x61, 0x74, 0x61, 0x44, 0x61, 0x74, 0x65, 0x3D, 0x22, 0x32, 0x30, 0x32, 0x32, 0x2D, 0x31, 0x31, 0x2D, 0x32, 0x39, 0x54, 0x31, 0x35, 0x3A, 0x31, 0x34, 0x3A, 0x32, 0x35, 0x2D, 0x30, 0x35, 0x3A, 0x30, 0x30, 0x22, 0x20, 0x64, 0x63, 0x3A, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x3D, 0x22, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x2F, 0x70, 0x6E, 0x67, 0x22, 0x20, 0x70, 0x68, 0x6F, 0x74, 0x6F, 0x73, 0x68, 0x6F, 0x70, 0x3A, 0x43, 0x6F, 0x6C, 0x6F, 0x72, 0x4D, 0x6F, 0x64, 0x65, 0x3D, 0x22, 0x31, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x4D, 0x4D, 0x3A, 0x49, 0x6E, 0x73, 0x74, 0x61, 0x6E, 0x63, 0x65, 0x49, 0x44, 0x3D, 0x22, 0x78, 0x6D, 0x70, 0x2E, 0x69, 0x69, 0x64, 0x3A, 0x39, 0x65, 0x36, 0x37, 0x62, 0x64, 0x39, 0x66, 0x2D, 0x33, 0x62, 0x33, 0x64, 0x2D, 0x34, 0x33, 0x34, 0x64, 0x2D, 0x39, 0x33, 0x35, 0x63, 0x2D, 0x30, 0x61, 0x65, 0x34, 0x31, 0x35, 0x62, 0x38, 0x32, 0x34, 0x38, 0x32, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x4D, 0x4D, 0x3A, 0x44, 0x6F, 0x63, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x49, 0x44, 0x3D, 0x22, 0x78, 0x6D, 0x70, 0x2E, 0x64, 0x69, 0x64, 0x3A, 0x39, 0x65, 0x36, 0x37, 0x62, 0x64, 0x39, 0x66, 0x2D, 0x33, 0x62, 0x33, 0x64, 0x2D, 0x34, 0x33, 0x34, 0x64, 0x2D, 0x39, 0x33, 0x35, 0x63, 0x2D, 0x30, 0x61, 0x65, 0x34, 0x31, 0x35, 0x62, 0x38, 0x32, 0x34, 0x38, 0x32, 0x22, 0x20, 0x78, 0x6D, 0x70, 0x4D, 0x4D, 0x3A, 0x4F, 0x72, 0x69, 0x67, 0x69, 0x6E, 0x61, 0x6C, 0x44, 0x6F, 0x63, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x49, 0x44, 0x3D, 0x22, 0x78, 0x6D, 0x70, 0x2E, 0x64, 0x69, 0x64, 0x3A, 0x39, 0x65, 0x36, 0x37, 0x62, 0x64, 0x39, 0x66, 0x2D, 0x33, 0x62, 0x33, 0x64, 0x2D, 0x34, 0x33, 0x34, 0x64, 0x2D, 0x39, 0x33, 0x35, 0x63, 0x2D, 0x30, 0x61, 0x65, 0x34, 0x31, 0x35, 0x62, 0x38, 0x32, 0x34, 0x38, 0x32, 0x22, 0x3E, 0x20, 0x3C, 0x78, 0x6D, 0x70, 0x4D, 0x4D, 0x3A, 0x48, 0x69, 0x73, 0x74, 0x6F, 0x72, 0x79, 0x3E, 0x20, 0x3C, 0x72, 0x64, 0x66, 0x3A, 0x53, 0x65, 0x71, 0x3E, 0x20, 0x3C, 0x72, 0x64, 0x66, 0x3A, 0x6C, 0x69, 0x20, 0x73, 0x74, 0x45, 0x76, 0x74, 0x3A, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x22, 0x20, 0x73, 0x74, 0x45, 0x76, 0x74, 0x3A, 0x69, 0x6E, 0x73, 0x74, 0x61, 0x6E, 0x63, 0x65, 0x49, 0x44, 0x3D, 0x22, 0x78, 0x6D, 0x70, 0x2E, 0x69, 0x69, 0x64, 0x3A, 0x39, 0x65, 0x36, 0x37, 0x62, 0x64, 0x39, 0x66, 0x2D, 0x33, 0x62, 0x33, 0x64, 0x2D, 0x34, 0x33, 0x34, 0x64, 0x2D, 0x39, 0x33, 0x35, 0x63, 0x2D, 0x30, 0x61, 0x65, 0x34, 0x31, 0x35, 0x62, 0x38, 0x32, 0x34, 0x38, 0x32, 0x22, 0x20, 0x73, 0x74, 0x45, 0x76, 0x74, 0x3A, 0x77, 0x68, 0x65, 0x6E, 0x3D, 0x22, 0x32, 0x30, 0x32, 0x32, 0x2D, 0x31, 0x31, 0x2D, 0x32, 0x39, 0x54, 0x31, 0x35, 0x3A, 0x31, 0x30, 0x3A, 0x35, 0x33, 0x2D, 0x30, 0x35, 0x3A, 0x30, 0x30, 0x22, 0x20, 0x73, 0x74, 0x45, 0x76, 0x74, 0x3A, 0x73, 0x6F, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x41, 0x67, 0x65, 0x6E, 0x74, 0x3D, 0x22, 0x41, 0x64, 0x6F, 0x62, 0x65, 0x20, 0x50, 0x68, 0x6F, 0x74, 0x6F, 0x73, 0x68, 0x6F, 0x70, 0x20, 0x32, 0x33, 0x2E, 0x35, 0x20, 0x28, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73, 0x29, 0x22, 0x2F, 0x3E, 0x20, 0x3C, 0x2F, 0x72, 0x64, 0x66, 0x3A, 0x53, 0x65, 0x71, 0x3E, 0x20, 0x3C, 0x2F, 0x78, 0x6D, 0x70, 0x4D, 0x4D, 0x3A, 0x48, 0x69, 0x73, 0x74, 0x6F, 0x72, 0x79, 0x3E, 0x20, 0x3C, 0x2F, 0x72, 0x64, 0x66, 0x3A, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x20, 0x3C, 0x2F, 0x72, 0x64, 0x66, 0x3A, 0x52, 0x44, 0x46, 0x3E, 0x20, 0x3C, 0x2F, 0x78, 0x3A, 0x78, 0x6D, 0x70, 0x6D, 0x65, 0x74, 0x61, 0x3E, 0x20, 0x3C, 0x3F, 0x78, 0x70, 0x61, 0x63, 0x6B, 0x65, 0x74, 0x20, 0x65, 0x6E, 0x64, 0x3D, 0x22, 0x72, 0x22, 0x3F, 0x3E, 0x31, 0xD9, 0x5B, 0x1A, 0x00, 0x00, 0x00, 0x99, 0x49, 0x44, 0x41, 0x54, 0x18, 0x95, 0x7D, 0xCF, 0xB1, 0x72, 0x02, 0x31, 0x0C, 0x04, 0xD0, 0x27, 0x71, 0x84, 0x7F, 0xA4, 0xE6, 0xFF, 0x9B, 0x74, 0xCC, 0xD9, 0xA2, 0xB0, 0x31, 0x47, 0x48, 0x22, 0x8F, 0x6D, 0x8D, 0xB4, 0xAB, 0xD5, 0xC6, 0x56, 0x05, 0x02, 0xBB, 0x91, 0x13, 0x25, 0x20, 0x7A, 0xCF, 0x51, 0x39, 0xA3, 0x49, 0x21, 0x2F, 0xBA, 0xAE, 0x3D, 0xA1, 0xF3, 0x8D, 0x38, 0xD9, 0x60, 0x12, 0xA8, 0x85, 0xC9, 0xEF, 0xDA, 0xAB, 0x29, 0x5F, 0x8B, 0x14, 0x28, 0xA5, 0xBD, 0xF0, 0xA8, 0x79, 0xC9, 0xB8, 0xA6, 0xC0, 0x7D, 0x36, 0xC6, 0x19, 0xB4, 0xBE, 0x74, 0xB7, 0x55, 0x25, 0xDD, 0x66, 0xF6, 0x23, 0x06, 0x49, 0xE5, 0x61, 0xD4, 0xD3, 0xE7, 0xD4, 0x3F, 0xBF, 0xD9, 0x4F, 0xA9, 0x29, 0x21, 0x14, 0x42, 0x29, 0x39, 0xEC, 0xBF, 0x16, 0xDE, 0x7F, 0xD1, 0x2A, 0x6C, 0x72, 0xF9, 0x18, 0x4B, 0xFE, 0x11, 0xB5, 0xFE, 0x76, 0x80, 0x8F, 0x0D, 0xFE, 0x67, 0xCC, 0xE4, 0x48, 0x1A, 0x94, 0xF6, 0x29, 0x18, 0xE2, 0x7D, 0xF8, 0x8A, 0x07, 0xCF, 0x2D, 0x3B, 0xC4, 0x42, 0x16, 0x21, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};
//https://www.iloveimg.com/

/*----------------- FIN VARAIBLES LEDS MATRIX -----------------*/

/*----------------- VARAIBLES POUR CONNEXION WI-FI -----------------*/
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> //marche sans
#include "SPIFFS.h"

// création instance d'un serveur asynchrone sur le port 80
AsyncWebServer monServeur(80);

// réseau Wifi
const char* ssid = "reseau2";
const char* password = "123456789";
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

  // get
  monServeur.on("/get", HTTP_GET, [](AsyncWebServerRequest * request) {
    // getRequete = request->params();
    int paramsNr = request->params();
    Serial.println(paramsNr);

    for (int i = 0; i < paramsNr; i++) {

      AsyncWebParameter* p = request->getParam(i);
      Serial.print("Param name: ");
      Serial.println(p->name());
      Serial.print("Param value: ");
      Serial.println(p->value());
      Serial.println("------");
    }

    Serial.println("Requête: ");
    Serial.println(getRequete);
    request->send(SPIFFS, "/index.html", String(), false);
  });
  // demarrer serveur
  monServeur.begin();
}

int y = matrix.height();
int x = matrix.width();
int pass = 0;
int line_pass = 0;

void loop() {

  // if mode greater than numMode reset
  if (mode > numMode) {
    mode = 0;
  }

  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  scroll(Text[mode], 50);
}

// this does the magic of scrolling
void scroll(char* message, int delays) {
  maxDisplacement = strlen(message) * pixelPerChar + matrix.width();
  if (++line_pass > matrix.width()) line_pass = 0;
  matrix.print(String(message));
  if (--x < -maxDisplacement) {
    x = matrix.width();
    if (++pass >= numColor) {
      pass = 0;
    };
    matrix.setTextColor(colors[pass]);
    mode++;
  }
  matrix.show();
  delay(delays);
}