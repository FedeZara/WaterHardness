#include <Arduino.h>
#include <URTouch.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "EEPROM.h"
#include "math.h"
#include "MemoryFree.h"

#include "Point.h"
#include "CalibrationData.h"
#include "LinearRegression.h"
#include "LabelClass.h"
#include "ButtonClass.h"
#include "PageClass.h"
#include "PageControllerClass.h"

#include "MainPage.h"
#include "StartCalibrationPage.h"
#include "EndCalibrationPage.h"
#include "CalibrationPage.h"
#include "MeasurementPage.h"

using namespace std;

// For the Adafruit shield, these are the default.
#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 6
#define t_CS 5
#define t_MOSI 4
#define t_MISO 3
#define t_IRQ 2

URTouch ts = URTouch(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void DefinePages();

PageController pageController;

CalibrationData calData;
LinearRegression model;

double rSquared;

void setup()
{
  Serial.begin(9600);

  tft.begin();
  tft.setRotation(3);

  /*// read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); */

  ts.InitTouch();
  ts.setPrecision(PREC_EXTREME);

  if (tcs.begin())
  {
    Serial.println("Found sensor");
  }
  else
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;
  }

  // Clear EEPROM 
  /* for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 0);
  }*/

  DefinePages(); 

  Serial.println(freeMemory());

  pageController.NavigateTo(1);
}

void DefinePages(){
  pageController.SetNumPages(5);

  pageController.AddPage(new MainPage(), 0);
  pageController.AddPage(new StartCalibrationPage(), 1);
  pageController.AddPage(new CalibrationPage(), 2);
  pageController.AddPage(new EndCalibrationPage(), 3);
  pageController.AddPage(new MeasurementPage(), 4);
}

void loop(void)
{
  pageController.OnLoop();
}
