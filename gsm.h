
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
void updateSerial();
void gsm_init()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  
  
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
 mySerial.println("AT+CMGS=\"+254799453385\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();

}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
void send_gsm(int n)
{ int m;
  if (n!=m)
  {
    switch(n)
    {
      case 1:
        mySerial.print("Water Quality is Excellent"); //text content
        updateSerial();
        mySerial.write(26);
        break;
      case 2 :
        mySerial.print("Water Quality is Good"); //text content
        updateSerial();
        mySerial.write(26);
        break;
      case 3 :
        mySerial.print("Water Quality is Bad"); //text content
        updateSerial();
        mySerial.write(26);
        break;
      default:
        mySerial.print("Device Error"); //text content
        updateSerial();
        mySerial.write(26);
        

    }
    m=n;
    }
}

