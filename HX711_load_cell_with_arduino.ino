#include "HX711.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define DT  3
#define SCK  2
HX711 scale(DT, SCK);

float weight; 
float calibration_factor = 104200; //104200
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}
void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  weight = scale.get_units(5); 
    if(weight<0)
  {
    weight=0.00;
    }
  //Serial.print(scale.get_units(), 2);
 // Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print("Kilogram:");
  Serial.print( weight); 
  Serial.print(" Kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(10,20); // column row
//  display.print("Weight:");
//  display.setTextSize(3);
//  display.setCursor(0,35);
  display.print(weight);
  display.setTextSize(3);
 // display.setCursor(75,35);
  display.print("Kg"); 
 display.display();
 delay(100);
}
