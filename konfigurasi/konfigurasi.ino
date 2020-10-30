#include <EEPROM.h>
#include <Wire.h>
#include <Sodaq_DS3231.h>
 
#define alamatRTC 0x68
#define alamatEEPROMCekToken 0
#define tokenRTC 0xAA //<== rubah token jika ingin nilai baru
 
void setup() {
  Serial.begin(9600);
  Serial.println("Set waktu RTC otomatis dengan arduino");
  
  Serial.println();
 
  Wire.begin();
  if (EEPROM.read(alamatEEPROMCekToken) != tokenRTC)
  {
    //Waktu compiler
    char bulan[12];
    byte indexBulan;
    int jam, menit, detik, tanggal, tahun;
 
    char *namaBulan[12] = {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun",
      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    sscanf(__TIME__, "%d:%d:%d", &jam, &menit, &detik);
    sscanf(__DATE__, "%s %d %d", bulan, &tanggal, &tahun);
    for (indexBulan = 0; indexBulan < 12; indexBulan++) {
      if (strcmp(bulan, namaBulan[indexBulan]) == 0)
        break;
    }
    uint8_t wday = hariDariTanggal(tanggal, indexBulan + 1, tahun);
    DateTime dt(tahun, indexBulan + 1, tanggal, jam, menit, detik, wday);
    rtc.setDateTime(dt);
    EEPROM.write(alamatEEPROMCekToken, tokenRTC);
    Serial.println("RTC sudah otomatis di setting (Sekali saja)");
  }
}
 
uint32_t old_ts;
void loop() {
  String strNamaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
  DateTime now = rtc.now(); //get the current date-time
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.date(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(' ');
  Serial.print(strNamaHari[now.dayOfWeek()-1]);
  Serial.println();
 
  while (1);
}
byte hariDariTanggal(byte tanggal, byte bulan, uint16_t tahun)
{
  uint16_t jumlahHariPerBulanMasehi[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  if (tahun >= 2000)
    tahun -= 2000;
 
  uint32_t jumlahHari = tahun * 365;
  uint16_t tahunKabisat = tahun / 4;
  for (byte i = 0; i < tahun; i++)
  {
    if (!(i % 4))
    {
      jumlahHari++;
    }
  }
  jumlahHari += jumlahHariPerBulanMasehi[bulan - 1];
  if ( (bulan >= 2) && !(tahun % 4))
  {
    jumlahHari++;
  }
  jumlahHari += tanggal;
  return ((jumlahHari + 5) % 7) + 1;
}
