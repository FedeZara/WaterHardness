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
#include "Label.h"
#include "Button.h"
#include "Page.h"
#include "NavigationController.h"

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

/* Connect SCL    to analog 5 (Arduino Uno) or digital 21 (Arduino Mega)
   Connect SDA    to analog 4 (Arduino Uno) or digital 20 (Arduino Mega)
   Connect VCC    to 5V DC
   Connect GROUND to common ground */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void DefinePages();

NavigationController navigationController;

CalibrationData calData;
LinearRegression model;

double rSquared;

void setup()
{
  Serial.begin(9600);

  tft.begin();
  tft.setRotation(3);

  ts.InitTouch();
  ts.setPrecision(PREC_EXTREME);

  tcs.begin();

  // Clear EEPROM 
  // Suggested if using the device for the first time
  /* for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 0);
  }*/

  DefinePages(); 

  navigationController.NavigateTo(1);
}

void DefinePages(){
  navigationController.SetNumPages(5);

  navigationController.AddPage(new MainPage(), 0);
  navigationController.AddPage(new StartCalibrationPage(), 1);
  navigationController.AddPage(new CalibrationPage(), 2);
  navigationController.AddPage(new EndCalibrationPage(), 3);
  navigationController.AddPage(new MeasurementPage(), 4);
}

void loop(void)
{
  navigationController.OnLoop();
}
