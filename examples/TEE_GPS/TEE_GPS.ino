#include <TEE_GPS_Shield.h>
#include <OLED_SSD1306.h>

SoftwareSerial SoftwareSerial(4, 5);
GPS gps;
OLED_SSD1306 OLED;

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  
  Serial.begin(9600);
  gps.begin(&SoftwareSerial);                      // Use Software Serial please set jumper to sw
  //gps.begin(&Serial);                            // Arduino Leonardo use Serial1
  gps.gpsType(1);                                  // byte | '0' Type GPGGA , '1' Type GOOGLE
  OLED.begin(0x3C);
  OLED.clearscreen();
  Serial.println("TEST OLED");
  OLED.Char_F8x16(0, 0, "TEST OLED");
  OLED.Char_F6x8(0, 25, "1234567890");
  OLED.Char_F8x16(0, 50, "SSD1306");
}

void loop()
{
  
  gps.read(0);                                    // byte | '0' don't show all data , '1' show all data
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    String Utctime = gps.getUtctime();            // get UTC Time
    String Latitude = gps.getLatitude();          // get Latitude
    String Longitude = gps.getLongitude();        // get Longitude
    String Altitude = gps.getAltitude();          // Get Altitude
    OLED.clearscreen();
    OLED.Char_F8x16(30, 0, "\"TEST GPS\"");
    OLED.Char_F6x8(0, 25, "UTC Time");
    OLED.Char_F6x8(60, 25, Utctime);
    OLED.Char_F6x8(0, 32, "Latitude");
    OLED.Char_F6x8(60, 32, Latitude);
    OLED.Char_F6x8(0, 42, "Longitude");
    OLED.Char_F6x8(60, 42, Longitude);
    OLED.Char_F6x8(0, 52, "Altitude");
    OLED.Char_F6x8(60, 52, Altitude);
  }
}
