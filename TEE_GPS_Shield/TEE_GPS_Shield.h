/*
* ThaiEasyElec
* Quectel L76 GPS Shield
* Vertion 1.0 :	2017/07/21
* Visit us 	  : http://thaieasyelec.com
*/
#ifndef GPS_h
#define GPS_h
#include <Stream.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Arduino.h>
class GPS {
	public:
		GPS();
		void begin(SoftwareSerial *serial);
		void begin(HardwareSerial *serial);
        void read(byte mode);
		void gpsType(byte mode);
		String getUtctime();
		String getLatitude();
		String getLongitude();
		String getAltitude();
		String latitudeGoogle(String latitude);
		String longitudeGoogle(String longitude);
	protected:
		Stream *_Serial;
};
 
#endif