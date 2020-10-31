#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

unsigned int menit,jam;
unsigned int state;
#define relay1 2
#define relay2 3
#define relay3 4
#define relay4 5
#define relay5 6 //for DC out from controller

void setup () {

pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
pinMode(relay5, OUTPUT);
digitalWrite(relay1,HIGH);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,HIGH);
digitalWrite(relay4,HIGH);
digitalWrite(relay5,HIGH);

  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("RTC TIDAK TERBACA");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//update rtc dari waktu komputer
  }
}

void loop () {

  
    DateTime now = rtc.now();
    Serial.print(now.dayOfTheWeek());  
    Serial.print(',');    
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" ");   
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print("  ");
    Serial.print("state = ");
    Serial.println(state);

    //algo
    jam = now.hour();
    menit = now.minute();

    if (jam >= 18 || jam <=4) { //lampu nyala
                                digitalWrite(relay5, LOW); delay(5000); //inverter ON
                                digitalWrite(relay1, LOW); state = 1; delay(2000);
                                digitalWrite(relay2, LOW);
                                digitalWrite(relay3, LOW); delay(2000);
                                digitalWrite(relay4, LOW);                
                              }
    else if (jam == 5) {
                        if (menit < 30) {
                                        digitalWrite(relay5, LOW); delay(5000); //inverter ON
                                        digitalWrite(relay1, LOW); delay(2000); state = 2;
                                        digitalWrite(relay2, LOW);
                                        digitalWrite(relay3, LOW); delay(2000);
                                        digitalWrite(relay4, LOW);   
                                        }
                        else if (menit >=30) {
                                              state =3;
                                              digitalWrite(relay1, HIGH); 
                                              delay(2000);
                                              digitalWrite(relay2, HIGH);
                                              digitalWrite(relay3, HIGH);
                                              delay(2000);
                                              digitalWrite(relay4, HIGH);
                                              delay(5000);
                                              digitalWrite(relay5, HIGH); //inverter OFF
                                              }
                       }
    else if (jam >=6 && jam <=18) {
                                  state = 4; 
                                  digitalWrite(relay5, HIGH); //inverter OFF
                                  digitalWrite(relay1, HIGH); 
                                  digitalWrite(relay2, HIGH);
                                  digitalWrite(relay3, HIGH);
                                  digitalWrite(relay4, HIGH);   
                                  }
delay(3000);
}
