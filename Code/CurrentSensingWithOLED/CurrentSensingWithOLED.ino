#include <SPI.h>
#include <Wire.h>

#include <Adafruit_INA219.h>


Adafruit_INA219 ina219;


// ************** Adafruit Oled Initializations
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// ************** Adafruit Oled Initializations Complete 


void setup()
{
  Serial.begin(115200);
  Wire.begin();

 Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
 ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
   
//   ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
  
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(500);
  display.clearDisplay();
  /* end of Adafruit Default Specification */
  /* Basic "hello world!" */
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  String s = "AnnaSid";
  display.println(s);
  display.display();
  display.clearDisplay();
  delay(500);


}

void measureVoltageCurrent()
{
    float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  Serial.println("Ensure: V+ to Supply, V- to Load's positive terminal");
  
  display.clearDisplay();
 
  display.setTextSize(2);
  display.setCursor (5, 20);

  display.print("bvlt: "); display.println(busvoltage);

   display.setCursor (5, 40);
  display.print("cur:");display.print(current_mA);
  display.display();
  delay(1000);
 display.clearDisplay();
  
 {
   Serial.print("Bus Voltage (betwee V- of INA219 and common Ground) :   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage (across the INA219's internal resistance): "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage: (between V+ and common Ground) "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("");
 }
  
}

void loop()
{


  measureVoltageCurrent(); 



}

