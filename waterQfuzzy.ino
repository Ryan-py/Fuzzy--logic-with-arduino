//fuzzy logic
#include "fuzz.h"
//gsm

#include "gsm.h"
//temperature
#include <OneWire.h>
#include <DallasTemperature.h>

int ONE_WIRE_BUS =4; //D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float get_temp()
{
  sensors.requestTemperatures(); 
  delay(100);
  float temp=sensors.getTempCByIndex(0);
  temp=24.0;
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


#define relay 9

void stop_pump()
{
  digitalWrite(relay,HIGH);
}
void pump()
{
  digitalWrite(relay,LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //initiating fuzzy logic
  fuzzy_logic_init();
  //initializing temperature sensor
  sensors.begin();

  //ec sensor
  ec.begin();
  delay(100);

  //lcd 
  lcd.init(); //initialize the lcd
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Water Quality");
  lcd.setCursor(0,1);
  lcd.print("GROUP 3");
  gsm_init();
  delay(500);
  lcd.clear();

  //pins
  pinMode(EC_PIN,INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);

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

  float output= fuzzy_result(Tub,Ec,Temp);// tub ,ec respectively
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fuzzy T Ec");
  lcd.setCursor(0,1);
  lcd.print(output);
  lcd.setCursor(5,1);
  lcd.print(Tub);
  lcd.setCursor(10,1);
  lcd.print(Ec);


  if (output >50)
{ 
  
  pump();
  send_gsm(1);
 
}
else if(output>30 && output <50){
  
  pump();
  send_gsm(2);

  }
else if (output<30)
{
    stop_pump();
    send_gsm(3);

}

}
