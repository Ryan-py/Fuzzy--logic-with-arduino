#include <Arduino.h>
//fuzzy logic
#include "fuzz.h"

//temperature
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4 //D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float get_temp()
{
  sensors.requestTemperatures(); 
  float temp=sensors.getTempCByIndex(0);
  return temp;

}
//turbidity sensor
#define tubPin  A0
float get_tub(){
  int analogValue = analogRead(tubPin);
  float tub = map(analogValue, 0, 1023, 0, 100);
  return tub;

}

// EC sensor
#include "DFRobot_EC.h"
#include <EEPROM.h>

#define EC_PIN A1
DFRobot_EC ec;

float get_ec ()
{ 
  float voltage = analogRead(EC_PIN)/1024.0*5000; 
  float temp=get_temp();
  ec.calibration(voltage,temp); 
  float ecValue =  ec.readEC(voltage,temp);
  return ecValue ;

}

//lcd
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //sda A4, scl A5

void setup() {
  // put your setup code here, to run once:
  //initiating fuzzy logic
  fuzzy_logic_init();
  //initializing temperature sensor
  sensors.begin();
  //ec sensor
  ec.begin();
  //lcd 
  lcd.init(); //initialize the lcd
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Water Quality");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);



}

void loop() {
  // put your main code here, to run repeatedly:
  float Temp=get_temp();
  float Tub =get_tub();
  delayMicroseconds(500);
  float Ec = get_ec();

  Serial.print("Temp: ");
  Serial.println(Temp);
  Serial.print("Tub: ");
  Serial.println(Tub);
  Serial.print("EC: ");
  Serial.println(Ec);

  float output= fuzzy_result(Tub,Ec);// tub ,ec respectively
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Output");
  lcd.setCursor(0,0);
  lcd.print(output);

  delay(2000);

}
