#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

unsigned int menit,jam;
unsigned int state;
#define relay1 2
#define relay2 3
#define relay3 4
#define relay4 5

void setup () {

digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
digitalWrite(relay4, HIGH);   

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
                                digitalWrite(relay1, LOW); state = 1;
                                digitalWrite(relay2, LOW);
                                digitalWrite(relay3, LOW);
                                digitalWrite(relay4, LOW);                
                              }
    else if (jam == 5) {
                        if (menit < 30) {
                                        digitalWrite(relay1, LOW); state = 2;
                                        digitalWrite(relay2, LOW);
                                        digitalWrite(relay3, LOW);
                                        digitalWrite(relay4, LOW);   
                                        }
                        else if (menit >=30) {
                                              digitalWrite(relay1, HIGH); state =3;
                                              digitalWrite(relay2, HIGH);
                                              digitalWrite(relay3, HIGH);
                                              digitalWrite(relay4, HIGH);   
                                              }
                       }
    else if (jam >=6 && jam <=18) {
                                  digitalWrite(relay1, HIGH); state = 4;
                                  digitalWrite(relay2, HIGH);
                                  digitalWrite(relay3, HIGH);
                                  digitalWrite(relay4, HIGH);   
                                  }
delay(100);
}
